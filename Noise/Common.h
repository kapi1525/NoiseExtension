#pragma once

#define MMFEXT

#define NOPROPS
#include "DarkEdif.h"

#include "FastNoiseLite.h"



// edPtr : Used at edittime and saved in the MFA/CCN/EXE files

// Latest EDITDATA revision
struct EDITDATA {
	NO_DEFAULT_CTORS(EDITDATA)

	// Header - required
	extHeader	eHeader;
	short		editdata_rev;

	// Properties
	int          noise_seed;

	unsigned int noise_type;
	float        noise_frequency;

	unsigned int fractal_type;
	int          fractal_octaves;
	float        fractal_lacunarity;
	float        fractal_gain;
	float        fractal_weighted_strength;
	float        fractal_pingpong_strength;

	unsigned int cellular_distance_func;
	unsigned int cellular_ret_type;
	float        cellular_jitter;
};


// Old version of EDITDATA without revision number yet
struct EDITDATA_prerev {
	NO_DEFAULT_CTORS(EDITDATA_prerev)

	// Header - required
	extHeader		eHeader;

	// Properties
	int          noise_seed;

	unsigned int noise_type;
	float        noise_frequency;

	unsigned int fractal_type;
	int          fractal_octaves;
	float        fractal_lacunarity;
	float        fractal_weighted_strength;
	float        fractal_pingpong_strength;

	unsigned int cellular_distance_func;
	unsigned int cellular_ret_type;
	float        cellular_jitter;
};


class Extension;

struct RUNDATA {
	// Main header - required
	HeaderObject rHo;

	// Required
	Extension * pExtension;
};

#include "Extension.h"
