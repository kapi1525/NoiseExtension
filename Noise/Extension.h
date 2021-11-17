#pragma once
#include "DarkEdif.h"

class Extension
{
public:

#ifdef _WIN32
	RUNDATA * rdPtr;
	RunHeader * rhPtr;
#elif defined(__ANDROID__)
	RuntimeFunctions & runFuncs;
	global<jobject> javaExtPtr;
#else
	RuntimeFunctions & runFuncs;
	void * objCExtPtr;
#endif

	Edif::Runtime Runtime;

	static const int MinimumBuild = 254;
	static const int Version = 4;

	// If you change OEFLAGS, make sure you modify RUNDATA so the data is available, or you'll get crashes!
	// For example, OEFLAGS::VALUES makes use of the AltVals rv struct.
	static const OEFLAGS OEFLAGS = OEFLAGS::NONE;
	static const OEPREFS OEPREFS = OEPREFS::NONE;

	static const int WindowProcPriority = 100;

#ifdef _WIN32
	Extension(RUNDATA * rdPtr, EDITDATA * edPtr, CreateObjectInfo * cobPtr);
#elif defined(__ANDROID__)
	Extension(RuntimeFunctions & runFuncs, EDITDATA * edPtr, jobject javaExtPtr);
#else
	Extension(RuntimeFunctions & runFuncs, EDITDATA * edPtr, void * objCExtPtr);
#endif
	~Extension();

	// To add items to the Fusion Debugger, just uncomment this line.
	DarkEdif::FusionDebugger FusionDebugger;
	// After enabling it, you run FusionDebugger.AddItemToDebugger() inside Extension's constructor
	// As an example:
	std::tstring exampleDebuggerTextItem;


	FastNoiseLite Noise;
	int Seed = 1337;

	int NoiseType = FastNoiseLite::NoiseType::NoiseType_OpenSimplex2;
	int FractalType = FastNoiseLite::FractalType::FractalType_None;
	int CellularFunction = FastNoiseLite::CellularDistanceFunction::CellularDistanceFunction_EuclideanSq;
	int CellularReturnType = FastNoiseLite::CellularReturnType::CellularReturnType_Distance;


	/// Actions
		void SetSeed(int Seed);

		// Requests
		void NoiseRequest3D(const TCHAR* name, int x, int y, int z, int xsize, int ysize, int zsize);
		void NoiseRequest2D(const TCHAR* name, int x, int y, int xsize, int ysize);
		void NoiseRequest1D(const TCHAR* name, int x, int xsize);
		// TODO: void NoiseRequestLooping1D();

		void CleanupRequest(const TCHAR* name);
		void CleanupRequests();

		// Sets
		void SetNoiseType(int Type);
		void SetNoiseFrequency(float Frequency);

		void SetFractalType(int Type);
		void SetFractalOctaves(int Octaves);
		void SetFractalLacunarity(float Lacunarity);
		void SetFractalWeighted(float Weighted);
		void SetFractalPingPong(float PingPong);

		void SetCellularDistanceFunction(int Function);
		void SetCellularReturnType(int Return);
		void SetCellularJitter(float Jitter);

	/// Conditions
		// (not) None
		bool IsRequestReady(const TCHAR* name);

	/// Expressions
		int GetSeed();
		int StringToSeed(const TCHAR* String);

		float GetNoise3D(float x, float y, float z);
		float GetNoise2D(float x, float y);
		float GetNoise1D(float x);
		float GetLoopingNoise1D(float x, float xoffset, float xsize);

		// Requests
		float GetRequestNoise3D(const TCHAR* name, float x, float y, float z);
		float GetRequestNoise2D(const TCHAR* name, float x, float y);
		float GetRequestNoise1D(const TCHAR* name, float x);
		// TODO: float GetRequestLoopingNoise1D(float x, float xoffset, float xsize);

		// Noise Types
		int OpenSimplex2();
		int OpenSimplex2S();
		int Cellular();
		int Perlin();
		int ValueCubic();
		int Value();

		// Fractal Types
		int None();
		int FBm();
		int Rigid();
		int PingPong();

		// Cellular Functions
		int Euclidean();
		int EuclideanSq();
		int Manhattan();
		int Hybrid();

		// Cellular Return Types
		int CellValue();
		int Distance();
		int Distance2();
		int Distance2Add();
		int Distance2Sub();
		int Distance2Mul();
		int Distance2Div();

		// Current selections
		int CurrentNoiseType();
		int CurrentFractalType();
		int CurrentCellularFunction();
		int CUrrentCellularReturnType();


	/* These are called if there's no function linked to an ID */

	void UnlinkedAction(int ID);
	long UnlinkedCondition(int ID);
	long UnlinkedExpression(int ID);




	/*  These replace the functions like HandleRunObject that used to be
		implemented in Runtime.cpp. They work exactly the same, but they're
		inside the extension class.
	*/

	REFLAG Handle();
	REFLAG Display();

	short FusionRuntimePaused();
	short FusionRuntimeContinued();
};
