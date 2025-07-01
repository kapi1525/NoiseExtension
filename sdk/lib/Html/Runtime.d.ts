// Typescript type declarations for clickteam's html runtime
// NOTE: A lot of things are missing or are stubs.
//       This is here only to add at leas some type safety to this.
// Extensions.js

// wasm file binary data
declare module "Extension.wasm" {
    let uint8array: Uint8Array;
    export default uint8array;
}

// FIXME: Compile time errors


// FIXME: Stubs from Objects.js
declare class CRun {};
declare class CObject {
    hoIdentifier: number;
};
declare class CExtension extends CObject {
    ext: CRunExtension;
    hoIdentifier: number;
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

    getParamObject(rhPtr: CRun, num: number): CExtension;
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

// Services.js

declare namespace CServices {
    function extend(top: object, bot: object): object;
    function HIWORD(ul: number): number;
    function LOWORD(ul: number): number;
    function MAKELONG(lo: number, hi: number): number;
    function getRValueFlash(rgb: number): number;
    function getGValueFlash(rgb: number): number;
    function getBValueFlash(rgb: number): number;
    function RGBFlash(r: number, g: number, b: number): number
    function swapRGB(rgb: number): number;
    function clamp(val: number, a: number, b: number): number;
    function getColorString(rgb: number): string;
    function floatToInt(value: number): number;
    function approximateInt(value: number): number;
    function isInt(value: number): number;
    // FIXME: whats context?
    function createEllipse(ctx: object, x: number, y: number, w: number, h: number);
    // FIXME: rc?
    function drawRect(context: object, rc: object);
    function drawLine(context: object, x1: number, y1: number, x2: number, y2: number);
    function formatDiscName(number: number, extension: string): string;
    function compareStringsIgnoreCase(string1: string, string2: string): boolean;
    function parseName(name: string): string;

    const MAX_HEIGHTS: number;
    const aHeightNormalToLF: number[];

    function heightNormalToLF(height: number): number;

    const DT_LEFT: number;
    const DT_TOP: number;
    const DT_CENTER: number;
    const DT_RIGHT: number;
    const DT_BOTTOM: number;
    const DT_VCENTER: number;
    const DT_SINGLELINE: number;
    const DT_CALCRECT: number;
    const DT_VALIGN: number;

    // FIXME:
    function drawText(context: object, s: object, flags: object, rc: object, font: object, displayArray: object): number;

    // Private?
    let xPos: (number | null);
    //CServices.fontHeight = 0;

    // FIXME:
    function drawIt(context: object, s: object, flags: object, rc: object, displayArray: object, font: object): number;
    function displayText(context: object, x: object, y: object, displayArray: object, font: object, color: object, effect: object, effectParam: object);

    // FIXME: Flags
    function intToString(value: number, displayFlags: number): string;
    function doubleToString(value: number, displayFlags: number): string;

    function subtractFilename(destination: string, source: string): string;
}

declare interface CDisplayText {
    x: number;
    y: number;
    text: s;
}

declare class CFile {
    constructor();
	readUnsignedByte(): number;
	getChecksum(): number;
    // FIXME: Callback
	getFile(fileName: string, callback: () => void, size: number);
    // FIXME: parrent
	openFileASync(fileName: string, parent: object);
	getBytes(): string;
    // FIXME: what?
	setBinary(binary: object): number;
	createFromFile(offset: number, length: number): CFile;

	getLength(): number;
	setUnicode(unicode: boolean);
	detectUnicode();
	skipBytes(skip: number)
	adjustTo8()
	isEOF(): boolean
	readInString(len: number): string;
	readAByte(): number;
	readAShort(): number;
	readShort(): number;
	readAChar(): number;
	readACharArray(size: number): number;
	readAInt(): number;
	readAColor(): number;
	readAFloat(): number;
	readADouble(): number;
	readAString(length: number): string;
	readAStringEOL(): string;
	skipAString(): string;
	getFilePointer(): number;
	seek(pos: number);
	skipBack(n: number);
	readBytesAsArray(a: object);
	readBuffer(size: number): Array;
	readLogFont(): CFontInfo;
	readLogFont16(): CFontInfo;

    ccfBytes: string;
    pointer: number;
    offset: number;
    bUnicode: boolean;
}

declare class CArrayList {
	add(o: object);
	isEmpty(): boolean;
	insert(index: number, o: object);
	get(index: nuber): (object | null);
	put(index: number, o: object);
	set(index: number, o: object);
	removeIndex(index: number);
	indexOf(o: object): number;
	contains(o: object): boolean;
	removeObject(o: object);
	size(): number;
	clear();
    // FIXME: callback
	sort(callback: () => void);

    array: Array;
}

declare class CRect {
    constructor(l: number, t: number, r: number, b: number);

	load(file: CFile);
	copyRect(srce: CRect);
	ptInRect(x: number, y: number);
	intersectRect(rc: CRect);

    left: number;
    top: number;
    right: number;
    bottom: number;
}

declare interface CPoint {
	x: number;
	y: number;
}

declare interface CZone {
	x1: number;
	y1: number;
	x2: number;
	y2: number;
}

declare class CFontInfo {
	copy(f: CFontInfo);
	getFont(): string;
	getHeight(): number;
	init();
	readLogFont(file: CFile);
	readLogFont16(file: CFile);

	lfHeight: number;
	lfWeight: number;
	lfItalic: number;
	lfFaceName: string;
	isGraphic: boolean;
}

declare class CIni {
    constructor(a: APP, flags: number);

    saveIni();
    loadIni(fileName: string);
    decodeUtf8(utftext: string): string;
    findSection(sectionName: string): number;
    findKey(l: string, keyName: string): number;
    getPrivateProfileString(sectionName: string, keyName: string, defaultString: string, fileName: string): string;
    writePrivateProfileString(sectionName: string, keyName: string, name: string, fileName: string);
    deleteItem(group: string, item: string, iniName: string);
    deleteGroup(group: string, iniName: string);

    static separator: string;
    static INIFLAG_UTF8: number;
    static INIFLAG_UTF16: number;

	app: APP;
	flags: number;
	strings: CArrayList;
	currentFileName: (string | null);
}

declare class CTextSurface {
    constructor(a: APP, w: number, h: number);

    measureText(text: string, font: string): number;
    setText(text: string, dtflags: number, rectangle: CRect, font: string, color: number): number;
    manualClear(color: number);
    manualDrawText(s: string, flags: number, rect: CRect, color: number, font: string, relief: number, color2: number);
    resize(w: number, h: number);
    // FIXME: Context
    draw(context: object, x: number, y: number, inkEffect: string, inkEffectParam: string);

	app: APP;
	width: number;
	height: number;
	canvas: HTMLCanvasElement;
	canvasContext: CanvasRenderingContext2D;
}

declare interface BrowserDetectEntry {
    string: string;
    subString: string;
    identity: string;
    versionSearch?: string;
}

declare class BrowserDetect {
    constructor();

    // FIXME: Verify
    searchString(data: BrowserDetectEntry[]): string;
    searchVersion(dataString: string): (void | number);

    static dataBrowser: BrowserDetectEntry[];
    static dataOS: BrowserDetectEntry[];

    isOpera: boolean;
    isFirefox: boolean;
    isSafari: boolean;
    isIE: boolean;
    isEdge: boolean;
    isChrome: boolean;
    isEdgeChromium: boolean;
    browser: string;
    version: string;
    OS: string;
}

declare interface CActReplaceColor {
    // FIXME:
	mode: (number | null);
	dwMax: (object | null);
	pImages: (object | null);
	pRh: (object | null);
}

declare class CReplaceColor {
    mode: (number | null)
    app: (APP | null)
    pImages: (object | null)
}
