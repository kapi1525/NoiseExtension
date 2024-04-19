// DarkEdit SDK for html but separated into another file
// SDK itself is under MIT license
// https://github.com/SortaCore/MMF2Exts/blob/4fbc2691e6a776bf8a513032d206739e33977e36/DarkEdif/DarkEdif%20Template/HTML5/DarkEdif_Template.js

// TODO: Merge common HTML and UWP parts

/* global console, darkEdif, alert, CRunExtension, CServices, window */
/* jslint esversion: 6, sub: true */

// This is strict, but that can be assumed
// "use strict";



/**
 * String.prototype.replaceAll() polyfill
 * https://gomakethings.com/how-to-replace-a-section-of-a-string-with-another-one-with-vanilla-js/
 * @author Chris Ferdinandi
 * @license MIT
 */
if (!String.prototype.replaceAll) {
    String.prototype.replaceAll = function(str, newStr) {
        // If a regex pattern
        if (Object.prototype.toString.call(str).toLowerCase() === '[object regexp]') {
            return this.replace(str, newStr);
        }

        // If a string
        return this.replace(new RegExp(str, 'g'), newStr);
    };
}

// Global data, including sub-applications, just how God intended.
// Note: This will allow newer SDK versions in later SDKs to take over.
// We need this[] and window[] instead of direct, because HTML5 Final Project minifies and breaks the names otherwise
// In case UWP is minified later, we'll keep these HTML5 minify precautions in UWP
export default window['darkEdif'] = (window['darkEdif'] && window['darkEdif'].sdkVersion >= 19) ? window['darkEdif'] :
    new (/** @constructor */ function() {
    this.data = {};
    this.getGlobalData = function (key) {
        key = key.toLowerCase();
        if (key in this.data) {
            return this.data[key];
        }
        return null;
    };
    this.setGlobalData = function (key, value) {
        key = key.toLowerCase();
        this.data[key] = value;
    };

    this.getCurrentFusionEventNumber = function (ext) {
        return ext.rh.rhEvtProg.rhEventGroup.evgLine || -1;
    };
    this.sdkVersion = 19;
    this.checkSupportsSDKVersion = function (sdkVer) {
        if (sdkVer < 16 || sdkVer > 19) {
            throw "UWP DarkEdif SDK does not support SDK version " + this.sdkVersion;
        }
    };

    // minifier will rename notMinified, so we can detect minifier simply
    this.minified = false;
    if (!this.hasOwnProperty('minified')) {
        this['minified'] = true;
    }

    this.consoleLog = function (ext, str) {
        // Log if DebugMode not defined, or true
        if (ext == null || ext['DebugMode'] == null || ext['DebugMode']) {
            // Exts will be renamed in minified
            if (this['minified'] && ext != null && ext['DebugMode'] == true) {
                console.warn("DebugMode left true for an extension in minified mode. Did the ext developer not set it false before distributing?");
                ext['DebugMode'] = false;
            }

            const extName = (ext == null || this['minified']) ? "Unknown DarkEdif ext" :
                ext['ExtensionName'] || ext.constructor.name.replaceAll('CRun', '').replaceAll('_',' ');
            console.log(extName + " - " + str);
        }
    };
    // UWP does not have FinalizationRegistry
    this.finalizer = { register: function(desc) { } };

    this['Properties'] = function(ext, edPtrFile, extVersion) {
        // DarkEdif SDK stores offset of DarkEdif props away from start of EDITDATA inside private data.
        // eHeader is 20 bytes, so this should be 20+ bytes.
        if (ext.ho.privateData < 20) {
            throw "Not smart properties - eHeader missing?";
        }
        // DarkEdif SDK header read:
        // header uint32, hash uint32, hashtypes uint32, numprops uint16, pad uint16, sizeBytes uint32 (includes whole EDITDATA)
        // then checkbox list, one bit per checkbox, including non-checkbox properties
        // so skip numProps / 8 bytes
        // then moving to Data list:
        // size uint32 (includes whole Data), propType uint16, propNameSize uint8, propname u8 (lowercased), then data bytes

        let header = new Uint8Array(edPtrFile.readBuffer(4 + 4 + 4 + 2 + 2 + 4));
        if (String.fromCharCode.apply('', [header[3], header[2], header[1], header[0]]) != 'DAR1') {
            throw "Did you read this.ho.privateData bytes?";
        }

        let headerDV = new DataView(header.buffer);
        this.numProps = headerDV.getUint16(4 + 4 + 4, true); // Skip past hash and hashTypes
        this.sizeBytes = headerDV.getUint32(4 + 4 + 4 + 4, true); // skip past numProps and pad

        let editData = edPtrFile.readBuffer(this.sizeBytes - header.byteLength);
        this.chkboxes = editData.slice(0, Math.ceil(this.numProps / 8));
        let that = this;
        let GetPropertyIndex = function(chkIDOrName) {
            if (typeof chkIDOrName == 'number') {
                if (that.numProps >= chkIDOrName) {
                    throw "Invalid property ID " + chkIDOrName + ", max ID is " + (that.numProps - 1) + ".";
                }
                return chkIDOrName;
            }
            const p = that.props.find(function(p) { return p.propName == chkIDOrName; });
            if (p == null) {
                throw "Invalid property name \"" + chkIDOrName + "\"";
            }
            return p.index;
        };
        this['IsPropChecked'] = function(chkIDOrName) {
            const idx = GetPropertyIndex(chkIDOrName);
            if (idx == -1) {
                return 0;
            }
            return (that.chkboxes[Math.floor(idx / 8)] & (1 << idx % 8)) != 0;
        };
        this['GetPropertyStr'] = function(chkIDOrName) {
            const idx = GetPropertyIndex(chkIDOrName);
            if (idx == -1) {
                return "";
            }
            const prop = that.props[idx];
            const textPropIDs = [
                5, // PROPTYPE_EDIT_STRING:
                22, // PROPTYPE_EDIT_MULTILINE:
                16, // PROPTYPE_FILENAME:
                19, // PROPTYPE_PICTUREFILENAME:
                26, // PROPTYPE_DIRECTORYNAME:
                7, // PROPTYPE_COMBOBOX:
                20, // PROPTYPE_COMBOBOXBTN:
                24 // PROPTYPE_ICONCOMBOBOX:
            ];
            if (textPropIDs.indexOf(prop.propTypeID) != -1) {
                let t = that.textDecoder.decode(prop.propData);
                if (prop.propTypeID == 22) //PROPTYPE_EDIT_MULTILINE
                    t = t.replaceAll('\r', ''); // CRLF to LF
                return t;
            }
            throw "Property " + prop.propName + " is not textual.";
        };
        this['GetPropertyNum'] = function(chkIDOrName) {
            const idx = GetPropertyIndex(chkIDOrName);
            if (idx == -1) {
                return 0.0;
            }
            const prop = that.props[idx];
            const numPropIDsInteger = [
                6, // PROPTYPE_EDIT_NUMBER
                9, // PROPTYPE_COLOR
                11, // PROPTYPE_SLIDEREDIT
                12, // PROPTYPE_SPINEDIT
                13 // PROPTYPE_DIRCTRL
            ];
            const numPropIDsFloat = [
                21, // PROPTYPE_EDIT_FLOAT
                27 // PROPTYPE_SPINEDITFLOAT
            ];
            if (numPropIDsInteger.indexOf(prop.propTypeID) != -1) {
                return new DataView(prop.propData.buffer).getUint32(0, true);
            }
            if (numPropIDsFloat.indexOf(prop.propTypeID) != -1) {
                return new DataView(prop.propData.buffer).getFloat32(0, true);
            }
            throw "Property " + prop.propName + " is not numeric.";
        };

        this.props = [];
        const data = editData.slice(this.chkboxes.length);
        const dataDV = new DataView(new Uint8Array(data).buffer);

        this.textDecoder = null;
        if (window['TextDecoder'] != null) {
            this.textDecoder = new window['TextDecoder']();
        }
        else {
            // one byte = one char - should suffice for basic ASCII property names
            this.textDecoder = {
                decode: function(txt) {
                    return String.fromCharCode.apply("", txt);
                }
            };
        }

        for (let i = 0, pt = 0, propSize, propEnd; i < this.numProps; ++i) {
            propSize = dataDV.getUint32(pt, true);
            propEnd = pt + propSize;
            const propTypeID = dataDV.getUint16(pt + 4, true);
            const propNameLength = dataDV.getUint8(pt + 4 + 2);
            pt += 4 + 2 + 1;
            const propName = this.textDecoder.decode(new Uint8Array(data.slice(pt, pt + propNameLength)));
            pt += propNameLength;
            const propData = new Uint8Array(data.slice(pt, pt + propSize - (4 + 2 + 1 + propNameLength)));

            this.props.push({ index: i, propTypeID: propTypeID, propName: propName, propData: propData });
            pt = propEnd;
        }
    };
})();