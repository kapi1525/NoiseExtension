// Wasm gets embeded into .js file by esbuild, its stored in base64 and gets converted to UInt8Array.
import wasm_file from "Noise.wasm"
import {WASI, File, OpenFile, ConsoleStdout} from "@bjorn3/browser_wasi_shim";

// FIXME: This should be generated from a template or something at build time

interface CppLand {
    memory: WebAssembly.Memory;
    // Allocating data
    wasm_alloc: (size: number) => number;
    wasm_free: (ptr: number) => void;
    // SDK init
    init: () => void;
    dealloc: () => void;
    // Object creation
    getNumberOfConditions: () => number;
    createRunObject: (file_ptr: number, cob_ptr: number, version: number) => number;
    destroyRunObject: (ext: number, bFast: boolean) => void;
    // Object handling
    handleRunObject: (ext: number) => number;
    displayRunObject: (ext: number) => number;
    pauseRunObject: (ext: number) => number;
    continueRunObject: (ext: number) => number;
    // ACE jumps
    conditionJump: (ext: number, num: number) => number;
    actionJump: (ext: number, num: number) => void;
    expressionJump: (ext: number, num: number) => void;
}


// Prototype definition
// -----------------------------------------------------------------
// This class is a sub-class of CRunExtension, by the mean of the
// CServices.extend function which copies all the properties of
// the parent class to the new class when it is created.
// As all the necessary functions are defined in the parent class,
// you only need to keep the ones that you actually need in your code.
class CRunNoise extends CRunExtension {
    static wasi = new WASI([], [], [new OpenFile(new File([])), ConsoleStdout.lineBuffered(msg => console.log(`[WASI stdout] ${msg}`)), ConsoleStdout.lineBuffered(msg => console.warn(`[WASI stderr] ${msg}`))]);

    static wasmImports = {
        condition_action_manager: {
            get_float: (index: number) => {
                if(CRunNoise.that.curConditionActionParams === null || CRunNoise.that.rh === null) {
                    return 0;
                }
                return Number(CRunNoise.that.curConditionActionParams.getParamExpression(CRunNoise.that.rh, index));
            },
            get_string: (index: number) => {
                if(CRunNoise.that.curConditionActionParams === null || CRunNoise.that.rh === null) {
                    return 0;
                }
                const strPtr = CRunNoise.wasmCStringAlloc(String(CRunNoise.that.curConditionActionParams.getParamExpression(CRunNoise.that.rh, index)));
                CRunNoise.that.wasmCStrings.push(strPtr);
                return strPtr;
            },
            get_integer: (index: number) => {
                return CRunNoise.wasmImports.condition_action_manager.get_float(index);
            },
        },
        expression_manager: {
            set_value_int: (a: number) => { CRunNoise.that.curExpressionReturn = a; },
            set_value_float: (a: number) => { CRunNoise.that.curExpressionReturn = a; },
            set_value_cstr: (strPtr: number) => { CRunNoise.that.curExpressionReturn = CRunNoise.wasmCStringDeref(strPtr); },
            get_float: (index: number) => {
                if(CRunNoise.that.ho === null) {
                    return 0;
                }
                while (CRunNoise.that.curExpressionParams.length <= index) {
                    CRunNoise.that.curExpressionParams.push(CRunNoise.that.ho.getExpParam());
                }
                return Number(CRunNoise.that.curExpressionParams[index]);
            },
            get_string: (index: number) => {
                if(CRunNoise.that.ho === null) {
                    return 0;
                }
                while (CRunNoise.that.curExpressionParams.length <= index) {
                    CRunNoise.that.curExpressionParams.push(CRunNoise.that.ho.getExpParam());
                }
                const strPtr = CRunNoise.wasmCStringAlloc(String(CRunNoise.that.curExpressionParams[index]));
                CRunNoise.that.wasmCStrings.push(strPtr);
                return strPtr;
            },
            get_integer: (index: number) => {
                return CRunNoise.wasmImports.expression_manager.get_float(index);
            },
        },
        wasi_snapshot_preview1: CRunNoise.wasi.wasiImport,
    };

    static wasmModule: WebAssembly.Module = new WebAssembly.Module(wasm_file);
    static wasmInstance: WebAssembly.Instance = new WebAssembly.Instance(CRunNoise.wasmModule, CRunNoise.wasmImports);
    static cppLand: CppLand = {
        memory: CRunNoise.wasmInstance.exports.memory as WebAssembly.Memory,
        wasm_alloc: CRunNoise.wasmInstance.exports.wasm_alloc as (size: number) => number,
        wasm_free: CRunNoise.wasmInstance.exports.wasm_free as (ptr: number) => void,
        init: CRunNoise.wasmInstance.exports.init as () => void,
        dealloc: CRunNoise.wasmInstance.exports.dealloc as () => void,
        getNumberOfConditions: CRunNoise.wasmInstance.exports.getNumberOfConditions as () => number,
        createRunObject: CRunNoise.wasmInstance.exports.createRunObject as (file_ptr: number, cob_ptr: number, version: number) => number,
        destroyRunObject: CRunNoise.wasmInstance.exports.destroyRunObject as (ext: number, bFast: boolean) => void,
        handleRunObject: CRunNoise.wasmInstance.exports.handleRunObject as (ext: number) => number,
        displayRunObject: CRunNoise.wasmInstance.exports.displayRunObject as (ext: number) => number,
        pauseRunObject: CRunNoise.wasmInstance.exports.pauseRunObject as (ext: number) => number,
        continueRunObject: CRunNoise.wasmInstance.exports.continueRunObject as (ext: number) => number,
        conditionJump: CRunNoise.wasmInstance.exports.conditionJump as (ext: number, num: number) => number,
        actionJump: CRunNoise.wasmInstance.exports.actionJump as (ext: number, num: number) => void,
        expressionJump: CRunNoise.wasmInstance.exports.expressionJump as (ext: number, num: number) => void,
    };

    cppExtPtr: number | null = null;

    static that: CRunNoise;
    curExpressionReturn: number | string | null = null;
    curExpressionParams: (number | string)[] = [];

    curConditionActionParams: CCndExtension | CActExtension | null = null;
    // Array of strings in wasm memory allocated by JS.
    wasmCStrings: number[] = [];

    // Functions for working with wasm side strings.
    static wasmCStringAlloc(str: string): number {
        const strLen = (str.length * 3) + 1;                    // https://developer.mozilla.org/en-US/docs/Web/API/TextEncoder/encodeInto#buffer_sizing
        const encoder = new TextEncoder;
        const strPtr = CRunNoise.cppLand.wasm_alloc(strLen);
        let strArray = new Uint8Array(CRunNoise.cppLand.memory.buffer, strPtr, strLen);
        strArray.fill(0);
        const ret = encoder.encodeInto(str, strArray);
        return strPtr;
    }

    static wasmCStringFree(strPtr: number) {
        CRunNoise.cppLand.wasm_free(strPtr);
    }

    static wasmCStringDeref(strPtr: number): string {
        const decoder = new TextDecoder;
        let strArray = new Uint8Array(CRunNoise.cppLand.memory.buffer, strPtr);
        strArray = strArray.subarray(0, strArray.findIndex((element) => { return element === 0; }));    // Find null terminator
        return decoder.decode(strArray);
    }

    // Constructor of the object.
    // ----------------------------------------------------------------
    // Called during the creation process of the object, but before any
    // initialization. You may want (although you can do it in CreateRunObject),
    // to instantiate variables.
    constructor() {
        super();
        CRunNoise.wasi.inst = CRunNoise.wasmInstance as any;
        CRunNoise.cppLand.init();
    }

    // Returns the number of conditions
    // --------------------------------------------------------------------
    // Warning, if this number is not correct, the application _will_ crash
    getNumberOfConditions(): number {
        return CRunNoise.cppLand.getNumberOfConditions();
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
        file.seek(fileStart)                    // go back to the begining

        const edPtr = CRunNoise.cppLand.wasm_alloc(edSize);
        const edView = new DataView(CRunNoise.cppLand.memory.buffer, edPtr, edSize);

        // extHeader
        edView.setUint32(0, edSize, true);
        edView.setUint32(4, edSize, true);
        edView.setUint32(8, version, true);
        edView.setUint32(12, this.ho!.hoIdentifier, true);
        edView.setUint32(16, this.ho!.privateData, true);

        for (let i = 20; i < edSize; i++) {
            edView.setUint8(i, file.readAByte());
        }

        this.cppExtPtr = CRunNoise.cppLand.createRunObject(edPtr, 0, version);

        CRunNoise.cppLand.wasm_free(edPtr);
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
        if(this.cppExtPtr === null) return 0;
        return CRunNoise.cppLand.handleRunObject(this.cppExtPtr);
    }

    // Destruction of the object
    // ---------------------------------------------------------------
    // Called when the object is actually destroyed. This will always be
    // after the main game loop, and out of the actions processing : the
    // destroy process is queued until the very end of the game loop.
    destroyRunObject(bFast: boolean) {
        if(this.cppExtPtr === null) return;
        CRunNoise.cppLand.destroyRunObject(this.cppExtPtr, bFast);
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
        if(this.cppExtPtr === null) return;
        CRunNoise.cppLand.displayRunObject(this.cppExtPtr);
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
        if(this.cppExtPtr === null) return;
        CRunNoise.cppLand.pauseRunObject(this.cppExtPtr);
    }

    // Get the object out of pause mode
    // -----------------------------------------------------------------
    // Called when the game quits pause mode.
    continueRunObject() {
        if(this.cppExtPtr === null) return;
        CRunNoise.cppLand.continueRunObject(this.cppExtPtr);
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
        if(this.cppExtPtr === null) return false;

        CRunNoise.that = this;
        this.curConditionActionParams = cnd;
        this.wasmCStrings = [];

        const ret = CRunNoise.cppLand.conditionJump(this.cppExtPtr, num);

        this.wasmCStrings.forEach(strPtr => {
            CRunNoise.wasmCStringFree(strPtr);
        });

        return (ret == 1);
    }

    // Action entry
    // --------------------------------------------------------------
    // Called when an action of this object is executed
    //   - num : number of the action, as defined in the list on top of this source
    //   - act : a CActExtension object, allowing you to retreive the parameters
    //           of the action
    action(num: number, act: CActExtension) {
        if(this.cppExtPtr === null) return;

        CRunNoise.that = this;
        this.curConditionActionParams = act;
        this.wasmCStrings = [];

        CRunNoise.cppLand.actionJump(this.cppExtPtr, num);

        this.wasmCStrings.forEach(strPtr => {
            CRunNoise.wasmCStringFree(strPtr);
        });
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
    expression(num: number): (number | string) {
        if(this.cppExtPtr === null) return 0;

        CRunNoise.that = this;
        this.curExpressionReturn = null;
        this.curExpressionParams = [];
        this.wasmCStrings = [];
        CRunNoise.cppLand.expressionJump(this.cppExtPtr, num);

        this.wasmCStrings.forEach(strPtr => {
            CRunNoise.wasmCStringFree(strPtr);
        });

        if(this.curExpressionReturn == null) {
            return 0;
        }
        return this.curExpressionReturn;
    }
}

// You are perfectly free to define any new class or global function in this code.
// Avoid using generic names, as they may clash with future extensions. The best
// option is to have a prefix specific to your name or object, inserted before the
// name of the class or functions.

// esbuild bundles everything in a way that nothing gets exposed to outside and nothing can conflict
// Expose extension class globaly.
(globalThis as any)["CRunNoise"] = CRunNoise;