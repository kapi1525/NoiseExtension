#pragma once

#define MMFEXT

#include "DarkEdif.h"



// EDITDATA with smart properties
struct EDITDATA {
	NO_DEFAULT_CTORS(EDITDATA)

	// Header - required
	extHeader eHeader;

    #if EditorBuild
    static DarkEdif::Properties::PropertyReader* UserConverter();
    #endif

	// Keep DarkEdif variables as last. Undefined behaviour otherwise.
	DarkEdif::Properties Props;
};



class Extension;

struct RUNDATA {
	// Main header - required
	HeaderObject rHo;

	// Required
	Extension* pExtension;
};

#include "FastNoiseLite.h"
#include "Extension.h"
