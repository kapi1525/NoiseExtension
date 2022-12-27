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
	static const int Version = 20;

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

	// TODO: Add DomainWarp in v1.1
	FastNoiseLite noise;
	int seed;

	int noise_type;
	int fractal_type;
	int cellular_function;
	int cellular_return_type;

	// Actions
		void set_seed(int seed_);

		// Sets
		void set_noise_type(int type);
		void set_noise_frequency(float frequency);

		void set_fractal_type(int type);
		void set_fractal_octaves(int octaves);
		void set_fractal_lacunarity(float lacunarity);
		void set_fractal_gain(float gain);
		void set_fractal_weighted(float weighted);
		void set_fractal_pingpong(float pingpong);

		void set_cellular_distance_function(int function);
		void set_cellular_return_type(int return_type);
		void set_cellular_jitter(float jitter);

	// Conditions

	// Expressions
		int get_seed();
		int string_to_seed(const TCHAR* string);

		float get_noise3D(float x, float y, float z);
		float get_noise2D(float x, float y);
		float get_noise1D(float x);
		float get_looping_noise1D(float x, float xoffset, float xsize);

        // Constant values
        int always_0();
        int always_1();
        int always_2();
        int always_3();
        int always_4();
        int always_5();
        int always_6();

		// Current selections
		int current_noise_type();
		int current_fractal_type();
		int current_cellular_function();
		int current_cellular_return_type();


	// These are called if there's no function linked to an ID

	void UnlinkedAction(int ID);
	long UnlinkedCondition(int ID);
	long UnlinkedExpression(int ID);


	REFLAG Handle();
	REFLAG Display();

	short FusionRuntimePaused();
	short FusionRuntimeContinued();
};
