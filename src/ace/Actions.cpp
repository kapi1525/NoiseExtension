#include "Common.hpp"



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
	#if EditorBuild
	if(type < 0 || type > FastNoiseLite::DomainWarpType_BasicGrid) {
		DarkEdif::MsgBox::WarningOK(_T("Domain warp > Set type"), _T("Set domain warp action expects one of domain warp types (see: Domain warp types expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
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
		DarkEdif::MsgBox::WarningOK(_T("Domain warp > Set rotation type 3D"), _T("Set rotation type 3D action expects one of rotation types 3d (see: Rotation type 3D expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
	}
	#endif
	warp.rotation_type_3d = static_cast<FastNoiseLite::RotationType3D>(type);
	fnl_warp.SetRotationType3D(warp.rotation_type_3d);
}


void Extension::set_warp_fractal_type(int type) {
	#if EditorBuild
	if(type != FastNoiseLite::FractalType_None && (type < FastNoiseLite::FractalType_DomainWarpProgressive || type > FastNoiseLite::FractalType_DomainWarpIndependent)) {
		DarkEdif::MsgBox::WarningOK(_T("Domain warp > Set fractal type"), _T("Set fractal type action expects one of fractal types (see: Fractal type expressions) but got random value.\nNote: This warning only shows up in Fusion editor so you can fix your events."));
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



void Extension::fill_surface_obj_with_noise(RunObject* surface_obj, float xoffset, float yoffset, float zoffset, int flags) {
    #ifdef _WIN32

    // Make sure the object is a surface
    if(surface_obj == nullptr || surface_obj->get_rHo()->Identifier != SurfaceID) {
        return;
    }

    SURFACE& surface_rd = *(SURFACE*)surface_obj;

    // Make sure the surface slected image is valid
    if(surface_rd.selected == nullptr || surface_rd.selectedIsValid == false) {
        return;
    }

    cSurface* target = surface_rd.selected;

    if(!target->IsValid()) {
        return;
    }


    int target_w, target_h, target_d;
    target->GetInfo(target_w, target_h, target_d);

    // cSurface* temp = create_surface(target_w, target_h, 24, SurfaceType::Memory, (SurfaceDriver)target->GetDriver());

    if(flags & FillRed || flags & FillGreen || flags & FillBlue) {
        uint8_t* buf = target->LockBuffer();

        if(buf == nullptr) {
            DarkEdif::MsgBox::Error(_T("Unsupported"), _T("LockBuffer() failed, cSurface type unsupported?"), target_d);
            return;
        }

        PixelFormat format;

        switch(target_d) {
        case 24:
            format = PixelFormat::BGR24; break;
        case 32:
            format = PixelFormat::BGR32; break;
        default:
            DarkEdif::MsgBox::Error(_T("Unsupported"), _T("Unsupported cSurface depth = %d"), target_d);
            return;
        }

        // Pitch = size between lines in bytes.
        fill_buffer_with_noise(buf, target_w, target_h, target->GetPitch(), format, xoffset, yoffset, zoffset, flags);
        target->UnlockBuffer(buf);    // you can pass a nullptr here and it will work!
    }

    if(flags & FillAlpha || flags & FillAlpha0 || flags & FillAlpha255) {
        if(!target->HasAlpha()) {
            target->CreateAlpha();
        }

        uint8_t* buf = target->LockAlpha();

        if(buf == nullptr) {
            DarkEdif::MsgBox::Error(_T("Unsupported"), _T("LockAlpha() failed, cSurface type unsupported?"), target_d);
            return;
        }

        fill_buffer_with_noise(buf, target_w, target_h, target->GetAlphaPitch(), PixelFormat::A8, xoffset, yoffset, zoffset, flags);
        target->UnlockAlpha();
    }

    surface_rd.rc.rcChanged = true;

    #endif
}



void Extension::fill_buffer_with_noise_bgr24(uint8_t* buf, int width, int height, int pitch, float xoffset, float yoffset, float zoffset, int flags) {
    uint8_t noise_val = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (flags & Only2D)
                noise_val = (uint8_t)get_noise2D(x + xoffset, y + yoffset);
            else
                noise_val = (uint8_t)get_noise3D(x + xoffset, y + yoffset, zoffset);

            const size_t buf_index = (x * 3) + (y * pitch);

            if (flags & FillBlue)
                buf[buf_index + 0] = noise_val;

            if (flags & FillGreen)
                buf[buf_index + 1] = noise_val;

            if (flags & FillRed)
                buf[buf_index + 2] = noise_val;
        }
    }
}

void Extension::fill_buffer_with_noise_bgr32(uint8_t* buf, int width, int height, int pitch, float xoffset, float yoffset, float zoffset, int flags) {
    uint8_t noise_val = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (flags & Only2D)
                noise_val = (uint8_t)get_noise2D(x + xoffset, y + yoffset);
            else
                noise_val = (uint8_t)get_noise3D(x + xoffset, y + yoffset, zoffset);

            const size_t buf_index = (x * 4) + (y * pitch);

            if (flags & FillBlue)
                buf[buf_index + 0] = noise_val;

            if (flags & FillGreen)
                buf[buf_index + 1] = noise_val;

            if (flags & FillRed)
                buf[buf_index + 2] = noise_val;
        }
    }
}

void Extension::fill_buffer_with_noise_a8(uint8_t* buf, int width, int height, int pitch, float xoffset, float yoffset, float zoffset, int flags) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const size_t buf_index = (x) + (y * pitch);

            if (flags & FillAlpha) {
                if (flags & Only2D)
                    buf[buf_index] = (uint8_t)get_noise2D(x + xoffset, y + yoffset);
                else
                    buf[buf_index] = (uint8_t)get_noise3D(x + xoffset, y + yoffset, zoffset);
            }

            if (flags & FillAlpha0)
                buf[buf_index] = 0;

            if (flags & FillAlpha255)
                buf[buf_index] = 255;
        }
    }
}

void Extension::fill_buffer_with_noise_rgba32(uint8_t* buf, int width, int height, int pitch, float xoffset, float yoffset, float zoffset, int flags) {
    uint8_t noise_val = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (flags & Only2D)
                noise_val = (uint8_t)get_noise2D(x + xoffset, y + yoffset);
            else
                noise_val = (uint8_t)get_noise3D(x + xoffset, y + yoffset, zoffset);

            const size_t buf_index = (x * 4) + (y * pitch);

            if (flags & FillRed)
                buf[buf_index + 0] = noise_val;

            if (flags & FillGreen)
                buf[buf_index + 1] = noise_val;

            if (flags & FillBlue)
                buf[buf_index + 2] = noise_val;

            if (flags & FillAlpha)
                buf[buf_index + 3] = noise_val;

            if (flags & FillAlpha0)
                buf[buf_index + 3] = 0;

            if (flags & FillAlpha255)
                buf[buf_index + 3] = 255;
        }
    }
}

void Extension::fill_buffer_with_noise(uint8_t* buf, int width, int height, int pitch, PixelFormat format, float xoffset, float yoffset, float zoffset, int flags) {
    // auto start = std::chrono::high_resolution_clock::now();

    // FIXME: Rethink

    switch (format) {
    case PixelFormat::BGR24:  fill_buffer_with_noise_bgr24 (buf, width, height, pitch, xoffset, yoffset, zoffset, flags); break;
    case PixelFormat::BGR32:  fill_buffer_with_noise_bgr32 (buf, width, height, pitch, xoffset, yoffset, zoffset, flags); break;
    case PixelFormat::A8:     fill_buffer_with_noise_a8    (buf, width, height, pitch, xoffset, yoffset, zoffset, flags); break;
    case PixelFormat::RGBA32: fill_buffer_with_noise_rgba32(buf, width, height, pitch, xoffset, yoffset, zoffset, flags); break;
    }

    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // DarkEdif::MsgBox::Info(_T("This took:"), _T("%lldms\n"), duration);
}

#ifdef __wasi__
void WASM_FUNC_EXPORT(fill_buffer_with_noise)(Extension* extPtr, uint8_t* buf, int width, int height, float xoffset, float yoffset, float zoffset, int flags) {
    extPtr->fill_buffer_with_noise(buf, width, height, width * 4, PixelFormat::RGBA32, xoffset, yoffset, zoffset, flags);
}
#endif