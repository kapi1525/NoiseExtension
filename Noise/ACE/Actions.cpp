#include "Common.h"



void Extension::set_noise_type(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::NoiseType_Value) {
		DarkEdif::MsgBox::WarningOK(_T("Set Noise type"), _T("Set Noise type action expects one of noise types (see: Noise type expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise.type = static_cast<FastNoiseLite::NoiseType>(type);
	fnl_noise.SetNoiseType(noise.type);
}


void Extension::set_noise_upper_range(float range) {
    noise.upper_range = range;
}

void Extension::set_noise_lower_range(float range) {
    noise.lower_range = range;
}


void Extension::set_noise_seed(int seed) {
	noise.seed = seed;
	fnl_noise.SetSeed(noise.seed);
}

void Extension::set_noise_frequency(float frequency) {
	fnl_noise.SetFrequency(frequency);
}

void Extension::set_noise_rotation_type_3d(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::RotationType3D_ImproveXZPlanes) {
		DarkEdif::MsgBox::WarningOK(_T("Set rotation type 3D"), _T("Set rotation type 3D action expects one of rotation types 3d (see: Rotation type 3D expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise.rotation_type_3d = static_cast<FastNoiseLite::RotationType3D>(type);
	fnl_noise.SetRotationType3D(noise.rotation_type_3d);
}



void Extension::set_noise_fractal_type(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::FractalType_PingPong) {
		DarkEdif::MsgBox::WarningOK(_T("Set fractal type"), _T("Set fractal type action expects one of fractal types (see: Fractal type expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise.fractal_type = static_cast<FastNoiseLite::FractalType>(type);
	fnl_noise.SetFractalType(noise.fractal_type);
}


void Extension::set_noise_fractal_octaves(int octaves) {
	fnl_noise.SetFractalOctaves(octaves);
}

void Extension::set_noise_fractal_lacunarity(float lacunarity) {
	fnl_noise.SetFractalLacunarity(lacunarity);
}

void Extension::set_noise_fractal_gain(float gain) {
	fnl_noise.SetFractalGain(gain);
}

void Extension::set_noise_fractal_weighted(float weighted) {
	fnl_noise.SetFractalWeightedStrength(weighted);
}

void Extension::set_noise_fractal_pingpong(float pingpong) {
	fnl_noise.SetFractalPingPongStrength(pingpong);
}



void Extension::set_noise_cellular_distance_function(int function) {
	#if EditorBuild
	if(function < 0 || function > FastNoiseLite::CellularDistanceFunction_Hybrid) {
		DarkEdif::MsgBox::WarningOK(_T("Set cellular distance function"), _T("Set cellular distance function action expects one of cellular distance functions (see: Cellular distance functions expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise.cellular_function = static_cast<FastNoiseLite::CellularDistanceFunction>(function);
	fnl_noise.SetCellularDistanceFunction(noise.cellular_function);
}

void Extension::set_noise_cellular_return_type(int return_type) {
	#if EditorBuild
	if(return_type < 0 || return_type > FastNoiseLite::CellularReturnType_Distance2Div) {
		DarkEdif::MsgBox::WarningOK(_T("Set cellular return type"), _T("Set cellular return type action expects one of cellular return types (see: Cellular return types expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	noise.cellular_return_type = static_cast<FastNoiseLite::CellularReturnType>(return_type);
	fnl_noise.SetCellularReturnType(noise.cellular_return_type);
}

void Extension::set_noise_cellular_jitter(float jitter) {
	fnl_noise.SetCellularJitter(jitter);
}



// Warp settings
void Extension::enable_warp() {
    warp.enabled = true;
}

void Extension::disable_warp() {
    warp.enabled = false;
}


void Extension::set_warp_type(int type) {
    warp.type = static_cast<FastNoiseLite::DomainWarpType>(type);
    fnl_warp.SetDomainWarpType(warp.type);
}

void Extension::set_warp_amp(float amp) {
    fnl_warp.SetDomainWarpAmp(amp);
}


void Extension::set_warp_seed(int seed) {
    fnl_warp.SetSeed(seed);
}

void Extension::set_warp_frequency(float frequency) {
    fnl_warp.SetFrequency(frequency);
}

void Extension::set_warp_rotation_type_3d(int type) {
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::RotationType3D_ImproveXZPlanes) {
		DarkEdif::MsgBox::WarningOK(_T("Set rotation type 3D"), _T("Set rotation type 3D action expects one of rotation types 3d (see: Rotation type 3D expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	warp.rotation_type_3d = static_cast<FastNoiseLite::RotationType3D>(type);
	fnl_warp.SetRotationType3D(warp.rotation_type_3d);
}


void Extension::set_warp_fractal_type(int type) {
	#if EditorBuild
	if(0) { //TODO
		DarkEdif::MsgBox::WarningOK(_T("Set fractal type"), _T("Set fractal type action expects one of fractal types (see: Fractal type expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	warp.fractal_type = static_cast<FastNoiseLite::FractalType>(type);
	fnl_warp.SetFractalType(warp.fractal_type);
}

void Extension::set_warp_fractal_octaves(int octaves) {
    fnl_warp.SetFractalOctaves(octaves);
}

void Extension::set_warp_fractal_lacunarity(float lacunarity) {
    fnl_warp.SetFractalLacunarity(lacunarity);
}

void Extension::set_warp_fractal_gain(float gain) {
    fnl_warp.SetFractalGain(gain);
}


#ifdef _WIN32

static cSurface* create_surface(int width, int height, int depth, SurfaceType type, SurfaceDriver driver) {
    cSurface* proto = nullptr;

    BOOL result = GetSurfacePrototype(&proto, depth, (int)type, (int)driver);
	assert(result == TRUE);

    cSurface* s = new cSurface;
    s->Create(width, height, proto);
    return s;
}

#endif

void Extension::fill_surface_obj_with_noise(SURFACE* surface_obj, float xoffset, float yoffset, float zoffset, int flags) {
    #ifdef _WIN32

    // Make sure the object is a surface and slected image is valid
    if(surface_obj == nullptr || surface_obj->rHo.Identifier != SurfaceID || surface_obj->selected == nullptr || surface_obj->selectedIsValid == false) {
        return;
    }

    cSurface* target = surface_obj->selected;

    int target_w, target_h, target_d;
    target->GetInfo(target_w, target_h, target_d);

    // Surface object images always have 24bit depth so theres no need to handle anything else
    cSurface* temp = create_surface(target_w, target_h, 24, SurfaceType::Memory, (SurfaceDriver)target->GetDriver());

    if(flags & FillRed || flags & FillGreen || flags & FillBlue) {
        // size_t bufsize = target_w * target_h * 3;      // In bytes, BGR layout, 1 pixel = 3bytes
        uint8_t* buf = temp->LockBuffer();

        fill_buffer_with_noise(buf, target_w, target_h, temp->GetDepth(), xoffset, yoffset, zoffset, flags);
        temp->UnlockBuffer(buf);    // you can pass a nullptr here and it will work!
    }

    if(flags & FillAlpha) {
        if(!temp->HasAlpha()) {
            temp->CreateAlpha();
        }

        uint8_t* buf = temp->LockAlpha();
        fill_alpha_buffer_with_noise(buf, target_w, target_h, xoffset, yoffset, zoffset, flags);
        temp->UnlockAlpha();
    }

    temp->Blit(*target);
    delete temp;
    surface_obj->rc.rcChanged = true;

    #endif
}





// Fill raw buffer with noise
// surface object always uses 24bit depth so other depths are not supported now
void Extension::fill_buffer_with_noise(uint8_t* buf, int width, int height, int depth, float xoffset, float yoffset, float zoffset, int flags) {
    size_t buf_index;
    uint8_t noise_val;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    assert(depth == 24);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if(flags & Only2D) {
                noise_val = (uint8_t)get_noise2D(x + xoffset, y + yoffset);
            } else {
                noise_val = (uint8_t)get_noise3D(x + xoffset, y + yoffset, zoffset);
            }

            if(flags & FillRed) {
                r = noise_val;
            }

            if(flags & FillGreen) {
                g = noise_val;
            }

            if(flags & FillBlue) {
                b = noise_val;
            }

            buf_index = (x + (y * width)) * 3;

            // BGR layout
            buf[buf_index + 0] = b;
            buf[buf_index + 1] = g;
            buf[buf_index + 2] = r;
        }
    }
}

void Extension::fill_alpha_buffer_with_noise(uint8_t* buf, int width, int height, float xoffset, float yoffset, float zoffset, int flags) {
    size_t buf_index;
    uint8_t noise_val;
    uint8_t alpha = 0;

    assert(flags & FillAlpha);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            noise_val = (uint8_t)get_noise3D(x + xoffset, y + yoffset, zoffset);

            alpha = noise_val;

            // 1 byte = 1 pixel
            buf_index = (x + (y * width));

            buf[buf_index] = alpha;
        }
    }
}
