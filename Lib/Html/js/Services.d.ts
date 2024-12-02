// Typescript type declarations for clickteam's html runtime Services.js

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

// TODO:
// function CReplaceColor()
// {
// 	this.mode = 0;
// 	this.app = null;
// 	this.pImages = null;
// }
// CReplaceColor.prototype =
// {
// 	replaceColor: function (rhPtr, pHo, newColor, oldColor)
// 	{
// 		this.app = rhPtr.rhApp;

// 		// Changement des couleurs
// 		// ----------------------------------------------------------------------------
// 		var oi = pHo.hoOi;
// 		var poi = rhPtr.rhApp.OIList.getOIFromHandle(oi);
// 		if (poi == null)
// 			return;

// 		// Get image max
// 		this.dwMax = -1;
// 		this.mode = 0;
// 		poi.enumElements(this, null);

// 		// Rechercher le premier
// 		var pHoFirst = pHo;
// 		while ((pHoFirst.hoNumPrev & 0x80000000) == 0)
// 			pHoFirst = rhPtr.rhObjectList[pHoFirst.hoNumPrev & 0x7FFFFFFF];

// 		// Parcourir la liste
// 		do
// 		{
// 			if (pHoFirst.roc.rcImage != -1 && pHoFirst.roc.rcImage > this.dwMax)
// 				this.dwMax = pHoFirst.roc.rcImage;
// 			if (pHoFirst.roc.rcOldImage != -1 && pHoFirst.roc.rcOldImage > this.dwMax)
// 				this.dwMax = pHoFirst.roc.rcOldImage;

// 			// Le dernier?
// 			if ((pHoFirst.hoNumNext & 0x80000000) != 0)
// 				break;

// 			// Next OI
// 			pHoFirst = rhPtr.rhObjectList[pHoFirst.hoNumNext];

// 		} while (true);

// 		// Allocate memory
// 		this.pImages = new Array(this.dwMax + 1);
// 		var n;
// 		for (n = 0; n < this.dwMax + 1; n++)
// 		{
// 			this.pImages[n] = -1;
// 		}

// 		// List all images
// 		this.mode = 1;
// 		poi.enumElements(this, null);

// 		// Replace color in all images and create new images
// 		var i;
// 		var newImg;
// 		for (i = 0; i <= this.dwMax; i++)
// 		{
// 			if (this.pImages[i] == -1)
// 				continue;

// 			var sourceImg = rhPtr.rhApp.imageBank.getImageFromHandle(i);
// 			var destImg = CServices.performReplacement(rhPtr.rhApp, sourceImg, oldColor, newColor);
// 			if (destImg != null)
// 			{
// 				// Create new image in the bank
// 				this.pImages[i] = rhPtr.rhApp.imageBank.addImage(destImg);
// 			}
// 		}

// 		// Remplacer images dans les objets de m�me OI
// 		pHoFirst = pHo;
// 		while ((pHoFirst.hoNumPrev & 0x80000000) == 0)
// 			pHoFirst = rhPtr.rhObjectList[pHoFirst.hoNumPrev & 0x7FFFFFFF];

// 		// Parcourir la liste
// 		do
// 		{
// 			if (pHoFirst.roc.rcImage != -1 && this.pImages[pHoFirst.roc.rcImage] != -1)
// 			{
// 				pHoFirst.roc.rcImage = this.pImages[pHoFirst.roc.rcImage];
// 			}
// 			if (pHoFirst.roc.rcOldImage != -1 && this.pImages[pHoFirst.roc.rcOldImage] != -1)
// 			{
// 				pHoFirst.roc.rcOldImage = this.pImages[pHoFirst.roc.rcOldImage];
// 			}

// 			// Le dernier?
// 			if ((pHoFirst.hoNumNext & 0x80000000) != 0)
// 				break;
// 			// Next OI
// 			pHoFirst = rhPtr.rhObjectList[pHoFirst.hoNumNext];

// 		} while (true);

// 		this.mode = 2;
// 		poi.enumElements(this, null);

// 		// Replace old images by new ones
// 		this.mode = 3;
// 		poi.enumElements(this, null);

// 		// Mark OI to reload
// 		poi.oiLoadFlags |= COI.OILF_TORELOAD;
// 	},
// 	enumerate:    function (num)
// 	{
// 		switch (this.mode)
// 		{
// 			case 0:
// 				if (num > this.dwMax)
// 					this.dwMax = num;
// 				return -1;
// 			case 1:
// 				this.pImages[num] = 1;
// 				return -1;
// 			case 2:
// 				this.app.imageBank.delImage(num);
// 				return -1;
// 			case 3:
// 				var image = this.app.imageBank.getImageFromHandle(this.pImages[num]);
// 				image.useCount++;
// 				return this.pImages[num];
// 		}
// 		return -1;
// 	}
// }
// CServices.performReplacement = function (app, image, sourceColor, destColor)
// {
// 	var canvas = document.createElement("canvas");
// 	canvas.width = image.width;
// 	canvas.height = image.height;
// 	var context = canvas.getContext("2d");
// 	if (image.mosaic == 0)
// 	{
// 		context.drawImage(image.img, 0, 0);
// 	}
// 	else
// 	{
// 		context.drawImage(app.imageBank.mosaics[image.mosaic],
// 			image.mosaicX, image.mosaicY,
// 			image.width, image.height, 0, 0,
// 			image.width, image.height);
// 	}
// 	var imageData = context.getImageData(0, 0, image.width, image.height);
// 	var newR = (destColor >> 16) & 0xFF;
// 	var newG = (destColor >> 8) & 0xFF;
// 	var newB = destColor & 0xFF;
// 	var oldR = (sourceColor >> 16) & 0xFF;
// 	var oldG = (sourceColor >> 8) & 0xFF;
// 	var oldB = sourceColor & 0xFF;
// 	var index, x, y;
// 	for (y = 0; y < image.height; y++)
// 	{
// 		for (x = 0; x < image.width; x++)
// 		{
// 			index = (y * image.width + x) * 4;
// 			if (imageData.data[index] == oldR && imageData.data[index + 1] == oldG && imageData.data[index + 2] == oldB)
// 			{
// 				imageData.data[index] = newR;
// 				imageData.data[index + 1] = newG;
// 				imageData.data[index + 2] = newB;
// 			}
// 		}
// 	}
// 	context.putImageData(imageData, 0, 0);
// 	var newImage = new CImage();
// 	newImage.app = app;
// 	newImage.width = image.width;
// 	newImage.height = image.height;
// 	newImage.xSpot = image.xSpot;
// 	newImage.ySpot = image.ySpot;
// 	newImage.xAP = image.xAP;
// 	newImage.yAP = image.yAP;
// 	newImage.useCount = 0;
// 	newImage.img = canvas;
// 	newImage.maskNormal = image.maskNormal;
// 	newImage.maskPlatform = image.maskPlatform;
// 	newImage.maskRotation = image.maskRotation;

// 	return newImage;
// }

// // Graphic font
// // ---------------------------------------------------------
// CGraphicFont.FONTFLAG_ITALIC = 0x0001;
// CGraphicFont.FONTFLAG_UNDERLINE = 0x0002;
// CGraphicFont.FONTFLAG_BOLD = 0x0004;
// CGraphicFont.FLAG_PRIORITY = 0x0008;
// function CGraphicFont()
// {
// 	this.characters = null;
// 	this.width = 0;
// 	this.height = 0;
// 	this.image = null;
// 	this.color = 0;
// 	this.flags = 0;
// 	this.fontName = null;
// 	this.fontHeight = 0;
// 	this.fontFlags = 0;
// 	this.interline = 0;
// 	this.interchar = 0;
// 	this.nChars = 0;
// 	this.charWidths = null;
// 	this.isGraphic = true;
// }

// CGraphicFont.prototype =
// {
// 	compareFont: function (font)
// 	{
// 		if (this.fontName != font.lfFaceName)
// 			return false;
// 		if (this.fontHeight != font.lfHeight)
// 			return false;
// 		var b1 = (this.fontFlags & CGraphicFont.FONTFLAG_ITALIC) != 0;
// 		var b2 = (font.lfItalic) != 0;
// 		if (b1 != b2)
// 			return false;
// 		b1 = (this.fontFlags & CGraphicFont.FONTFLAG_BOLD) != 0;
// 		b2 = (font.lfWeight) > 400;
// 		if (b1 != b2)
// 			return false;
// 		return true;
// 	},

// 	getHeight: function () {
// 	    return this.height + this.interline;
// 	},

// 	measureText: function (s)
// 	{
// 		var w = 0;
// 		var l = s.length;
// 		var n, index;
// 		for (n = 0; n < l; n++)
// 		{
// 			index = this.characters.indexOf(s.charAt(n));
// 			if (index >= 0)
// 			{
// 				w += this.charWidths[index] + this.interchar;
// 			}
// 			else
// 			{
// 				w += this.width;
// 			}
// 		}
// 		return w;
// 	},

// 	measureChar: function (c)
// 	{
// 		var w;
// 		var index = characters.indexOf(String.fromCharCode(c));
// 		if (index >= 0)
// 			w = this.charWidths[index] + this.interchar;
// 		else
// 			w = this.width;
// 		return w;
// 	},

// 	fillText: function (context, s, x, y)
// 	{
// 		var l = s.length;
// 		var n, xs, ys, index, col, line, c;

// 		var image = this.image;

// 		if ((this.flags & CGraphicFont.FLAG_PRIORITY) == 0)
// 		{
// 			for (n = 0; n < l; n++)
// 			{
// 				index = this.characters.indexOf(s.charAt(n));
// 				if (index >= 0)
// 				{
// 					line = Math.floor(index / this.nChars);
// 					col = index - (line * this.nChars);
// 					ys = line * (this.height + 1);
// 					xs = col * (this.width + 1);

// 					if (image.mosaic == 0)
// 					{
// 					    context.drawImage(image.img, xs, ys, this.width, this.height, Math.round(x), Math.round(y), this.width, this.height);
// 					}
// 					else
// 					{
// 						context.drawImage(image.app.imageBank.mosaics[image.mosaic],
// 							xs + image.mosaicX, ys + image.mosaicY, this.width, this.height,
// 							Math.round(x), Math.round(y), this.width, this.height);
// 					}
// 					x += this.charWidths[index] + this.interchar;
// 				}
// 				else
// 				{
// 					context.fillStyle = CServices.getColorString(this.color);
// 					context.fillRect(x, y, this.width, this.height);
// 					x += this.width;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			x += this.measureText(s);
// 			for (n = l - 1; n >= 0; n--)
// 			{
// 				index = this.characters.indexOf(s.charAt(n));
// 				if (index >= 0)
// 				{
// 					x -= (this.charWidths[index] + this.interchar);
// 					line = index / this.nChars;
// 					col = index - (line * this.nChars);
// 					ys = line * (this.height + 1);
// 					xs = col * (this.width + 1);
// 					if (image.mosaic == 0)
// 					{
// 					    context.drawImage(image.img, xs, ys, this.width, this.height, Math.round(x), Math.round(y), this.width, this.height);
// 					}
// 					else
// 					{
// 						context.drawImage(image.app.imageBank.mosaics[image.mosaic],
// 							xs + image.mosaicX, ys + image.mosaicY, this.width, this.height,
// 							Math.round(x), Math.round(y), this.width, this.height);
// 					}
// 				}
// 				else
// 				{
// 					x -= this.width;
// 					context.fillStyle = CServices.getColorString(this.color);
// 					context.fillRect(x, y, this.width, this.height);
// 				}
// 			}
// 		}
// 	}
// }

// // OBJECT SELECTION CLASS
// // ------------------------------------------------------------------------------
// function ObjectSelection(runApp)
// {
// 	this.rhPtr = runApp;
// 	this.run = this.rhPtr.run;
// 	this.eventProgram = this.run.rhEvtProg;
// 	this.ObjectList = this.run.rhObjectList;				//get a pointer to the mmf object list
// 	this.OiList = this.run.rhOiList;						//get a pointer to the mmf object info list
// 	this.QualToOiList = this.eventProgram.qualToOiList;	//get a pointer to the mmf qualifier to Oi list
// }
// ObjectSelection.prototype =
// {
// 	//Selects *all* objects of the given object-type
// 	selectAll:                 function (OiList)
// 	{
// 		var pObjectInfo = this.OiList[OiList];
// 		pObjectInfo.oilNumOfSelected = pObjectInfo.oilNObjects;
// 		pObjectInfo.oilListSelected = pObjectInfo.oilObject;
// 		pObjectInfo.oilEventCount = this.eventProgram.rh2EventCount;

// 		var i = pObjectInfo.oilObject;
// 		while ((i & 0x80000000) == 0)
// 		{
// 			var pObject = this.ObjectList[i];
// 			pObject.hoNextSelected = pObject.hoNumNext;
// 			i = pObject.hoNumNext;
// 		}
// 	},

// 	//Resets all objects of the given object-type
// 	selectNone:                function (OiList)
// 	{
// 		var pObjectInfo = this.OiList[OiList];
// 		if (pObjectInfo == null)
// 			return;
// 		pObjectInfo.oilNumOfSelected = 0;
// 		pObjectInfo.oilListSelected = -1;
// 		pObjectInfo.oilEventCount = this.eventProgram.rh2EventCount;
// 	},

// 	//Resets the SOL and inserts only one given object
// 	selectOneObject:           function (object)
// 	{
// 		var pObjectInfo = object.hoOiList;
// 		pObjectInfo.oilNumOfSelected = 1;
// 		pObjectInfo.oilEventCount = this.eventProgram.rh2EventCount;
// 		pObjectInfo.oilListSelected = object.hoNumber;
// 		this.ObjectList[object.hoNumber].hoNextSelected = -1;
// 	},

// 	//Resets the SOL and inserts the given list of objects
// 	selectObjects:             function (OiList, objects)
// 	{
// 		var pObjectInfo = this.OiList[OiList];

// 		if (pObjectInfo == null)
// 			return;

// 		pObjectInfo.oilNumOfSelected = objects.length;
// 		pObjectInfo.oilEventCount = eventProgram.rh2EventCount;

// 		if (objects.length == 0)
// 			return;

// 		var i = 0;
// 		var prevNumber = objects[i].hoNumber;
// 		pObjectInfo.oilListSelected = prevNumber;
// 		while (i < objects.length)
// 		{
// 			currentNumber = objects[i++].hoNumber;
// 			this.ObjectList[prevNumber].hoNextSelected = currentNumber;
// 			prevNumber = currentNumber;
// 		}
// 		this.ObjectList[prevNumber].hoNextSelected = -1;
// 	},

// 	//Run a custom filter on the SOL (via function callback)
// 	filterObjects:             function (rdPtr, OiList, negate, filter)
// 	{
// 		if ((OiList & 0x8000) != 0)
// 		{
// 			return ((this.filterQualifierObjects(rdPtr, OiList & 0x7FFF, negate, filter) ? 1 : 0) ^ (negate ? 1 : 0)) != 0;
// 		}
// 		return ((this.filterNonQualifierObjects(rdPtr, OiList, negate, filter) ? 1 : 0) ^ (negate ? 1 : 0)) != 0;
// 	},

// 	//Filter qualifier objects
// 	filterQualifierObjects:    function (rdPtr, OiList, negate, filter)
// 	{
// 		var CurrentQualToOi = this.QualToOiList[OiList];

// 		var hasSelected = false;
// 		var i = 0;

// 		while (i < CurrentQualToOi.qoiList.length)
// 		{
// 			var CurrentOi = CurrentQualToOi.qoiList[i + 1];
//             if (CurrentOi < 0)
//                 break;
// 			hasSelected = (((hasSelected ? 1 : 0) |
// 				(this.filterNonQualifierObjects(rdPtr, CurrentOi, negate, filter) ? 1 : 0))) != 0;

// 			i += 2;
// 		}
// 		return hasSelected;
// 	},

// 	//Filter normal objects
// 	filterNonQualifierObjects: function (rdPtr, OiList, negate, filter)
// 	{
// 		var pObjectInfo = this.OiList[OiList];
// 		if (pObjectInfo == null)
// 			return false;
// 		var hasSelected = false;
// 		if (pObjectInfo.oilEventCount != this.eventProgram.rh2EventCount)
// 		{
// 			this.selectAll(OiList);	//The SOL is invalid, must reset.
// 		}

// 		//If SOL is empty
// 		if (pObjectInfo.oilNumOfSelected <= 0)
// 		{
// 			return false;
// 		}

// 		var firstSelected = -1;
// 		var count = 0;
// 		var current = pObjectInfo.oilListSelected;
// 		var previous = null;

// 		while ((current & 0x80000000) == 0)
// 		{
// 			var pObject = this.ObjectList[current];
// 			var filterResult = filter(rdPtr, pObject);
// 			var useObject = ((filterResult ? 1 : 0) ^ (negate ? 1 : 0)) != 0;
// 			hasSelected = ((hasSelected ? 1 : 0) | (useObject ? 1 : 0)) != 0;

// 			if (useObject)
// 			{
// 				if (firstSelected == -1)
// 				{
// 					firstSelected = current;
// 				}

// 				if (previous != null)
// 				{
// 					previous.hoNextSelected = current;
// 				}

// 				previous = pObject;
// 				count++;
// 			}
// 			current = pObject.hoNextSelected;
// 		}
// 		if (previous != null)
// 		{
// 			previous.hoNextSelected = -1;
// 		}

// 		pObjectInfo.oilListSelected = firstSelected;
// 		pObjectInfo.oilNumOfSelected = count;

// 		return hasSelected;
// 	},

// 	//Return the number of selected objects for the given object-type
// 	getNumberOfSelected:       function (OiList)
// 	{
// 		if ((OiList & 0x8000) != 0)
// 		{
// 			OiList &= 0x7FFF;	//Mask out the qualifier part
// 			var numberSelected = 0;

// 			var CurrentQualToOi = this.QualToOiList[OiList];

// 			var i = 0;
// 			while (i < CurrentQualToOi.qoiList.length)
// 			{
//                 var noil = CurrentQualToOi.qoiList[i + 1];
//                 if (noil < 0)
//                     break;
//                 var CurrentOi = this.OiList[noil];
// 				numberSelected += CurrentOi.oilNumOfSelected;
// 				i += 2;
// 			}
// 			return numberSelected;
// 		}
// 		else
// 		{
// 			var pObjectInfo = this.OiList[OiList];
// 			return pObjectInfo.oilNumOfSelected;
// 		}
// 	},

// 	objectIsOfType: function (obj, OiList)
// 	{
// 		if ((OiList & 0x8000) != 0)
// 		{
// 			OiList &= 0x7FFF;	//Mask out the qualifier part
// 			var CurrentQualToOi = this.QualToOiList[OiList];

// 			var i = 0;
// 			while (i < CurrentQualToOi.qoiList.length)
// 			{
//                 var noil = CurrentQualToOi.qoiList[i + 1];
//                 if (noil < 0)
//                     break;
//                 var CurrentOi = this.OiList[noil];
// 				if (CurrentOi.oilOi == obj.hoOi)
// 					return true;
// 				i += 2;
// 			}
// 			return false;
// 		}
// 		return (obj.hoOi == this.OiList[OiList].oilOi);
// 	},

// 	//Returns the object-info structure from a given object-type
// 	GetOILFromOI:   function (Oi)
// 	{
// 		for (i = 0; i < this.run.rhMaxOI; ++i)
// 		{
// 			var oil = this.OiList[i];
// 			if (oil.oilOi == Oi)
// 				return oil;
// 		}
// 		return null;
// 	}
// }


// // function decode_b64(d,b,c,u,r,q,x){b="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";for(r=q=x='';c=d.charAt(x++);~c&&(u=q%4?u*64+c:c,q++%4)?r+=String.fromCharCode(255&u>>(-2*q&6)):0)c=b.indexOf(c);return r}
// // function encode_b64(a,b,c,d,e,f){b="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";c="=";for(d=f='';e&=3,a.charAt(d++)||(b='=',e);f+=b.charAt(63&c>>++e*2))c=c<<8|a.charCodeAt(d-=!e);return f}


// //----------------------------------------------------------------------------------
// //
// // CTokenizer
// //
// //----------------------------------------------------------------------------------
// function CTokenizer(text, delimiter) {
//     this.tokens = new CArrayList();

//     var oldPos = 0;
//     var pos = text.indexOf(delimiter);

//     // Special case: if delimiter = \n, then remove \r from end of tokens
//     if (delimiter.length == 1 && delimiter.charCodeAt(0) == 10) {
//         while (pos >= 0) {
//             if (pos > oldPos) {
//                 var str = text.substring(oldPos, pos);
//                 if (str.length > 0 && str.charCodeAt(str.length - 1) == 13)
//                     str = str.substr(0, str.length - 1);
//                 this.tokens.add(str);
//             }
//             oldPos = pos + delimiter.length;
//             pos = text.indexOf(delimiter, oldPos);
//         }

//         if (text.length > oldPos) {
//             var str = text.substring(oldPos, text.length);
//             if (str.length > 0 && str.charCodeAt(str.length - 1) == 13)
//                 str = str.substr(0, str.length - 1);
//             this.tokens.add(str);
//         }
//     }
//     else {
//         while (pos >= 0) {
//             if (pos > oldPos) {
//                 this.tokens.add(text.substring(oldPos, pos));
//             }
//             oldPos = pos + delimiter.length;
//             pos = text.indexOf(delimiter, oldPos);
//         }

//         if (text.length > oldPos) {
//             this.tokens.add(text.substring(oldPos, text.length));
//         }
//     }

//     this.numToken = 0;
// }
// CTokenizer.prototype =
// {
//     countTokens: function () {
//         return this.tokens.size();
//     },
//     nextToken: function () {
//         if (this.numToken < this.tokens.size()) {
//             var s = this.tokens.get(this.numToken++);
//             if (s == null) {
//                 return "";
//             }
//             return s;
//         }
//         return "";
//     }
// }