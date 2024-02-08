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
        this['ExtensionVersion'] = 22;      // To match C++ version
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
            type:               Object.values(FastNoiseLite.NoiseType).indexOf("OpenSimplex2"),
            rotationType3D:     Object.values(FastNoiseLite.RotationType3D).indexOf("None"),
            fractalType:        Object.values(FastNoiseLite.FractalType).indexOf("None"),
            cellularFunction:   Object.values(FastNoiseLite.CellularDistanceFunction).indexOf("EuclideanSq"),
            cellularReturnType: Object.values(FastNoiseLite.CellularReturnType).indexOf("Distance"),
        };

        this.warpSettings = {
            enabled:            false,
            seed:               1337,
            type:               Object.values(FastNoiseLite.DomainWarpType).indexOf("OpenSimplex2"),
            rotationType3D:     Object.values(FastNoiseLite.RotationType3D).indexOf("None"),
            fractalType:        Object.values(FastNoiseLite.FractalType).indexOf("None"),
        };

        // =============================
        // Function arrays
        // =============================

        this.$actionFuncs = [
            // 0
            this.setSeed,
            // 1
            this.setNoiseType,
            // 2
            (frequency) => {
                this.fnlNoise.SetFrequency(frequency);
            },
            // 3
            this.setFractalType,
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
            this.setCellularDistanceFunc,
            // 9
            this.setCellularRetType,
            // 10
            (cellularJitter) => {
                this.fnlNoise.SetCellularJitter(cellularJitter);
            },
            // 11
            (fractalGain) => {
                this.fnlNoise.SetFractalGain(fractalGain);
            },
            // 12
            this.setRotationType3D,
            // 13
            () => {
                this.warpSettings.enabled = true;
            },
            // 14
            () => {
                this.warpSettings.enabled = false;
            },
            // 15
            this.setWarpType,
            // 16
            (warpAmp) => {
                this.fnlWarp.SetDomainWarpAmp(warpAmp);
            },
            // 17
            (warpSeed) => {
                this.fnlWarp.SetSeed(warpSeed);
            },
            // 18
            (warpFrequency) => {
                this.fnlWarp.SetFrequency(warpFrequency);
            },
            // 19
            this.setWarpRortationType3D,
            // 20
            this.warpSetFractalType,
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
                return Object.values(FastNoiseLite.NoiseType).indexOf("OpenSimplex2");
            },
            // 7
            () => {
                return Object.values(FastNoiseLite.NoiseType).indexOf("OpenSimplex2S");
            },
            // 8
            () => {
                return Object.values(FastNoiseLite.NoiseType).indexOf("Cellular");
            },
            // 9
            () => {
                return Object.values(FastNoiseLite.NoiseType).indexOf("Perlin");
            },
            // 10
            () => {
                return Object.values(FastNoiseLite.NoiseType).indexOf("ValueCubic");
            },
            // 11
            () => {
                return Object.values(FastNoiseLite.NoiseType).indexOf("Value");
            },
            // 12
            () => {
                // reused for FastNoiseLite.RotationType3D.None, both should be 0
                return Object.values(FastNoiseLite.FractalType).indexOf("None");
            },
            // 13
            () => {
                return Object.values(FastNoiseLite.FractalType).indexOf("FBm");
            },
            // 14
            () => {
                // FIXME: Was it always called that??????
                return Object.values(FastNoiseLite.FractalType).indexOf("Ridged");
            },
            // 15
            () => {
                return Object.values(FastNoiseLite.FractalType).indexOf("PingPong");
            },
            // 16
            () => {
                return Object.values(FastNoiseLite.CellularDistanceFunction).indexOf("Euclidean");
            },
            // 17
            () => {
                return Object.values(FastNoiseLite.CellularDistanceFunction).indexOf("EuclideanSq");
            },
            // 18
            () => {
                return Object.values(FastNoiseLite.CellularDistanceFunction).indexOf("Manhattan");
            },
            // 19
            () => {
                return Object.values(FastNoiseLite.CellularDistanceFunction).indexOf("Hybrid");
            },
            // 20
            () => {
                return Object.values(FastNoiseLite.CellularReturnType).indexOf("CellValue");
            },
            // 21
            () => {
                return Object.values(FastNoiseLite.CellularReturnType).indexOf("Distance");
            },
            // 22
            () => {
                return Object.values(FastNoiseLite.CellularReturnType).indexOf("Distance2");
            },
            // 23
            () => {
                return Object.values(FastNoiseLite.CellularReturnType).indexOf("Distance2Add");
            },
            // 24
            () => {
                return Object.values(FastNoiseLite.CellularReturnType).indexOf("Distance2Sub");
            },
            // 25
            () => {
                return Object.values(FastNoiseLite.CellularReturnType).indexOf("Distance2Mul");
            },
            // 26
            () => {
                return Object.values(FastNoiseLite.CellularReturnType).indexOf("Distance2Div");
            },
            // 27
            () => {
                return this.noiseSettings.type;
            },
            // 28
            () => {
                return this.noiseSettings.fractalType;
            },
            // 29
            () => {
                return this.noiseSettings.cellularFunction;
            },
            // 30
            () => {
                return this.noiseSettings.cellularReturnType;
            },
            // 31
            () => {
                return Object.values(FastNoiseLite.RotationType3D).indexOf("ImproveXYPlanes");
            },
            // 32
            () => {
                return Object.values(FastNoiseLite.RotationType3D).indexOf("ImproveXZPlanes");
            },
            // 33
            () => {
                return this.noiseSettings.rotationType3D;
            },
            // 34
            () => {
                return Object.values(FastNoiseLite.DomainWarpType).indexOf("OpenSimplex2Reduced");
            },
            // 35
            () => {
                return Object.values(FastNoiseLite.DomainWarpType).indexOf("BasicGrid");
            },
            // 36
            () => {
                return Object.values(FastNoiseLite.FractalType).indexOf("DomainWarpProgressive");
            },
            // 37
            () => {
                return Object.values(FastNoiseLite.FractalType).indexOf("DomainWarpIndependent");
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
                return Object.values(FastNoiseLite.DomainWarpType).indexOf(this.warpSettings.type);
            },
            // 41
            () => {
                return this.warpSettings.rotationType3D;
            },
            // 42
            () => {
                return this.warpSettings.fractalType;
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

    setNoiseType(type) {
        this.fnlNoise.SetNoiseType(Object.values(FastNoiseLite.NoiseType)[type]);
        this.noiseSettings.type = type;
    }

    setFractalType(fractalType) {
        this.fnlNoise.SetFractalType(Object.values(FastNoiseLite.FractalType)[fractalType]);
        this.noiseSettings.FractalType = fractalType;
    }

    setCellularDistanceFunc(cellularDistanceFunc) {
        this.fnlNoise.SetCellularDistanceFunction(Object.values(FastNoiseLite.CellularDistanceFunction)[cellularDistanceFunc]);
        this.noiseSettings.CellularDistanceFunction = cellularDistanceFunc;
    }

    setCellularRetType(cellularRetType) {
        this.fnlNoise.SetCellularReturnType(Object.values(FastNoiseLite.CellularReturnType)[cellularRetType]);
        this.noiseSettings.CellularReturnType = cellularRetType;
    }

    setRotationType3D(rotationType3D) {
        this.fnlNoise.SetRotationType3D(Object.values(FastNoiseLite.RotationType3D)[rotationType3D]);
        this.noiseSettings.rotationType3D = rotationType3D;
    }

    setWarpType(warpType) {
        this.fnlWarp.SetDomainWarpType(Object.values(FastNoiseLite.DomainWarpType)[warpType]);
        this.warpSettings.type = warpType;
    }

    setWarpRortationType3D(warpRotationType3D) {
        this.fnlWarp.SetRotationType3D(Object.values(FastNoiseLite.RotationType3D)[warpRotationType3D]);
        this.warpSettings.rotationType3D = warpRotationType3D;
    }

    warpSetFractalType(warpFractalType) {
        this.fnlWarp.SetFractalType(Object.values(FastNoiseLite.FractalType)[warpFractalType]);
        this.warpSettings.fractalType = warpFractalType;
    }


    stringToSeed(str) {
        // TODO:
        return 1337;
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
