// Wasm gets embeded into .js file by esbuild, its stored in base64 and gets converted to UInt8Array.

// import wasm_file from "Extension.wasm"
// import {WASI, File, OpenFile, ConsoleStdout} from "@bjorn3/browser_wasi_shim";

// Typescript support is currently borked both for --instantiation sync and wit resources
// @ts-ignore
import * as WasmExt from "WasmExt";

import { environment, exit as exit$1, stderr, stdin, stdout, terminalInput, terminalOutput, terminalStderr, terminalStdin, terminalStdout } from '@bytecodealliance/preview2-shim/cli';
import { preopens, types } from '@bytecodealliance/preview2-shim/filesystem';
import { error, streams, poll } from '@bytecodealliance/preview2-shim/io';
import { tcp, udp } from '@bytecodealliance/preview2-shim/sockets';

// @ts-ignore
import CoreWasm1 from "../temp/WasmExt.core.wasm";
// @ts-ignore
import CoreWasm2 from "../temp/WasmExt.core2.wasm";
// @ts-ignore
import CoreWasm3 from "../temp/WasmExt.core3.wasm";
// @ts-ignore
import CoreWasm4 from "../temp/WasmExt.core4.wasm";

// FIXME: This should be generated from a template or something at build time

class ConditionOrActionManager {
    rh: CRun;
    cndOrAct: CCndExtension | CActExtension;

    constructor(rh: CRun, cndOrAct: CCndExtension | CActExtension) {
        this.rh = rh;
        this.cndOrAct = cndOrAct;
    }

    getInteger(index: number): number {
        return this.cndOrAct.getParamExpression(this.rh, index) as number;
    }

    getFloat(index: number): number {
        return this.cndOrAct.getParamExpression(this.rh, index) as number;
    }

    getString(index: number): string {
        return this.cndOrAct.getParamExpression(this.rh, index) as string;
    }

    getObject(index: number): number {
        return 0;   // stub
    }
}

class ExpressionManager {
    ho: CExtension;
    retValue: number | string | null = null;

    constructor(ho: CExtension) {
        this.ho = ho;
    }

    setInteger(val: number) {
        this.retValue = val;
    }

    setFloat(val: number) {
        this.retValue = val;
    }

    setString(val: string) {
        this.retValue = val;
    }

    getInteger(index: number): number {
        return this.ho.getExpParam() as number;
    }

    getFloat(index: number): number {
        return this.ho.getExpParam() as number;
    }

    getString(index: number): string {
        return this.ho.getExpParam() as string;
    }

    getObject(index: number): number {
        return 0;   // stub
    }

    getReturnValue(): number | string {
        return this.retValue!;
    }
}

const imports: WasmExt.ImportObject = {
    'wasi:cli/environment': environment,
    'wasi:cli/exit': exit$1,
    'wasi:cli/stderr': stderr,
    'wasi:cli/stdin': stdin,
    'wasi:cli/stdout': stdout,
    'wasi:cli/terminal-input': terminalInput,
    'wasi:cli/terminal-output': terminalOutput,
    'wasi:cli/terminal-stderr': terminalStderr,
    'wasi:cli/terminal-stdin': terminalStdin,
    'wasi:cli/terminal-stdout': terminalStdout,
    'wasi:clocks/wall-clock': {},
    'wasi:filesystem/preopens': preopens,
    'wasi:filesystem/types': types,
    'wasi:io/error': error,
    'wasi:io/poll': poll,
    'wasi:io/streams': streams,
    'wasi:sockets/tcp': tcp,
    'wasi:sockets/udp': udp,
    'condition-or-action-manager' : { default: ConditionOrActionManager },
    'expression-manager' : { default: ExpressionManager },
} as any;

let cppLand = WasmExt.instantiate(
    (path: string) => {
        switch (path) {
        case "WasmExt.core.wasm":
            return new WebAssembly.Module(CoreWasm1);
        case "WasmExt.core2.wasm":
            return new WebAssembly.Module(CoreWasm2);
        case "WasmExt.core3.wasm":
            return new WebAssembly.Module(CoreWasm3);
        case "WasmExt.core4.wasm":
            return new WebAssembly.Module(CoreWasm4);
        }
        throw "for some reason jco generates multiple core wasm modules from one wasm component, but with --instantiation sync it doesnt load them and embed them for me. WHY?????";
    },
    imports
)

cppLand.init();

// Prototype definition
// -----------------------------------------------------------------
// This class is a sub-class of CRunExtension, by the mean of the
// CServices.extend function which copies all the properties of
// the parent class to the new class when it is created.
// As all the necessary functions are defined in the parent class,
// you only need to keep the ones that you actually need in your code.
class CRunNoise extends CRunExtension {
    cppExtPtr: WasmExt.Extension | null = null;

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

        let editdata = new Uint8Array(edSize);
        const edView = new DataView(editdata.buffer);

        // extHeader
        edView.setUint32(0, edSize, true);
        edView.setUint32(4, edSize, true);
        edView.setUint32(8, version, true);
        edView.setUint32(12, this.ho!.hoIdentifier, true);
        edView.setUint32(16, this.ho!.privateData, true);

        for (let i = 20; i < edSize; i++) {
            edView.setUint8(i, file.readAByte());
        }

        this.cppExtPtr = cppLand.createRunObject(editdata, 0, version);
        console.log("createRunObject cppExtPtr: " + this.cppExtPtr);

        // CRunNoise.cppLand.wasm_free(edPtr);
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
        return cppLand.handleRunObject(this.cppExtPtr!);
    }

    // Destruction of the object
    // ---------------------------------------------------------------
    // Called when the object is actually destroyed. This will always be
    // after the main game loop, and out of the actions processing : the
    // destroy process is queued until the very end of the game loop.
    destroyRunObject(bFast: boolean) {
        cppLand.destroyRunObject(this.cppExtPtr!, bFast);
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
        cppLand.displayRunObject(this.cppExtPtr!);
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
        cppLand.pauseRunObject(this.cppExtPtr!);
    }

    // Get the object out of pause mode
    // -----------------------------------------------------------------
    // Called when the game quits pause mode.
    continueRunObject() {
        cppLand.continueRunObject(this.cppExtPtr!);
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
        let manager = new ConditionOrActionManager(this.rh!, cnd);

        const ret = cppLand.conditionJump(this.cppExtPtr!, num, manager);

        return (ret == 1);
    }

    // Action entry
    // --------------------------------------------------------------
    // Called when an action of this object is executed
    //   - num : number of the action, as defined in the list on top of this source
    //   - act : a CActExtension object, allowing you to retreive the parameters
    //           of the action
    action(num: number, act: CActExtension) {
        let manager = new ConditionOrActionManager(this.rh!, act);

        cppLand.actionJump(this.cppExtPtr!, num, manager);
        console.log("createRunObject cppExtPtr: " + this.cppExtPtr);
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
        let manager = new ExpressionManager(this.ho!);

        cppLand.expressionJump(this.cppExtPtr!, num, manager);

        return manager.getReturnValue();
    }
}

// You are perfectly free to define any new class or global function in this code.
// Avoid using generic names, as they may clash with future extensions. The best
// option is to have a prefix specific to your name or object, inserted before the
// name of the class or functions.

// esbuild bundles everything in a way that nothing gets exposed to outside and nothing can conflict
// Expose extension class globaly.
(globalThis as any)["CRunNoise"] = CRunNoise;