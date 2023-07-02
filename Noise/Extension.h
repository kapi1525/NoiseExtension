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
	static const int Version = 21;

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


	FastNoiseLite fnl_noise;        // Main FastNoiseLite instance for generating noise
	FastNoiseLite fnl_warp;         // Separate FastNoiseLite instance for domain warp

    // TODO: Add support for exporting and importing settings at runtime?
    struct {
        int seed;
        float upper_range;
        float lower_range;
        FastNoiseLite::NoiseType type;
        FastNoiseLite::RotationType3D rotation_type_3d;
        FastNoiseLite::FractalType fractal_type;
        FastNoiseLite::CellularDistanceFunction cellular_function;
        FastNoiseLite::CellularReturnType cellular_return_type;
    } noise;

    struct {
        bool enabled;
        int seed;
        FastNoiseLite::DomainWarpType type;
        FastNoiseLite::RotationType3D rotation_type_3d;
        FastNoiseLite::FractalType fractal_type;
    } warp;

    bool multithreading_enabled = true;


	// Actions
		// Noise settings
		void set_noise_type(int type);

        void set_noise_upper_range(float range);
        void set_noise_lower_range(float range);

        void set_noise_seed(int seed);
		void set_noise_frequency(float frequency);
        void set_noise_rotation_type_3d(int type);

		void set_noise_fractal_type(int type);
		void set_noise_fractal_octaves(int octaves);
		void set_noise_fractal_lacunarity(float lacunarity);
		void set_noise_fractal_gain(float gain);
		void set_noise_fractal_weighted(float weighted);
		void set_noise_fractal_pingpong(float pingpong);

		void set_noise_cellular_distance_function(int function);
		void set_noise_cellular_return_type(int return_type);
		void set_noise_cellular_jitter(float jitter);

        // Warp settings
        void enable_warp();
        void disable_warp();

        void set_warp_type(int type);
        void set_warp_amp(float amp);

        void set_warp_seed(int seed);
        void set_warp_frequency(float frequency);
        void set_warp_rotation_type_3d(int type);

		void set_warp_fractal_type(int type);
		void set_warp_fractal_octaves(int octaves);
		void set_warp_fractal_lacunarity(float lacunarity);
		void set_warp_fractal_gain(float gain);
		void set_warp_fractal_weighted(float weighted);


        void fill_surface_obj_with_noise(SURFACE* surface_obj, float xoffset, float yoffset, float zoffset, int flags);
        void fill_buffer_with_noise(uint8_t* buf, int depth, int width, int height, float xoffset, float yoffset, float zoffset, int flags);
        void fill_buffer_with_noise_multithreaded(uint8_t* buf, int depth, int width, int height, float xoffset, float yoffset, float zoffset, int flags);

	// Conditions
        // No conditions are here

	// Expressions
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

		// Current settings for noise
		int current_noise_seed();
		int current_noise_type();
		int current_noise_rotation_type_3d();
		int current_noise_fractal_type();
		int current_noise_cellular_function();
		int current_noise_cellular_return_type();

        // Current settings for domain warp
        int is_warp_enabled();
		int current_warp_seed();
        int current_warp_type();
		int current_warp_rotation_type_3d();
		int current_warp_fractal_type();

        // Fill surface with noise flags
        int default_flags();
        int fill_red();
        int fill_green();
        int fill_blue();


    float map_noise_value(float value);


	// These are called if there's no function linked to an ID
	void UnlinkedAction(int ID);
	long UnlinkedCondition(int ID);
	long UnlinkedExpression(int ID);

	REFLAG Handle();
	REFLAG Display();

	short FusionRuntimePaused();
	short FusionRuntimeContinued();
};
