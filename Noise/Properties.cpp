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
    auto prop = CurLang["Properties"][id];
    auto version_id = convState->oldEdPtr->eHeader.extVersion;

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
        "Ridged",
        "PingPong",
        "None"      // Due to mistake there was a 5th fractal type in some versions
    };


    // Assume its EDITDATA_v16, if its v13 it will be changed by an if statement bellow
    EDITDATA_v16* ed = (EDITDATA_v16*)convState->oldEdPtr;

    // Versions v0.9.1 --- v0.9.3
    // EDITDATA_v13 and v16 are simmilar so convert from v13 to v16
    if(version_id >= 13 && version_id <= 15) {
        const EDITDATA_v13* old_ed = (EDITDATA_v13*)convState->oldEdPtr;

        // TODO: Fix memory leak
        ed = (EDITDATA_v16*)malloc(sizeof(EDITDATA_v16));

        // Copy everything
        memcpy(&ed->eHeader, &old_ed->eHeader, sizeof(extHeader));
        ed->eHeader.extSize = sizeof(EDITDATA_v16);

        ed->noise_seed = old_ed->noise_seed;
        ed->noise_type = old_ed->noise_type;
        ed->noise_frequency = old_ed->noise_frequency;
        ed->fractal_type = old_ed->fractal_type;
        ed->fractal_octaves = old_ed->fractal_octaves;
        ed->fractal_lacunarity = old_ed->fractal_lacunarity;
        ed->fractal_weighted_strength = old_ed->fractal_weighted_strength;
        ed->fractal_pingpong_strength = old_ed->fractal_pingpong_strength;
        ed->cellular_distance_func = old_ed->cellular_distance_func;
        ed->cellular_ret_type = old_ed->cellular_ret_type;
        ed->cellular_jitter = old_ed->cellular_jitter;

        // Was added in v16
        ed->editdata_rev = 1;
        ed->fractal_gain = 0.5;
    }


    auto freedata = [](const void* ptr) { delete ptr; };
    auto ret_float = [&](const float f) { float* d = new float(f); convRet->Return_OK(d, sizeof(float), freedata); };
    auto ret_int = [&](const int i) { int* d = new int(i); convRet->Return_OK(d, sizeof(int), freedata); };
    auto ret_str = [&](const char* str) { convRet->Return_OK(_strdup(str), strnlen_s(str, 128), freedata); };
    auto ret_combo = [&](const std::string values[], const unsigned int index) { ret_str(values[index].c_str()); };


    // Versions v0.9.4 --- v1.0.1
    // Convert from EDITDATA_v16 to smart properties
    // NOTE: If property titles are changed they need to be updated here as well
    std::map<std::tstring, std::function<void()>> prop_map = {
        {_T("Noise seed"),                 [&]() { ret_str(std::to_string(ed->noise_seed).c_str()); }},
        {_T("Noise type"),                 [&]() { ret_combo(noise_types, ed->noise_type); }},
        {_T("Noise frequency"),            [&]() { ret_float(ed->noise_frequency); }},
        {_T("Fractal type"),               [&]() { ret_combo(fractal_types, ed->fractal_type); }},
        {_T("Fractal octaves"),            [&]() { ret_int(ed->fractal_octaves); }},
        {_T("Fractal lacunarity"),         [&]() { ret_float(ed->fractal_lacunarity); }},
        {_T("Fractal gain"),               [&]() { ret_float(ed->fractal_gain); }},
        {_T("Fractal weighted strength"),  [&]() { ret_float(ed->fractal_weighted_strength); }},
        {_T("Fractal PingPong strength"),  [&]() { ret_float(ed->fractal_pingpong_strength); }},
        {_T("Cellular distance function"), [&]() { ret_combo(cellular_distance_functons, ed->cellular_distance_func); }},
        {_T("Cellular return type"),       [&]() { ret_combo(cellular_ret_types, ed->cellular_ret_type); }},
        {_T("Cellular jitter"),            [&]() { ret_float(ed->cellular_jitter); }}
    };

    try {
        prop_map.at(DarkEdif::UTF8ToTString(std::string(prop["Title"])))();
    }
    catch(std::out_of_range x) {
        // Load defaults from json so pre smart converter cant break anything
        auto state = prop["DefaultState"];

        switch(state.type) {
        case json_integer:
            return ret_int(static_cast<const int>(state.u.integer));

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