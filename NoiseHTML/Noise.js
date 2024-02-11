/*
    This Noise Fusion extension HTML5 port is under MIT license.

    Modification for purposes of tuning to your own HTML5 application is permitted, but must retain this notice and not be redistributed,
    outside of its (hopefully minified) presence inside your HTML5 website's source code.
*/

/* global console, darkEdif, globalThis, alert, CRunExtension, FinalizationRegistry, CServices */
/* jslint esversion: 6, sub: true */

// This is strict, but that can be assumed
// "use strict";

// webpack handles imports and bundles everything into single js file
// It seems like webpack handles everything in a smart way and names cant conflict with other extensions
import "DarkEdif";
import FastNoiseLite from "fastnoise-lite";


// Mixing new syntax with old closure, what could go wrong!
// NOTE: Closure seems to partialy support class syntax: class methods are supported but public, static member variables produce errors
export default class CRunNoise extends CRunExtension {
    constructor() {
        /// <summary> Constructor of Fusion object. </summary>
        super();    // Calls the parrent object constructor, inits ho with null

        // DarkEdif SDK exts should have these four variables defined.
        // We need this[] and globalThis[] instead of direct because HTML5 Final Project minifies and breaks the names otherwise
        this['ExtensionVersion'] = 23;      // To match C++ version
        this['SDKVersion'] = 18;            // To match C++ version
        this['DebugMode'] = true;
        this['ExtensionName'] = 'Noise';

        // Can't find DarkEdif wrapper
        if (!globalThis.hasOwnProperty('darkEdif')) {
            throw "a wobbly";
        }
        globalThis['darkEdif'].checkSupportsSDKVersion(this.SDKVersion);

        this.fnlNoise = null;
        this.fnlWarp = null;

        this.noiseSettings = {
            upperRange:         1.0,
            lowerRange:         -1.0,
            seed:               1337,
            type:               FastNoiseLite.NoiseType.OpenSimplex2,
            rotationType3D:     FastNoiseLite.RotationType3D.None,
            fractalType:        FastNoiseLite.FractalType.None,
            cellularFunction:   FastNoiseLite.CellularDistanceFunction.EuclideanSq,
            cellularReturnType: FastNoiseLite.CellularReturnType.Distance,
        };

        this.warpSettings = {
            enabled:            false,
            seed:               1337,
            type:               FastNoiseLite.DomainWarpType.OpenSimplex2,
            rotationType3D:     FastNoiseLite.RotationType3D.None,
            fractalType:        FastNoiseLite.FractalType.None,
        };

        // =============================
        // Function arrays
        // =============================

        this.$actionFuncs = [
            // 0
            this.setSeed,
            // 1
            (noiseType) => {
                this.setNoiseType(this.getNoiseTypeString(noiseType));
            },
            // 2
            (frequency) => {
                this.fnlNoise.SetFrequency(frequency);
            },
            // 3
            (fractalType) => {
                this.setFractalType(this.getFractalTypeString(fractalType));
            },
            // 4
            (fractalOctaves) => {
                this.fnlNoise.SetFractalOctaves(fractalOctaves);
            },
            // 5
            (fractalLacnarity) => {
                this.fnlNoise.SetFractalLacunarity(fractalLacnarity);
            },
            // 6
            (fractalWeightedStrength) => {
                this.fnlNoise.SetFractalWeightedStrength(fractalWeightedStrength);
            },
            // 7
            (fractalPingPongStrength) => {
                this.fnlNoise.SetFractalPingPongStrength(fractalPingPongStrength);
            },
            // 8
            (cellularDistanceFunc) => {
                this.setCellularDistanceFunc(this.getCellularDistanceFuncString(cellularDistanceFunc));
            },
            // 9
            (cellularRetType) => {
                this.setCellularRetType(this.getCellularRetTypeString(cellularRetType));
            },
            // 10
            (cellularJitter) => {
                this.fnlNoise.SetCellularJitter(cellularJitter);
            },
            // 11
            (fractalGain) => {
                this.fnlNoise.SetFractalGain(fractalGain);
            },
            // 12
            (noiseRotationType3D) => {
                this.setRotationType3D(this.getRotationType3DString(noiseRotationType3D));
            },
            // 13
            () => {
                this.warpSettings.enabled = true;
            },
            // 14
            () => {
                this.warpSettings.enabled = false;
            },
            // 15
            (warpType) => {
                this.setWarpType(this.getWarpTypeString(warpType));
            },
            // 16
            (warpAmp) => {
                this.fnlWarp.SetDomainWarpAmp(warpAmp);
            },
            // 17
            (warpSeed) => {
                this.setWarpSeed(warpSeed);
            },
            // 18
            (warpFrequency) => {
                this.fnlWarp.SetFrequency(warpFrequency);
            },
            // 19
            (warpRotationType3D) => {
                this.setWarpRortationType3D(this.getRotationType3DString(warpRotationType3D));
            },
            // 20
            (warpFractalType) => {
                this.warpSetFractalType(this.getFractalTypeString(warpFractalType));
            },
            // 21
            (warpFractalOctaves) => {
                this.fnlWarp.SetFractalOctaves(warpFractalOctaves);
            },
            // 22
            (warpFractalLacunarity) => {
                this.fnlWarp.SetFractalLacunarity(warpFractalLacunarity);
            },
            // 23
            (warpFractalGain) => {
                this.fnlWarp.SetFractalGain(warpFractalGain);
            },
            // 24
            (upperRange) => {
                this.noiseSettings.upperRange = upperRange;
            },
            // 25
            (lowerRange) => {
                this.noiseSettings.lowerRange = lowerRange;
            },
            // 26
            (surface, xOffset, yOffset, zOffset) => {
                console.warn("Fill surface object with noise is unsupported");
            }
        ];

        // update getNumOfConditions function if you edit this!!!!
        this.$conditionFuncs = [
        ];

        this.$expressionFuncs = [
            // 0
            () => {
                return this.noiseSettings.seed;
            },
            // 1
            this.stringToSeed,
            // 2
            (x, y, z) => {
                let pos = {};
                pos.x = x;
                pos.y = y;
                pos.z = z;

                if (this.warpSettings.enabled) {
                    this.fnlWarp.DomainWarp(pos);
                }

                return this.mapNoiseValue(this.fnlNoise.GetNoise(pos.x, pos.y, pos.z));
            },
            // 3
            (x, y) => {
                let pos = {};
                pos.x = x;
                pos.y = y;

                if (this.warpSettings.enabled) {
                    this.fnlWarp.DomainWarp(pos);
                }

                return this.mapNoiseValue(this.fnlNoise.GetNoise(pos.x, pos.y));
            },
            // 4
            (x) => {
                let pos = {};
                pos.x = x;
                pos.y = 0;

                if (this.warpSettings.enabled) {
                    this.fnlWarp.DomainWarp(pos);
                }

                return this.mapNoiseValue(this.fnlNoise.GetNoise(pos.x, pos.y));
            },
            // 5
            (x, xOffset, xSize) => {
                let xPos = x - xOffset;
                let radius = xSize / (Math.PI * 2.0);
                let angleStep = 360.0 / xSize;
                let angle = xPos * angleStep;
                angle = angle * Math.PI / 180.0;

                let pos = {};
                pos.x = (radius * Math.cos(angle));
                pos.y = (radius * Math.sin(angle));

                if (this.warpSettings.enabled) {
                    this.fnlWarp.DomainWarp(pos);
                }

                return this.mapNoiseValue(this.fnlNoise.GetNoise(pos.x, pos.y));
            },
            // 6
            () => {
                // reused for FastNoiseLite.DomainWarpType.OpenSimplex2, both should be 0
                return this.getNoiseTypeIndex("OpenSimplex2");
            },
            // 7
            () => {
                return this.getNoiseTypeIndex("OpenSimplex2S");
            },
            // 8
            () => {
                return this.getNoiseTypeIndex("Cellular");
            },
            // 9
            () => {
                return this.getNoiseTypeIndex("Perlin");
            },
            // 10
            () => {
                return this.getNoiseTypeIndex("ValueCubic");
            },
            // 11
            () => {
                return this.getNoiseTypeIndex("Value");
            },
            // 12
            () => {
                // reused for FastNoiseLite.RotationType3D.None, both should be 0
                return this.getFractalTypeIndex("None");
            },
            // 13
            () => {
                return this.getFractalTypeIndex("FBm");
            },
            // 14
            () => {
                return this.getFractalTypeIndex("Ridged");
            },
            // 15
            () => {
                return this.getFractalTypeIndex("PingPong");
            },
            // 16
            () => {
                return this.getCellularDistanceFuncIndex("Euclidean");
            },
            // 17
            () => {
                return this.getCellularDistanceFuncIndex("EuclideanSq");
            },
            // 18
            () => {
                return this.getCellularDistanceFuncIndex("Manhattan");
            },
            // 19
            () => {
                return this.getCellularDistanceFuncIndex("Hybrid");
            },
            // 20
            () => {
                return this.getCellularRetTypeIndex("CellValue");
            },
            // 21
            () => {
                return this.getCellularRetTypeIndex("Distance");
            },
            // 22
            () => {
                return this.getCellularRetTypeIndex("Distance2");
            },
            // 23
            () => {
                return this.getCellularRetTypeIndex("Distance2Add");
            },
            // 24
            () => {
                return this.getCellularRetTypeIndex("Distance2Sub");
            },
            // 25
            () => {
                return this.getCellularRetTypeIndex("Distance2Mul");
            },
            // 26
            () => {
                return this.getCellularRetTypeIndex("Distance2Div");
            },
            // 27
            () => {
                return this.getNoiseTypeIndex(this.noiseSettings.type);
            },
            // 28
            () => {
                return this.getFractalTypeIndex(this.noiseSettings.fractalType);
            },
            // 29
            () => {
                return this.getCellularDistanceFuncIndex(this.noiseSettings.cellularFunction);
            },
            // 30
            () => {
                return this.getCellularRetTypeIndex(this.noiseSettings.cellularReturnType);
            },
            // 31
            () => {
                return this.getRotationType3DIndex("ImproveXYPlanes");
            },
            // 32
            () => {
                return this.getRotationType3DIndex("ImproveXZPlanes");
            },
            // 33
            () => {
                return this.getRotationType3DIndex(this.noiseSettings.rotationType3D);
            },
            // 34
            () => {
                return this.getWarpTypeIndex("OpenSimplex2Reduced");
            },
            // 35
            () => {
                return this.getWarpTypeIndex("BasicGrid");
            },
            // 36
            () => {
                return this.getFractalTypeIndex("DomainWarpProgressive");
            },
            // 37
            () => {
                return this.getFractalTypeIndex("DomainWarpIndependent");
            },
            // 38
            () => {
                if(this.warpSettings.enabled)
                    return 1;
                return 0;
            },
            // 39
            () => {
                return this.warpSettings.seed;
            },
            // 40
            () => {
                return this.getWarpTypeIndex(this.warpSettings.type);
            },
            // 41
            () => {
                return this.getRotationType3DIndex(this.warpSettings.rotationType3D);
            },
            // 42
            () => {
                return this.getFractalTypeIndex(this.warpSettings.fractalType);
            },
            // 43
            () => {
                console.warn("Fill surface object with noise is unsupported");
            },
            // 44
            () => {
                console.warn("Fill surface object with noise is unsupported");
            },
            // 45
            () => {
                console.warn("Fill surface object with noise is unsupported");
            },
            // 46
            () => {
                console.warn("Fill surface object with noise is unsupported");
            },
            // 47
            () => {
                console.warn("Fill surface object with noise is unsupported");
            },
            // 48
            () => {
                console.warn("Fill surface object with noise is unsupported");
            }
        ];
    }

    mapNoiseValue(value) {
        return (this.noiseSettings.lowerRange + (this.noiseSettings.upperRange - this.noiseSettings.lowerRange) * ((value - -1.0) / (1.0 - -1.0)));
    }

    setSeed(seed) {
        this.fnlNoise.SetSeed(seed);
        this.noiseSettings.seed = seed;
    }

    setWarpSeed(seed) {
        this.fnlWarp.SetSeed(seed);
        this.warpSettings.seed = seed;
    }

    // All of these functions expect a string id, use get...String to get it from index.
    setNoiseType(type) {
        this.fnlNoise.SetNoiseType(type);
        this.noiseSettings.type = type;
    }

    setFractalType(fractalType) {
        this.fnlNoise.SetFractalType(fractalType);
        this.noiseSettings.fractalType = fractalType;
    }

    setCellularDistanceFunc(cellularDistanceFunc) {
        this.fnlNoise.SetCellularDistanceFunction(cellularDistanceFunc);
        this.noiseSettings.cellularDistanceFunction = cellularDistanceFunc;
    }

    setCellularRetType(cellularRetType) {
        this.fnlNoise.SetCellularReturnType(cellularRetType);
        this.noiseSettings.cellularReturnType = cellularRetType;
    }

    setRotationType3D(rotationType3D) {
        this.fnlNoise.SetRotationType3D(rotationType3D);
        this.noiseSettings.rotationType3D = rotationType3D;
    }

    setWarpType(warpType) {
        this.fnlWarp.SetDomainWarpType(warpType);
        this.warpSettings.type = warpType;
    }

    setWarpRortationType3D(warpRotationType3D) {
        this.fnlWarp.SetRotationType3D(warpRotationType3D);
        this.warpSettings.rotationType3D = warpRotationType3D;
    }

    setWarpFractalType(warpFractalType) {
        this.fnlWarp.SetFractalType(warpFractalType);
        this.warpSettings.fractalType = warpFractalType;
    }


    // FastNoiseLite js port stores type enums as strings, but we need numeric ids like in the c++ version
    // Since all type enums are stored in the same order instead of ids we can use the value index as one.
    // All input should come as numeric id and be converted to correct string id from FastNoiseLite enums and that string should be stored.
    getNoiseTypeIndex(noiseType) {
        return Object.values(FastNoiseLite.NoiseType).indexOf(noiseType);
    }

    getFractalTypeIndex(fractalType) {
        return Object.values(FastNoiseLite.FractalType).indexOf(fractalType);
    }

    getCellularDistanceFuncIndex(cellularDistanceFunc) {
        return Object.values(FastNoiseLite.CellularDistanceFunction).indexOf(cellularDistanceFunc);
    }

    getCellularRetTypeIndex(cellularRetType) {
        return Object.values(FastNoiseLite.CellularReturnType).indexOf(cellularRetType);
    }

    getRotationType3DIndex(rotationType3D) {
        return Object.values(FastNoiseLite.RotationType3D).indexOf(rotationType3D);
    }

    getWarpTypeIndex(warpType) {
        return Object.values(FastNoiseLite.DomainWarpType).indexOf(warpType);
    }

    // Convert index to string
    getNoiseTypeString(noiseType) {
        return Object.values(FastNoiseLite.NoiseType)[noiseType];
    }

    getFractalTypeString(fractalType) {
        return Object.values(FastNoiseLite.FractalType)[fractalType];
    }

    getCellularDistanceFuncString(cellularDistanceFunc) {
        return Object.values(FastNoiseLite.CellularDistanceFunction)[cellularDistanceFunc];
    }

    getCellularRetTypeString(cellularRetType) {
        return Object.values(FastNoiseLite.CellularReturnType)[cellularRetType];
    }

    getRotationType3DString(rotationType3D) {
        return Object.values(FastNoiseLite.RotationType3D)[rotationType3D];
    }

    getWarpTypeString(warpType) {
        return Object.values(FastNoiseLite.DomainWarpType)[warpType];
    }



    stringToSeed(str) {
        let seed = 0;
        str = str.trim();

        if(!isNaN(str)) {
            seed = Number(str);
        }
        else {
            // Convert the string to raw UTF8 bytes
            let enc = new TextEncoder;
            let rawBytes = enc.encode(str);

            for (let i = 0; i < rawBytes.length; i++) {
                const byte = rawBytes[i];
                seed += (byte + 1) * 6991;
                seed = seed << i;
            }
        }

        return seed;
    }


    getNumberOfConditions() {
        return 0; // $conditionFuncs not available yet
    }


    createRunObject(file, cob, version) {
        /// <summary> Creation of the Fusion extension. </summary>
        /// <param name="file"> A CFile object, pointing to the object's data zone </param>
        /// <param name="cob"> A CCreateObjectInfo containing infos about the created object</param>
        /// <param name="version"> version : the version number of the object, as defined in the C code </param>
        /// <returns type="Boolean"> Always false, as it is unused. </returns>

        // Use the "file" parameter to call the CFile object, and
        // gather the data of the object in the order as they were saved
        // (same order as the definition of the data in the EDITDATA structure
        // of the C code).
        // Please report to the documentation for more information on the CFile object

        if (this.ho == null)
            throw "HeaderObject not defined when needed to be.";

        // DarkEdif properties are accessible as on other platforms: IsPropChecked(), GetPropertyStr(), GetPropertyNum()
        let props = new darkEdif['Properties'](this, file, version);

        this.fnlNoise = new FastNoiseLite();
        this.fnlWarp = new FastNoiseLite();

        this.setNoiseType(props["GetPropertyStr"]("Noise type"));

        this.noiseSettings.upperRange = props["GetPropertyNum"]("Noise value upper range");
        this.noiseSettings.lowerRange = props["GetPropertyNum"]("Noise value lower range");

        this.setSeed(this.stringToSeed(props["GetPropertyStr"]("Noise seed")));
        this.fnlNoise.SetFrequency(props["GetPropertyNum"]("Noise frequency"));
        this.setRotationType3D(props["GetPropertyStr"]("Rotation type 3D"));

        this.setFractalType(props["GetPropertyStr"]("Fractal type"));
        this.fnlNoise.SetFractalOctaves(props["GetPropertyNum"]("Fractal octaves"))
        this.fnlNoise.SetFractalLacunarity(props["GetPropertyNum"]("Fractal lacunarity"));
        this.fnlNoise.SetFractalGain(props["GetPropertyNum"]("Fractal gain"));
        this.fnlNoise.SetFractalWeightedStrength(props["GetPropertyNum"]("Fractal weighted strength"));
        this.fnlNoise.SetFractalPingPongStrength(props["GetPropertyNum"]("Fractal PingPong strength"));

        this.setCellularDistanceFunc(props["GetPropertyStr"]("Cellular distance function"));
        this.setCellularRetType(props["GetPropertyStr"]("Cellular return type"));
        this.fnlNoise.SetCellularJitter(props["GetPropertyNum"]("Cellular jitter"));

        {
            const warpType = props["GetPropertyStr"]("Domain warp type");

            if(warpType === "Disabled") {
                this.warpSettings.enabled = false;
            } else {
                this.warpSettings.enabled = true;
                this.setWarpType(warpType);
            }
        }

        this.fnlWarp.SetDomainWarpAmp(props["GetPropertyNum"]("Domain warp amplitude"));

        this.setWarpSeed(this.stringToSeed(props["GetPropertyStr"]("Domain warp seed")));
        this.fnlWarp.SetFrequency(props["GetPropertyNum"]("Domain warp frequency"));
        this.setWarpRortationType3D(props["GetPropertyStr"]("Domain warp rotation type 3D"));

        this.setWarpFractalType(props["GetPropertyStr"]("DW fractal type"));
        this.fnlWarp.SetFractalOctaves(props["GetPropertyNum"]("DW fractal octaves"))
        this.fnlWarp.SetFractalLacunarity(props["GetPropertyNum"]("DW fractal lacunarity"));
        this.fnlWarp.SetFractalGain(props["GetPropertyNum"]("DW fractal gain"));

        console.log(this.noiseSettings);
        console.log(this.warpSettings);

        // The return value is not used in this version of the runtime: always return false.
        return false;
    }

    handleRunObject() {
        /// <summary> This function is called at every loop of the game. You have to perform
        /// in it all the tasks necessary for your object to function. </summary>
        /// <returns type="Number"> One of two options:
        ///                            0 : this function will be called during the next loop
        /// CRunExtension.REFLAG_ONESHOT : this function will not be called anymore,
        ///                                unless this.reHandle() is called. </returns>
        return CRunExtension.REFLAG_ONESHOT;
    }

    condition(num, cnd) {
        /// <summary> Called when a condition of this object is tested. </summary>
        /// <param name="num" type="Number" integer="true"> The number of the condition; 0+. </param>
        /// <param name="cnd" type="CCndExtension"> a CCndExtension object, allowing you to retreive the parameters of the condition. </param>
        /// <returns type="Boolean"> True if the condition is currently true. </returns>

        const func = this.$conditionFuncs[~~num];
        if (func == null)
            throw "Unrecognised condition ID " + (~~num) + " passed to DarkEdif Template.";

        // Note: New Direction parameter is not supported by this, add a workaround based on condition and parameter index;
        // SDL Joystick's source has an example.
        const args = new Array(func.length);
        for (let i = 0; i < args.length; i++)
            args[i] = cnd.getParamExpString(this.rh, i);

        return func.apply(this, args);
    }

    action(num, act) {
        /// <summary> Called when an action of this object is executed </summary>
        /// <param name="num" type="Number"> The ID/number of the action, as defined by its array index. </param>
        /// <param name="act" type="CActExtension"> A CActExtension object, allowing you to retrieve the parameters of the action </param>

        const func = this.$actionFuncs[~~num];
        if (func == null)
            throw "Unrecognised action ID " + (~~num) + " passed to DarkEdif Template.";

        // Note: New Direction parameter is not supported by this, add a workaround based on action and parameter index;
        // SDL Joystick's source has an example.
        const args = new Array(func.length);
        for (let i = 0; i < args.length; i++)
            args[i] = act.getParamExpression(this.rh, i);

        func.apply(this, args);
    }

    expression(num) {
        /// <summary> Called during the evaluation of an expression. </summary>
        /// <param name="num" type="Number"> The ID/number of the expression. </param>
        /// <returns> The result of the calculation, a number or a string </returns>

        // Note that it is important that your expression function asks for
        // each and every one of the parameters of the function, each time it is
        // called. The runtime will crash if you miss parameters.

        const func = this.$expressionFuncs[~~num];
        if (func == null)
            throw "Unrecognised expression ID " + (~~num) + " passed to DarkEdif Template.";

        const args = new Array(func.length);
        for (let i = 0; i < args.length; i++)
            args[i] = this.ho.getExpParam();

        return func.apply(this, args);
    }
}
