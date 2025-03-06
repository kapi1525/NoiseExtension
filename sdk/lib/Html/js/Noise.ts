// Wasm gets embeded into .js file by esbuild, its stored in base64 and gets converted to UInt8Array.
import extWasm from "Extension.wasm";
import {WASI, File, OpenFile, ConsoleStdout} from "@bjorn3/browser_wasi_shim";

// FIXME: This should be generated from a template or something at build time



interface WasmCallbacks {
    // For ace param lookup:
    getNumber: (index: number) => number,
    getString: (bufferPtr: number, bufferSize: number, index: number) => number,
    // For setting expression return value:
    setNumber: (value: number) => void,
    setString: (cStrPtr: number, cStrSize: number) => void,
}

function getBlankWasmCallbacks(): WasmCallbacks {
    return {
        getNumber: () => { console.warn("Called uninitialized callback!"); return 0; },
        getString: () => { console.warn("Called uninitialized callback!"); return 0; },
        setNumber: () => { console.warn("Called uninitialized callback!"); },
        setString: () => { console.warn("Called uninitialized callback!"); },
    }
};

// Currently you cant pass JS callback functions to wasm as a function parameter.
// imported js functions will call into functions stored in this object.
let wasmCallbacks: WasmCallbacks = getBlankWasmCallbacks();



// Used to pass strings between wasm and js
// Required for utf16 -> utf8 conversion.
// TODO: Maybe build the extension as UNICODE so no conversion would be required?
const encoder = new TextEncoder;
const decoder = new TextDecoder;



// We only use wasi apis implementation.
const wasi = new WASI(
    [], // args
    [], // env
    [   // open fds
        new OpenFile(new File([])),                                                     // stdin
        new ConsoleStdout(msg => console.log(decoder.decode(msg).replace("\n", ""))),   // stdout
        new ConsoleStdout(msg => console.warn(decoder.decode(msg)))                     // stderr
    ]
);

// Init wasm module
const extModule = new WebAssembly.Module(extWasm);
const extInstance = new WebAssembly.Instance(extModule, {
    "wasi_snapshot_preview1": wasi.wasiImport,
    "ace_params": {
        "get_integer": (index: number) =>                                        { return wasmCallbacks.getNumber(index); },
        "get_float":   (index: number) =>                                        { return wasmCallbacks.getNumber(index); },
        "get_string":  (bufferPtr: number, bufferSize: number, index: number) => { return wasmCallbacks.getString(bufferPtr, bufferSize, index); },
        "set_integer": (value: number) =>                                        { wasmCallbacks.setNumber(value); },
        "set_float":   (value: number) =>                                        { wasmCallbacks.setNumber(value); },
        "set_string":  (cStrPtr: number, cStrSize: number) =>                    { wasmCallbacks.setString(cStrPtr, cStrSize); },
    }
});

wasi.initialize(extInstance as any);

let cppLand = {
    memory:                 extInstance.exports["memory"]                   as WebAssembly.Memory,
    malloc:                 extInstance.exports["wasm_malloc"]              as (size: number) => number,
    free:                   extInstance.exports["wasm_free"]                as (ptr: number) => void,
    init:                   extInstance.exports["init"]                     as () => void,
    dealloc:                extInstance.exports["dealloc"]                  as () => void,
    getNumberOfConditions:  extInstance.exports["get_number_of_conditions"] as () => number,
    createRunObject:        extInstance.exports["create_run_object"]        as (edPtr: number, cobPtr: number, version: number) => number,
    destroyRunObject:       extInstance.exports["destroy_run_object"]       as (extPtr: number, fast: boolean) => void,
    handleRunObject:        extInstance.exports["handle_run_object"]        as (extPtr: number) => number,
    displayRunObject:       extInstance.exports["display_run_object"]       as (extPtr: number) => number,
    pauseRunObject:         extInstance.exports["pause_run_object"]         as (extPtr: number) => number,
    continueRunObject:      extInstance.exports["continue_run_object"]      as (extPtr: number) => number,
    conditionJump:          extInstance.exports["condition_jump"]           as (extPtr: number, id: number) => number,
    actionJump:             extInstance.exports["action_jump"]              as (extPtr: number, id: number) => void,
    expressionJump:         extInstance.exports["expression_jump"]          as (extPtr: number, id: number) => void,
}

cppLand.init();


// Prototype definition
// -----------------------------------------------------------------
// This class is a sub-class of CRunExtension, by the mean of the
// CServices.extend function which copies all the properties of
// the parent class to the new class when it is created.
// As all the necessary functions are defined in the parent class,
// you only need to keep the ones that you actually need in your code.
class CRunWasmExtWrapper extends CRunExtension {
    cppExtPtr: number = 0;

    constructor() {
        super();
    }

    // Returns the number of conditions
    // --------------------------------------------------------------------
    // Warning, if this number is not correct, the application _will_ crash
    getNumberOfConditions(): number {
        return cppLand.getNumberOfConditions();
    }

    // Creation of the object
    // --------------------------------------------------------------------
    // - file : a CFile object, pointing to the object's data zone
    // - cob : a CCreateObjectInfo containing infos about the created object
    // - version : the version number of the object, as defined in the C code
    createRunObject(file: CFile, cob: CCreateObjectInfo, version: number): boolean {
		// header uint32, hash uint32, hashtypes uint32, numprops uint16, pad uint16, sizeBytes uint32 (includes whole EDITDATA)
        const fileStart = file.getFilePointer();
        file.skipBytes(4 + 4 + 4 + 2 + 2);      // skip to sizeBytes
        const edSize = file.readAInt();         // Fixme: should be unsigned
        file.seek(fileStart);                   // go back to the begining

        // TODO: refactor to not require malloc export
        const edPtr = cppLand.malloc(edSize);

        const edView = new DataView(cppLand.memory.buffer, edPtr, edSize);

        // Recreate extHeader as its not saved but needed on c++ side.
        edView.setUint32(0, edSize, true);
        edView.setUint32(4, edSize, true);
        edView.setUint32(8, version, true);
        edView.setUint32(12, this.ho!.hoIdentifier, true);
        edView.setUint32(16, this.ho!.privateData, true);

        for (let i = 20; i < edSize; i++) {
            edView.setUint8(i, file.readAByte());
        }

        this.cppExtPtr = cppLand.createRunObject(edPtr, 0, version);

        cppLand.free(edPtr);

        return false;
    }

    // Handling of the object
    // ---------------------------------------------------------------------
    // This function is called at every loop of the game. You have to perform
    // in it all the tasks necessary for your object to function.
    // Return values:
    //    - 0 : this function will be called during the next loop
    //    - CRunExtension.REFLAG_ONESHOT : this function will not be called anymore
    //      In this case, call the this.reHandle(); function of the base class
    //      to have it called again.
    handleRunObject(): number {
        return cppLand.handleRunObject(this.cppExtPtr);
    }

    // Destruction of the object
    // ---------------------------------------------------------------
    // Called when the object is actually destroyed. This will always be
    // after the main game loop, and out of the actions processing : the
    // destroy process is queued until the very end of the game loop.
    destroyRunObject(bFast: boolean) {
        cppLand.destroyRunObject(this.cppExtPtr, bFast);
    }

    // Displays the object
    // ----------------------------------------------------------------
    // Called when the object needs to be displayed in the browser.
    //    - renderer : the Renderer object which will draw the object
    //    - xDraw : an offset to add to every X coordinate for display
    //    - yDraw : an offset to add to every Y coordinate for display
    // This function will only be called if the object's flags in the C code
    // indicate that this is a displayable object (OEFLAG_SPRITE)
    displayRunObject(renderer: Renderer, xDraw: number, yDraw: number) {
        cppLand.displayRunObject(this.cppExtPtr);
        // Example of display of an image, taking the layer and frame position
        // into account
        // var x = this.ho.hoX - this.rh.rhWindowX + this.ho.pLayer.x + xDraw;
        // var y = this.ho.hoY - this.rh.rhWindowY + this.ho.pLayer.y + yDraw;
        // renderer.renderSimpleImage(this.image, x, y, this.image.width, this.image.height, 0, 0);
    }

    // Put the object into pause
    // ----------------------------------------------------------------
    // Called when the game enters pause mode.
    pauseRunObject() {
        cppLand.pauseRunObject(this.cppExtPtr);
    }

    // Get the object out of pause mode
    // -----------------------------------------------------------------
    // Called when the game quits pause mode.
    continueRunObject() {
        cppLand.continueRunObject(this.cppExtPtr);
    }

    // Returns the current font of the object
    // -----------------------------------------------------------------
    // Return value:
    //    The CFontInfo object of the current font used by the object
    // Only called for objects who have a OEFLAG_TEXT flag defined
    getRunObjectFont(): (object | null) {
        return null;
    }

    // Sets the current font of the object
    // ------------------------------------------------------------------
    //    - font : a CFontInfo object containing the font to set
    //    - rc : null, or a CRect object containing the new size of the object
    //           it it has to be resized while changing the font
    setRunObjectFont(font: object, rc: object) {
    }

    // Gets the current color of the text
    // ------------------------------------------------------------------
    // Return value :
    //     A RGB value containing the current color of the font used by the object
    getRunObjectTextColor(): number {
        return 0;
    }

    // Sets the current color of the text
    // ------------------------------------------------------------------
    //     - color : the new color to use to display the text
    setRunObjectTextColor(color: number) {
    }

    // Condition entry
    // -----------------------------------------------------------------
    // Called when a condition of this object is evaluated
    //    - num : the number of the condition, as defined on top of this source
    //    - cnd : a CCndExtension object, allowing you to retreive the parameters
    //            of the condition
    // Return value :
    //    true or false
    condition(num: number, cnd: CCndExtension): boolean {
        wasmCallbacks.getNumber = (index: number) => {
            return cnd.getParamExpression(this.rh!, index) as number;
        };

        wasmCallbacks.getString = (bufferPtr: number, bufferSize: number, index: number) => {
            const string = cnd.getParamExpression(this.rh!, index) as string;

            if(bufferPtr == 0 || bufferSize == 0) {
                return (string.length * 3) + 1; // Not sure if +1 is required for the null terminator TODO: check.
            }

            const memory_view = new Uint8Array(cppLand.memory.buffer, bufferPtr, bufferSize);
            memory_view.fill(0);

            return encoder.encodeInto(string, memory_view).written;
        };

        const ret = cppLand.conditionJump(this.cppExtPtr!, num);

        // reset callbacks
        wasmCallbacks = getBlankWasmCallbacks();

        return (ret == 1);
    }

    // Action entry
    // --------------------------------------------------------------
    // Called when an action of this object is executed
    //   - num : number of the action, as defined in the list on top of this source
    //   - act : a CActExtension object, allowing you to retreive the parameters
    //           of the action
    action(num: number, act: CActExtension) {
        wasmCallbacks.getNumber = (index: number) => {
            return act.getParamExpression(this.rh!, index) as number;
        };

        wasmCallbacks.getString = (bufferPtr: number, bufferSize: number, index: number) => {
            const string = act.getParamExpression(this.rh!, index) as string;

            if(bufferPtr == 0 || bufferSize == 0) {
                return (string.length * 3) + 1; // Not sure if +1 is required for the null terminator TODO: check.
            }

            const memory_view = new Uint8Array(cppLand.memory.buffer, bufferPtr, bufferSize);
            memory_view.fill(0);

            return encoder.encodeInto(string, memory_view).written;
        };

        cppLand.actionJump(this.cppExtPtr!, num);

        // reset callbacks
        wasmCallbacks = getBlankWasmCallbacks();
    }

    // Expression entry
    // ------------------------------------------------------------------
    // Called during the evaluation of an expression.
    //    - num : the number of the expression, as defined on top of this source.
    // Note that it is important that your expression function asks for
    // each and every one of the parameters of the function, each time it is
    // called. The runtime will crash if you miss parameters.
    // Return value :
    //    - The result of the calculation, a number or a string
    expression(num: number): number | string {
        // getExpParam doesnt take in the index, so store the params as the same index may be needed multiple times.
        let params: (number | string)[] = [];


        wasmCallbacks.getNumber = (index: number) => {
            while(params.length <= index) {
                params.push(this.ho?.getExpParam()!);
            }
            return params[index] as number;
        };

        wasmCallbacks.getString = (bufferPtr: number, bufferSize: number, index: number) => {
            while(params.length <= index) {
                params.push(this.ho?.getExpParam()!);
            }

            const string = params[index] as string;

            if(bufferPtr == 0 || bufferSize == 0) {
                return (string.length * 3) + 1; // Not sure if +1 is required for the null terminator TODO: check.
            }

            const memory_view = new Uint8Array(cppLand.memory.buffer, bufferPtr, bufferSize);
            memory_view.fill(0);

            return encoder.encodeInto(string, memory_view).written;
        };


        let expressionReturn: number | string = 0;

        wasmCallbacks.setNumber = (value: number) => {
            expressionReturn = value;
        };

        wasmCallbacks.setString = (cStrPtr: number, cStrSize: number) => {
            const memory_view = new Uint8Array(cppLand.memory.buffer, cStrPtr, cStrSize);

            expressionReturn = decoder.decode(memory_view);
        };

        cppLand.expressionJump(this.cppExtPtr, num);

        // reset callbacks
        wasmCallbacks = getBlankWasmCallbacks();
        return expressionReturn;
    }
}

// You are perfectly free to define any new class or global function in this code.
// Avoid using generic names, as they may clash with future extensions. The best
// option is to have a prefix specific to your name or object, inserted before the
// name of the class or functions.

// esbuild bundles everything in a way that nothing gets exposed to outside and nothing can conflict
// Expose extension class globaly.
export default CRunWasmExtWrapper;