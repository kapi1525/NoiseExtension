#include "Common.hpp"
#include <cctype>
#include <charconv>

#ifdef PI
	#undef PI
#endif
#define PI 3.141592741f



int Extension::current_noise_seed() {
	return noise.seed;
}

int Extension::string_to_seed(const TCHAR* string) {
    #if UniBuild == 1
    // on windows unicode builds, string first has to be converted from utf16 to utf8
    auto converted_text = DarkEdif::TStringToUTF8(std::tstring_view(string));
    auto text = std::string_view(converted_text);
    #else
    // android and wasm, no conversion needed.
    auto text = std::string_view(string);
    #endif

    // Trim whitespace
    size_t start = 0;
    size_t end = 0;

    for (size_t i = 0; i < text.size(); i++) {
        if(!std::isspace(text[i])) {
            start = i;
            break;
        }
    }

    for (size_t i = text.size() - 1; i > 0; i--) {
        if(!std::isspace(text[i])) {
            end = i;
            break;
        }
    }

    text = text.substr(start, start - end);

    bool is_number = true;

    for (size_t i = 0; i < text.size(); i++) {
        if(!std::isdigit(text[i]) && !(i == 0 && (text[i] == '-' || text[i] == '+'))) {
            is_number = false;
            break;
        }
    }

    if(is_number) {
        int seed = 0;

        // on error assumbe the number is to big for conversion.
        auto result = std::from_chars(text.data(), text.data() + text.size(), seed);

        if(result.ec == std::errc{}) {
            // no error
            return seed;
        }
    }

    // either its not a number or the number is too big to be converted
    // crc32
    uint32_t divisor = 0xEDB88320;
    uint32_t data = 0xffffffff;

    for (size_t i = 0; i < text.size(); i++) {
        data ^= text[i];
        for (uint_fast8_t j = 0; j < 8; j++) {
            if (data & 1) {
                data = (data >> 1) ^ divisor;
            } else {
                data >>= 1;
            }
        }
    }

    data ^= 0xffffffff;

    return data;
}



float Extension::get_noise3D(float x, float y, float z) {
    if(warp.enabled) {
        fnl_warp.DomainWarp(x, y, z);
    }
	return map_noise_value(fnl_noise.GetNoise(x, y, z));
}

float Extension::get_noise2D(float x, float y) {
    if(warp.enabled) {
        fnl_warp.DomainWarp(x, y);
    }
	return map_noise_value(fnl_noise.GetNoise(x, y));
}

float Extension::get_noise1D(float x) {
    return get_noise2D(x, 0.f);
}

float Extension::get_looping_noise1D(float x, float xoffset, float xsize) {
	float XPos = x - xoffset;
	float Radius = xsize / (PI * 2.0f);
	float AngleStep = 360.f / xsize;
	float Angle = XPos * AngleStep;
	Angle = Angle * PI / 180.f;

    return get_noise2D((Radius * cos(Angle)), (Radius * sin(Angle)));
}



// Constant returns
int Extension::always_0() {
    return 0;
}

int Extension::always_1() {
    return 1;
}

int Extension::always_2() {
    return 2;
}

int Extension::always_3() {
    return 3;
}

int Extension::always_4() {
    return 4;
}

int Extension::always_5() {
    return 5;
}

int Extension::always_6() {
    return 6;
}



// Current settings for noise
int Extension::current_noise_type() {
	return noise.type;
}

int Extension::current_noise_rotation_type_3d() {
    return noise.rotation_type_3d;
}

int Extension::current_noise_fractal_type() {
	return noise.fractal_type;
}

int Extension::current_noise_cellular_function() {
	return noise.cellular_function;
}

int Extension::current_noise_cellular_return_type() {
	return noise.cellular_return_type;
}


// Current settings for domain warp
int Extension::is_warp_enabled() {
    return warp.enabled;
}

int Extension::current_warp_seed() {
    return warp.seed;
}

int Extension::current_warp_type() {
    return warp.type;
}

int Extension::current_warp_rotation_type_3d() {
    return warp.rotation_type_3d;
}

int Extension::current_warp_fractal_type() {
    return warp.fractal_type;
}


// Fill surface with noise flags
int Extension::default_flags() {
    return FillSurfaceFlags::DefaultFlags;
}

int Extension::fill_red() {
    return FillSurfaceFlags::FillRed;
}

int Extension::fill_green() {
    return FillSurfaceFlags::FillGreen;
}

int Extension::fill_blue() {
    return FillSurfaceFlags::FillBlue;
}

int Extension::fill_alpha() {
    return FillSurfaceFlags::FillAlpha;
}

int Extension::only_2d() {
    return FillSurfaceFlags::Only2D;
}

int Extension::fill_alpha0() {
    return FillSurfaceFlags::FillAlpha0;
}

int Extension::fill_alpha255() {
    return FillSurfaceFlags::FillAlpha255;
}