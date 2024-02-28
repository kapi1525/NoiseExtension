#pragma once

#define MMFEXT

// TODO: Use the new cross platform functions if possible.
#define FUSION_INTERNAL_ACCESS

#include "DarkEdif.hpp"

#ifdef _DEBUG
#define JSON_COMMENT_MACRO "(Debug) "
#else
#define JSON_COMMENT_MACRO ""
#endif



// EDITDATA with smart properties
struct EDITDATA {
	NO_DEFAULT_CTORS_OR_DTORS(EDITDATA)

	// Header - required
	extHeader eHeader;

    #if EditorBuild
    static DarkEdif::Properties::PropertyReader* UserConverter();
    #endif

	// Keep DarkEdif variables as last. Undefined behaviour otherwise.
	DarkEdif::Properties Props;
};

class Extension;

#include "FastNoiseLite.h"
#include "SurfaceObject.hpp"
#include "Extension.hpp"
