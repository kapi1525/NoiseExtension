// Wasm gets embeded into .js file by esbuild, its stored in base64 and gets converted to UInt8Array.
import wasm_file from "Noise.wasm"
import {WASI, File, OpenFile, ConsoleStdout} from "@bjorn3/browser_wasi_shim";


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
    handleRunObject?: () => void;
    displayRunObject?: () => void;
    pauseRunObject?: () => void;
    continueRunObject?: () => void;
    // ACE jumps
    confitionJump?: () => void;
    actionJump?: () => void;
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
        expression_manager: {
            set_value_int:          (a: number) => { CRunNoise.that.curExpressionReturn = a; },
            set_value_float:        (a: number) => { console.log("set_value_float" + a); CRunNoise.that.curExpressionReturn = a; },
            set_value_cstr:         (str_ptr: number) => { CRunNoise.that.curExpressionReturn = str_ptr; }, // FIXME
            get_float:              (index: number) => {
                if(CRunNoise.that.ho === null) {
                    return 0;
                }
                while (CRunNoise.that.curExpressionParams.length <= index) {
                    CRunNoise.that.curExpressionParams.push(CRunNoise.that.ho.getExpParam());
                }
                console.log("get_float index:" + index);
                console.log(CRunNoise.that.curExpressionParams[index])
                return CRunNoise.that.curExpressionParams[index];
            },
            get_string:             (index: number) => {
                return 0;
            },
            get_integer:            (index: number) => {
                if(CRunNoise.that.ho === null) {
                    return 0;
                }
                while (CRunNoise.that.curExpressionParams.length <= index) {
                    CRunNoise.that.curExpressionParams.push(CRunNoise.that.ho.getExpParam());
                }
                return CRunNoise.that.curExpressionParams[index];
            },
            // get_object:             () => {},
            set_return_type:        (rt: number) => {},
        },
        // TODO:
        // wasi_snapshot_preview1: {
        //     args_get:               () => { console.warn("stub"); },
        //     args_sizes_get:         () => { console.warn("stub"); },
        //     fd_close:               () => { console.warn("stub"); },
        //     fd_fdstat_get:          () => { console.warn("stub"); },
        //     fd_prestat_get:         () => { console.warn("stub"); },
        //     fd_prestat_dir_name:    () => { console.warn("stub"); },
        //     fd_seek:                () => { console.warn("stub"); },
        //     fd_write:               () => { console.warn("stub"); },
        //     proc_exit:              () => { console.warn("stub"); },
        // },
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

        expressionJump: CRunNoise.wasmInstance.exports.expressionJump as (ext: number, num: number) => void,
    };

    cppExtPtr: number | null = null;

    curExpressionReturn: number | string | null = null;
    curExpressionParams: (number | string)[] = [];
    static that: CRunNoise;

    // Constructor of the object.
    // ----------------------------------------------------------------
    // Called during the creation process of the object, but before any
    // initialization. You may want (although you can do it in CreateRunObject),
    // to instantiate variables.
    constructor() {
        super();

        // if(CRunNoise.wasmModule != null) {
        //     console.log("wasm already initialized.");
        //     return;
        // }

        CRunNoise.wasi.inst = CRunNoise.wasmInstance as any;

        console.log(CRunNoise.cppLand);
        console.log(CRunNoise.wasmInstance.exports);
        CRunNoise.cppLand.init();
    }

    // Returns the number of conditions
    // --------------------------------------------------------------------
    // Warning, if this number is not correct, the application _will_ crash
    getNumberOfConditions(): number {
        // const number = CRunNoise.cppLand.getNumberOfConditions();
        const number = 0;
        console.log(number);
        return number;
        // return CRunNoise.CND_LAST;
    }

    // Creation of the object
    // --------------------------------------------------------------------
    // - file : a CFile object, pointing to the object's data zone
    // - cob : a CCreateObjectInfo containing infos about the created object
    // - version : the version number of the object, as defined in the C code
    createRunObject(file: CFile, cob: CCreateObjectInfo, version: number): boolean {
        // console.log(file.getLength());
        // console.log(file.getBytes());
        // console.log(file.readBuffer(file.getLength()));
        // Use the "file" parameter to call the CFile object, and
        // gather the data of the object in the order as they were saved
        // (same order as the definition of the data in the EDITDATA structure
        // of the C code).
        // Examples :
        // this.myIntegerValue = file.readAInt();   Reads 4 bytes as a signed number
        // this.myShortValue = file.readAShort();   Reads 2 bytes as a unsigned number
        // this.myString = file.readAString();      Reads a string, ending by 0
        // this.myString = file.readAString(size);  Reads a string out of a given sized buffer
        //                                            - The string can end before the end of the buffer with a 0
        //                                            - If the string is as long as the buffer, it does not
        //                                              need to end by a 0
        //                                            > Whatever happens, this function will always position the file
        //                                              at the end of the buffer upon exit
        // this.myString = file.readAStringEOL();   Reads a string until a CR or a CR/LF (works with both)
        // this.myColor = file.readAColor();        Reads a RGB value
        // file.skipBytes(number);                  Skips a number of bytes in the file
        // Please report to the documentation for more information on the CFile object

        // The return value is not used in this version of the runtime but maybe later.
        // So please return false;

        let bytes = file.getBytes();

        console.log(file);

        const length_in_bytes = bytes.length;
        const wasm_edptr = CRunNoise.cppLand.wasm_alloc(length_in_bytes);

        const dv = new DataView(CRunNoise.cppLand.memory.buffer, wasm_edptr);
        for (let index = 0; index < length_in_bytes; index++) {
            dv.setInt8(index, file.readAByte());
        }

        this.cppExtPtr = CRunNoise.cppLand.createRunObject(wasm_edptr, 0, version);

        CRunNoise.cppLand.wasm_free(wasm_edptr);
        console.log("Allocating Extension ptr: " + this.cppExtPtr);
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
        return 0;       // The object will be called next loop
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
    }

    // Get the object out of pause mode
    // -----------------------------------------------------------------
    // Called when the game quits pause mode.
    continueRunObject() {
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
        // You usually do a switch statement from the "num" parameter
        // switch (num)
        // {
        //     // Dummy condition : true if the parameter is equal to 0
        //     case CRunNoise.CND_DUMMY:
        //         var parameter = cnd.getParamExpression(this.rh, 0);
        //         return (parameter == 0);

        //     // Dummy condition. Example of a condition called from within the object
        //     // by an action. Returns true if the parameter of the action is
        //     // equal to the parameter of the condition.
        //     case CRunNoise.CND_DUMMY2:
        //         var string = cnd.getParamExpString(this.rh, 0);
        //         var fromAction = this.rh.rhEvtProg.rhCurParam0;
        //         if (string == fromAction)
        //             return true;
        //         break;
        // }
        return false;
    }

    // Action entry
    // --------------------------------------------------------------
    // Called when an action of this object is executed
    //   - num : number of the action, as defined in the list on top of this source
    //   - act : a CActExtension object, allowing you to retreive the parameters
    //           of the action
    action(num: number, act: CActExtension) {
        // switch (num)
        // {
        //     // Dummy action : changes the position of the object
        //     case CRunNoise.ACT_DUMMY:
        //         var x = act.getParamExpression(this.rh, 0);
        //         var y = act.getParamExpression(this.rh, 1);
        //         this.setPosition(x, y);
        //         break;

        //     // Dummy action : calls the CND_DUMMY2 condition of this object
        //     case CRunNoise.ACT_DUMMY2;
        //         var string = act.getParamExpString(this.rh, 0);
        //         this.generateEvent(CRunNoise.CND_DUMMY2, string);
        //         break;
        // }
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
        CRunNoise.cppLand.expressionJump(this.cppExtPtr, num);
        // switch (num)
        // {
        //     // Dummy expression : adds the two parameters
        //     case CRunNoise.EXP_DUMMY:
        //         var param1 = this.ho.getExpParam();     // Get first parameter
        //         var param2 = this.ho.getExpParam();     // Get second parameter
        //         return param1 + param2;

        //     // Dummy expression : returns the length of a string
        //     case CRunNoise.EXP_DUMMY2:
        //         var string = this.ho.getExpParam();     // Get the string parameter
        //         return string.length;
        // }
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


(globalThis as any)["CRunNoise"] = CRunNoise;