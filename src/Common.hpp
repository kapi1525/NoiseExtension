#pragma once

// Do not move XXXEXT after #include of DarkEdif.h!
#define MMFEXT		// Fusion 2.x, Fusion 2.x Dev

#include "DarkEdif.hpp"

#ifdef _DEBUG
#define JSON_COMMENT_MACRO "(Debug) "
#else
#define JSON_COMMENT_MACRO ""
#endif

#pragma pack (push, 1)
// Binary block used in Fusion editor and saved in the MFA/CCN/EXE files
struct EDITDATA final
{
	NO_DEFAULT_CTORS_OR_DTORS(EDITDATA);
	// Header - required, must be first variable in EDITDATA
	extHeader eHeader;

    #if EditorBuild
    static DarkEdif::Properties::PropertyReader* UserConverter();
    #endif

	// Keep Properties variable last; its size varies.
	DarkEdif::Properties Props;
};
#pragma pack (pop)

#include "Extension.hpp"
