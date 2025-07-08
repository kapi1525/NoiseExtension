#pragma once
#include "Common.hpp"



enum FillSurfaceFlags : int {
    // What color channels should be filled with noise?
    FillRed = 1<<0,
    FillGreen = 1<<1,
    FillBlue = 1<<2,
    FillAlpha = 1<<3,
    // Use GetNoise2D instead of GetNoise3D, z offset will be ignored
    Only2D = 1<<4,
    FillAlpha0 = 1<<5,
    FillAlpha255 = 1<<6,

    DefaultFlags = (FillRed | FillGreen | FillBlue),
};


enum class PixelFormat {
    BGR24,
    A8,
    RGBA32,
};


// Surface object Identifier
static const uint32_t SurfaceID (('S'<<24)|('U'<<16)|('R'<<8)|('F'));


// Surface object was never ported to other platforms (except paid html5 port)
#ifdef _WIN32

// Surface object RUNDATA
struct SURFACE {
	NO_DEFAULT_CTORS_OR_DTORS(SURFACE)
    HeaderObject rHo;
    rCom rc;
    rMvt rm;
    Sprite rs;
    AltVals rv;

    void* rRd;

    // std::vector of the cSurfaces - use functions at bottom instead
    void* images;

    // Selected image for editing
    cSurface* selected;
    short selectedId;
    bool selectedIsValid;

    // Displayed image
    cSurface* current;
    short currentId;

    // Index of the last added image
    short lastId;

    // Please use these functions to access a specific image
    cSurface* (*GetImage) (SURFACE* thisPointer, int imageIndex);
    int (*GetImageCount) (SURFACE* thisPointer);
};

#else

using SURFACE=void*;

#endif