// Typescript type declarations for clickteam's html runtime Extensions.js

// wasm file binary data
declare module "Extension.wasm" {
    let uint8array: Uint8Array;
    export default uint8array;
}


// FIXME: Stubs from Objects.js
declare class CRun {};
declare class CObject {
    hoIdentifier: number;
};
declare class CExtension extends CObject {
    privateData: number;
    getExpParam(): number | string;
};

// FIXME: Stubs from Renderer.js
declare class Renderer {};

// FIXME: Stubs from RunLoop.js
declare interface CCreateObjectInfo {};


// NOTE: CExtLoader is missing
// NOTE: CExtLoad is missing

declare class CRunExtension {
    constructor();

    init(hoPtr: object);

    getNumberOfConditions(): number;
    createRunObject(file: CFile, cob: CCreateObjectInfo, version: number): boolean;
    handleRunObject(): number;
    displayRunObject(renderer: Renderer, xDraw: number, yDraw: number);
    destroyRunObject(bFast: boolean);
    createFont();
    pauseRunObject();
    continueRunObject();
    getZoneInfos();

    condition(num: number, cnd: object): boolean;
    action(num: number, act: object);
    expression(num): (number | string);

    // FIXME:
    getRunObjectCollisionMask(flags: null): null;
    getRunObjectFont(): (object | null);
    setRunObjectFont(font: object, rc: object);
    getRunObjectTextColor(): number;
    setRunObjectTextColor(rgb: number);

    // FIXME
    autoResize();
    // FIXME
    forcePosition();

    ho: (CExtension | null);
    rh: (CRun | null);

    static REFLAG_DISPLAY: number;
    static REFLAG_ONESHOT: number;
}

// NOTE: CExpExtension is missing

declare class CActExtension {
    constructor();

    execute(rhPtr: CRun);

    getParamObject(rhPtr: CRun, num: number): CObject;
    getParamBorder(rhPtr: CRun, num: number): number;                   // TODO: Verify the return.
    getParamShort(rhPtr: CRun, num: number): number;                    // TODO: Verify the return.
    getParamAltValue(rhPtr: CRun, num: number): number;                 // TODO: Verify the return.
    getParamDirection(rhPtr: CRun, num: number): number;                // TODO: Verify the return.
    getParamEffect(rhPtr: CRun, num: number): string;
    getParamCreate(rhPtr: CRun, num: number): object;                   // Not implemented?
    getParamAnimation(rhPtr: CRun, num: number): number;
    getParamPlayer(rhPtr: CRun, num: number): number;
    getParamEvery(rhPtr: CRun, num: number): number
    getParamKey(rhPtr: CRun, num: number): number;
    getParamSpeed(rhPtr: CRun, num: number): number;
    getParamPosition(rhPtr: CRun, num: number): CPositionInfo;
    getParamJoyDirection(rhPtr: CRun, num: number): number;
    getParamShoot(rhPtr: CRun, num: number): object;                    // Not implemented?
    getParamZone(rhPtr: CRun, num: number): PARAM_ZONE;
    getParamExpression(rhPtr: CRun, num: number): (number | string);
    getParamColour(rhPtr: CRun, num: number): number;
    getParamFrame(rhPtr: CRun, num: number): number;
    getParamNewDirection(rhPtr: CRun, num: number): number;
    getParamClick(rhPtr: CRun, num: number): number;
    getParamExpString(rhPtr: CRun, num: number): string;
    getParamFilename(rhPtr: CRun, num: number): string;
    getParamExpDouble(rhPtr: CRun, num: number): number;
    getParamFilename2(rhPtr: CRun, num: number): string;
    getParamExtension(rhPtr: CRun, num: number): (object | null);       // What?
    getParamTime(rhPtr: CRun, num: number): number;
}

declare class CCndExtension {
    constructor();

    eva1(rhPtr, pHo): boolean;
    eva2(rhPtr): boolean;

    getParamObject(rhPtr: CRun, num: number): CObject;
    getParamTime(rhPtr: CRun, num: number): number;
    getParamBorder(rhPtr: CRun, num: number): number;                   // TODO: Verify the return.
    getParamAltValue(rhPtr: CRun, num: number): number;                 // TODO: Verify the return.
    getParamDirection(rhPtr: CRun, num: number): number;                // TODO: Verify the return.
    getParamAnimation(rhPtr: CRun, num: number): number;
    getParamPlayer(rhPtr: CRun, num: number): number;
    getParamEvery(rhPtr: CRun, num: number): number
    getParamKey(rhPtr: CRun, num: number): number;
    getParamSpeed(rhPtr: CRun, num: number): number;
    getParamPosition(rhPtr: CRun, num: number): CPositionInfo;
    getParamJoyDirection(rhPtr: CRun, num: number): number;
    getParamExpression(rhPtr: CRun, num: number): (number | string);
    getParamColour(rhPtr: CRun, num: number): number;
    getParamFrame(rhPtr: CRun, num: number): number;
    getParamNewDirection(rhPtr: CRun, num: number): number;
    getParamClick(rhPtr: CRun, num: number): number;
    getParamExpString(rhPtr: CRun, num: number): string;

    compareValues(rhPtr: CRun, num: number, value: number): number;                // FIXME
    compareTime(rhPtr: CRun, num: number, t: number): number;
}