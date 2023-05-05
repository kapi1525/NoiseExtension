// This file handles property updates to smart properties

#if EditorBuild

#include <functional>
#include <map>
#include "Common.h"



// versions v0.9.4 --- v1.0.1
struct EDITDATA_v16 {
    NO_DEFAULT_CTORS(EDITDATA_v16)
    extHeader eHeader;
    short editdata_rev;

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

// versions v0.9.1 --- v0.9.3
struct EDITDATA_v13 {
    NO_DEFAULT_CTORS(EDITDATA_v13)
    extHeader eHeader;

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



struct CustomPropertyReader : DarkEdif::Properties::PropertyReader {
    const DarkEdif::Properties::ConverterState* convState;

    // Start the property reader/converter. Return ConverterUnsuitable if the converter isn't usable.
    void Initialise(DarkEdif::Properties::ConverterState& convState, DarkEdif::Properties::ConverterReturn* const convRet);

    // Get property by ID.
    // Note that IDs will always be increasing, but you should program GetProperty() as if IDs can be skipped (non-monotonic).
    void GetProperty(size_t id, DarkEdif::Properties::ConverterReturn* const convRet);
    void GetPropertyCheckbox(size_t id, DarkEdif::Properties::ConverterReturn* const convRet);
};



void CustomPropertyReader::Initialise(DarkEdif::Properties::ConverterState& convState, DarkEdif::Properties::ConverterReturn* const convRet) {
    this->convState = &convState;

    if(convState.oldEdPtrProps == nullptr && convState.oldEdPtr != nullptr && convState.oldEdPtr->eHeader.extVersion >= 13 && convState.oldEdPtr->eHeader.extVersion <= 20) {
        return convRet->Return_OK(nullptr, 0);
    }

    return convRet->Return_ConverterUnsuitable();
}



void CustomPropertyReader::GetProperty(size_t id, DarkEdif::Properties::ConverterReturn* const convRet) {
    auto freedata = [](const void* d) { delete d; };

    // lambdas are nice
    auto ret_float = [&](const float f) { float* d = new float(f); convRet->Return_OK(d, sizeof(float), freedata); };
    auto ret_int = [&](const int i) { int* d = new int(i); convRet->Return_OK(d, sizeof(int), freedata); };
    auto ret_str = [&](const char* str) { convRet->Return_OK(_strdup(str), strnlen_s(str, 128), freedata); };
    auto ret_combo = [&](const std::string values[], const unsigned int index) { ret_str(values[index].c_str()); };

    auto prop = CurLang["Properties"][id];
    auto version = convState->oldEdPtr->eHeader.extVersion;

    std::map<const char*, std::function<void()>> prop_map;


    // Combobox options for properties
    const std::string noise_types[] = {
        "OpenSimplex2",
        "OpenSimplex2S",
        "Cellular",
        "Perlin",
        "ValueCubic",
        "Value"
    };

    const std::string cellular_distance_functons[] = {
        "Euclidean",
        "EuclideanSq",
        "Manhattan",
        "Hybrid"
    };

    const std::string cellular_ret_types[] = {
        "CellValue",
        "Distance",
        "Distance2",
        "Distance2Add",
        "Distance2Sub",
        "Distance2Mul",
        "Distance2Div"
    };

    const std::string fractal_types[] = {
        "None",
        "FBm",
        "Rigid",
        "PingPong",
        "None"      // Due to mistake there was a 5th fractal type in some versions
    };


    // Versions v0.9.4 --- v1.0.1
    if(version >= 16) {
        const EDITDATA_v16& ed = *(EDITDATA_v16*)convState->oldEdPtr;

        prop_map = {
            {"Seed",                        [&]() { ret_str(std::to_string(ed.noise_seed).c_str()); }},
            {"Noise type",                  [&]() { ret_combo(noise_types, ed.noise_type); }},
            {"Noise frequency",             [&]() { ret_float(ed.noise_frequency); }},
            {"Fractal type",                [&]() { ret_combo(fractal_types, ed.fractal_type); }},
            {"Fractal octaves",             [&]() { ret_int(ed.fractal_octaves); }},
            {"Fractal lacunarity",          [&]() { ret_float(ed.fractal_lacunarity); }},
            {"Fractal gain",                [&]() { ret_float(ed.fractal_gain); }},
            {"Fractal weighted strength",   [&]() { ret_float(ed.fractal_weighted_strength); }},
            {"Fractal PingPong strength",   [&]() { ret_float(ed.fractal_pingpong_strength); }},
            {"Cellular distance function",  [&]() { ret_combo(cellular_distance_functons, ed.cellular_distance_func); }},
            {"Cellular return type",        [&]() { ret_combo(cellular_ret_types, ed.cellular_ret_type); }},
            {"Cellular jitter",             [&]() { ret_float(ed.cellular_jitter); }}
        };
    }

    // Versions v0.9.1 --- v0.9.3
    else if(version >= 13) {
        const EDITDATA_v13& ed = *(EDITDATA_v13*)convState->oldEdPtr;

        prop_map = {
            {"Seed",                        [&]() { ret_str(std::to_string(ed.noise_seed).c_str()); }},
            {"Noise type",                  [&]() { ret_combo(noise_types, ed.noise_type); }},
            {"Noise frequency",             [&]() { ret_float(ed.noise_frequency); }},
            {"Fractal type",                [&]() { ret_combo(fractal_types, ed.fractal_type); }},
            {"Fractal octaves",             [&]() { ret_int(ed.fractal_octaves); }},
            {"Fractal lacunarity",          [&]() { ret_float(ed.fractal_lacunarity); }},
            {"Fractal weighted strength",   [&]() { ret_float(ed.fractal_weighted_strength); }},
            {"Fractal PingPong strength",   [&]() { ret_float(ed.fractal_pingpong_strength); }},
            {"Cellular distance function",  [&]() { ret_combo(cellular_distance_functons, ed.cellular_distance_func); }},
            {"Cellular return type",        [&]() { ret_combo(cellular_ret_types, ed.cellular_ret_type); }},
            {"Cellular jitter",             [&]() { ret_float(ed.cellular_jitter); }}
        };
    }


    try {
        // Try to convert property, if it fails it creates out_of_range exception
        prop_map.at(prop["Title"])();
    }
    catch(std::out_of_range x) {
        // Load defaults from json so pre smart converter cant break anything
        auto state = prop["DefaultState"];

        switch(state.type) {
        case json_integer:
            return ret_int(state);

        case json_double:
            return ret_float(static_cast<const float>(state.u.dbl));

        case json_string:
            return ret_str(state);

        case json_none:
            return convRet->Return_Pass();

        default:
            DarkEdif::MsgBox::Error(_T("Property conversion error"), _T("Failed to convert old property format, your .mfa may be corrupted.\nProperties have been reset."));
            convRet->Return_ConverterUnsuitable();
        }
    }
}



void CustomPropertyReader::GetPropertyCheckbox(size_t id, DarkEdif::Properties::ConverterReturn* const convRet) {
    return convRet->Return_Pass();
}


static CustomPropertyReader customPropertyReader;

DarkEdif::Properties::PropertyReader* EDITDATA::UserConverter() {
    return &customPropertyReader;
}

#endif