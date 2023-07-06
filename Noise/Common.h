#pragma once

#define MMFEXT

#include "DarkEdif.h"

#ifdef _DEBUG
#define JSON_COMMENT_MACRO "(Debug) "
#else
#define JSON_COMMENT_MACRO ""
#endif



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
#include "SurfaceObject.hpp"
#include "Extension.h"
