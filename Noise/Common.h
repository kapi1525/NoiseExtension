#pragma once

#define MMFEXT

#include "DarkEdif.h"

#include "FastNoiseLite.h"



enum class NoisePropID {
	Seed,
	NoiseType,
	FractalType,
	CellularDistFunc,
	CellularRetType,
	Version
}



// edPtr : Used at edittime and saved in the MFA/CCN/EXE files
struct EDITDATA {
	// Header - required
	extHeader		eHeader;

	// Keep DarkEdif variables as last. Undefined behaviour otherwise.
	int				DarkEdif_Prop_Size;
	char			DarkEdif_Props[];

	// =====
	// DarkEdif functions, use within Extension ctor.
	// =====
	bool IsPropChecked(int propID);						// Returns property checked or unchecked.
	std::tstring GetPropertyStr(const char * propName);	// Returns std::tstring property setting from property name.
	std::tstring GetPropertyStr(int propID);			// Returns std::tstring property string from property ID.
};

class Extension;

struct RUNDATA {
	// Main header - required
	HeaderObject rHo;

	// Required
	Extension * pExtension;
};

#include "Extension.h"
