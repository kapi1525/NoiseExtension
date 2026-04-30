// Typescript type declarations for clickteam's html runtime

// wasm file binary data
declare module "Extension.wasm" {
    const uint8array: Uint8Array<ArrayBuffer>;
    export default uint8array;
}


// Stubs

declare interface CCreateObjectInfo {}
declare class CExtension {
    hoIdentifier: number;
    privateData: number;
    ext: CRunExtension;

    getExpParam(): number | string;
}
declare class CRun {}

// Services.js Build 295.10

declare namespace CServices {
    function extend(top: any, bot: any): any;
    function HIWORD(ul: number): number;
    function LOWORD(ul: number): number;
    function MAKELONG(lo: number, hi: number): number;
    function getRValueFlash(rgb: number): number;
    function getGValueFlash(rgb: number): number;
    function getBValueFlash(rgb: number): number;
    function RGBFlash(r: number, g: number, b: number): number;
    function swapRGB(rgb: number): number;
    function clamp(val: number, a: number, b: number): number;
    function getColorString(rgb: number): string;
    function floatToInt(value: number): number;
    function approximateInt(value: number): number;
    function isInt(value: number): number;
    function createEllipse(ctx: any, x: number, y: number, w: number, h: number): void;
    function drawRect(context: any, rc: any): void;
    function drawLine(context: any, x1: number, y1: number, x2: number, y2: number): void;
    function formatDiscName(number: number, extension: any): string;
    function compareStringsIgnoreCase(string1: string, string2: string): boolean;
    function parseName(name: string): string;

    const MAX_HEIGHTS = 40;
    const aHeightNormalToLF: number[];

    function heightNormalToLF(height: number): number;

    const DT_LEFT = 0x0000;
    const DT_TOP = 0x0000;
    const DT_CENTER = 0x0001;
    const DT_RIGHT = 0x0002;
    const DT_BOTTOM = 0x0008;
    const DT_VCENTER = 0x0004;
    const DT_SINGLELINE = 0x0020;
    const DT_CALCRECT = 0x0400;
    const DT_VALIGN = 0x0800;

    function drawText(context: any, s: string, flags: any, rc: any, font: any, displayArray: any): number;

    let xPos: number | null;

    function drawIt(context: any, s: string, flags: any, rc: any, displayArray: any, font: any): number;
    function displayText(context: any, x: number, y: number, displayArray: any, font: any, color: number, effect: any, effectParam: any): void;
    function intToString(value: number, displayFlags: any): string;
    function doubleToString(value: number, displayFlags: any): string;
    function subtractFilename(destination: string, source: string): string;

    function performReplacement(app: any, image: any, sourceColor: any, destColor: any): any;
}

declare class CDisplayText {
    constructor(xx: number, yy: number, s: string)

    x: number;
    y: number;
    text: string;
}

declare class CFile {
    constructor();

    ccfBytes: string;
    pointer: number;
    offset: number;
    bUnicode: boolean;

    readUnsignedByte(): number;
    getChecksum(): number;
    getFile(fileName: string, callback: any, size: number): void;
    openFileASync(fileName: string, parent: any): void;
    getBytes(): string;
    setBinary(binary: string): void;
    createFromFile(offset: number, length: number): CFile;
    getLength(): number;
    setUnicode(unicode: boolean): void;
    detectUnicode(): void;
    skipBytes(skip: number): void;
    adjustTo8(): void;
    isEOF(): boolean;
    readInString(len: number): string;
    readAByte(): number;
    readAShort(): number;
    readShort(): number;
    readAChar(): number;
    readACharArray(size: number): number[];
    readAInt(): number;
    readAColor(): number;
    readAFloat(): number;
    readADouble(): number;
    readAString(length: number): string;
    readAStringEOL(): string;
    skipAString(): void;
    getFilePointer(): number;
    seek(pos: number): void;
    skipBack(n: number): void;
    readBytesAsArray(a: any): void;
    readBuffer(size: number): number[];
    readLogFont(): any;
    readLogFont16(): any;
}

// TODO:
declare class CArrayList {}
declare class CRect {}
declare class CPoint {}
declare class CZone {}
declare class CFontInfo {}
declare class CIni {}
declare class CTextSurface {}
declare class BrowserDetect {}
declare class CActReplaceColor {}
declare class CReplaceColor {}
declare class CGraphicFont {}
declare class ObjectSelection {}
declare class CTokenizer {}



// Extensions.js Build 295.10

declare class CExtLoader {
    static readonly KPX_BASE: number; // 32
    app: any;
    extensions: any;
    numOfConditions: any;

    createList(file: any): void;
    addExt(e: any): void;
    loadRunObject(type: any): void;
    getNumberOfConditions(type: any): number;
}

declare class CExtLoad {
    handle: number;
    loadRunObject(): any | null;
}

declare class CRunExtension {
    static readonly REFLAG_DISPLAY: number; // 1
    static readonly REFLAG_ONESHOT: number; // 2

    ho: CExtension;
    rh: CRun;

    init(hoPtr: any): void;
    getNumberOfConditions(): number;
    createRunObject(file: any, cob: any, version: number): boolean;
    handleRunObject(): number;
    displayRunObject(context: any, xDraw: number, yDraw: number): void;
    destroyRunObject(bFast: boolean): void;

    createFont(): void;
    pauseRunObject(): void;
    continueRunObject(): void;
    getZoneInfos(): void;

    condition(num: number, cnd: CCndExtension): boolean;
    action(num: number, act: CActExtension): void;
    expression(num: number): number | string | null;

    getRunObjectCollisionMask(flags: any): any | null;
    getRunObjectFont(): any | null;
    setRunObjectFont(fi: any, rc: any): void;
    getRunObjectTextColor(): number;
    setRunObjectTextColor(rgb: number): void;
    autoResize(): void;
    forcePosition(): void;
}

declare class CExpExtension {
    evaluate(rhPtr: any): void;
}

declare class CActExtension {
    execute(rhPtr: any): void;

    getParamObject      (rhPtr: any, num: number): CExtension;
    getParamBorder      (rhPtr: any, num: number): any;
    getParamShort       (rhPtr: any, num: number): any;
    getParamAltValue    (rhPtr: any, num: number): any;
    getParamDirection   (rhPtr: any, num: number): any;
    getParamEffect      (rhPtr: any, num: number): any;
    getParamCreate      (rhPtr: any, num: number): any;
    getParamAnimation   (rhPtr: any, num: number): any;
    getParamPlayer      (rhPtr: any, num: number): any;
    getParamEvery       (rhPtr: any, num: number): any;
    getParamKey         (rhPtr: any, num: number): any;
    getParamSpeed       (rhPtr: any, num: number): any;
    getParamPosition    (rhPtr: any, num: number): any;
    getParamJoyDirection(rhPtr: any, num: number): any;
    getParamShoot       (rhPtr: any, num: number): any;
    getParamZone        (rhPtr: any, num: number): any;
    getParamExpression  (rhPtr: any, num: number): number | string;
    getParamColour      (rhPtr: any, num: number): any;
    getParamFrame       (rhPtr: any, num: number): any;
    getParamNewDirection(rhPtr: any, num: number): any;
    getParamClick       (rhPtr: any, num: number): any;
    getParamExpString   (rhPtr: any, num: number): any;
    getParamFilename    (rhPtr: any, num: number): any;
    getParamExpDouble   (rhPtr: any, num: number): any;
    getParamFilename2   (rhPtr: any, num: number): any;
    getParamExtension   (rhPtr: any, num: number): any;
    getParamTime        (rhPtr: any, num: number): any;
}

declare class CCndExtension {
    eva1(rhPtr: any, pHo: any): boolean;
    eva2(rhPtr: any): boolean;

    getParamObject      (rhPtr: any, num: number): any;
    getParamTime        (rhPtr: any, num: number): any;
    getParamBorder      (rhPtr: any, num: number): any;
    getParamAltValue    (rhPtr: any, num: number): any;
    getParamDirection   (rhPtr: any, num: number): any;
    getParamAnimation   (rhPtr: any, num: number): any;
    getParamPlayer      (rhPtr: any, num: number): any;
    getParamEvery       (rhPtr: any, num: number): any;
    getParamKey         (rhPtr: any, num: number): any;
    getParamSpeed       (rhPtr: any, num: number): any;
    getParamPosition    (rhPtr: any, num: number): any;
    getParamJoyDirection(rhPtr: any, num: number): any;
    getParamExpression  (rhPtr: any, num: number): number | string;
    getParamColour      (rhPtr: any, num: number): any;
    getParamFrame       (rhPtr: any, num: number): any;
    getParamNewDirection(rhPtr: any, num: number): any;
    getParamClick       (rhPtr: any, num: number): any;
    getParamExpString   (rhPtr: any, num: number): any;
    compareValues       (rhPtr: any, num: number, value: any): any;
    compareTime         (rhPtr: any, num: number, t: any): any;
}

/* Base for control extensions (James) */
declare class CRunControl extends CRunExtension {
    element: any | null;
    controlIgnoreHeight: boolean;
    bnShownOld: boolean;

    setElement(e: any, visible: boolean): void;
    getXOffset(): number;
    getYOffset(): number;
    setX(x: number): void;
    setY(y: number): void;
    setPosition(x: number, y: number): void;
    setWidth(width: number): void;
    setHeight(height: number): void;
    setSize(width: number, height: number): void;
    setFont(fontInfo: any): void;
}
