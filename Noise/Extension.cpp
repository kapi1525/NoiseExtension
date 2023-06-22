#include <map>
#include "Common.h"


///
/// EXTENSION CONSTRUCTOR/DESTRUCTOR
///

#ifdef _WIN32
Extension::Extension(RUNDATA * _rdPtr, EDITDATA * edPtr, CreateObjectInfo * cobPtr) :
	rdPtr(_rdPtr), rhPtr(_rdPtr->rHo.AdRunHeader), Runtime(&_rdPtr->rHo)
#elif defined(__ANDROID__)
Extension::Extension(RuntimeFunctions & runFuncs, EDITDATA * edPtr, jobject javaExtPtr) :
	runFuncs(runFuncs), javaExtPtr(javaExtPtr, "Extension::javaExtPtr from Extension ctor"), Runtime(runFuncs, this->javaExtPtr)
#else
Extension::Extension(RuntimeFunctions & runFuncs, EDITDATA * edPtr, void * objCExtPtr) :
	runFuncs(runFuncs), objCExtPtr(objCExtPtr), Runtime(runFuncs, this->objCExtPtr)
#endif
{
	// Actions
	{
        // Noise settings
		LinkAction(1, set_noise_type);

		LinkAction(0, set_noise_seed);
		LinkAction(2, set_noise_frequency);
		LinkAction(12, set_noise_rotation_type_3d);

		LinkAction(3, set_noise_fractal_type);
		LinkAction(4, set_noise_fractal_octaves);
		LinkAction(5, set_noise_fractal_lacunarity);
		LinkAction(11, set_noise_fractal_gain);
		LinkAction(6, set_noise_fractal_weighted);
		LinkAction(7, set_noise_fractal_pingpong);

		LinkAction(8, set_noise_cellular_distance_function);
		LinkAction(9, set_noise_cellular_return_type);
		LinkAction(10, set_noise_cellular_jitter);

        // Warp settings
        LinkAction(13, enable_warp);
        LinkAction(14, disable_warp);

        LinkAction(15, set_warp_type);
        LinkAction(16, set_warp_amp);

        LinkAction(17, set_warp_seed);
        LinkAction(18, set_warp_frequency);
        LinkAction(19, set_warp_rotation_type_3d);

        LinkAction(20, set_warp_fractal_type);
        LinkAction(21, set_warp_fractal_octaves);
        LinkAction(22, set_warp_fractal_lacunarity);
        LinkAction(23, set_warp_fractal_gain);
        LinkAction(24, set_warp_fractal_weighted);
	}

	// Conditions
	{
	}

	// Expressions
	{

		LinkExpression(2, get_noise3D);
		LinkExpression(3, get_noise2D);
		LinkExpression(4, get_noise1D);
		LinkExpression(5, get_looping_noise1D);

		LinkExpression(1, string_to_seed);

        // Noise types
		LinkExpression(6, always_0);
		LinkExpression(7, always_1);
		LinkExpression(8, always_2);
		LinkExpression(9, always_3);
		LinkExpression(10, always_4);
		LinkExpression(11, always_5);

        // Rotation type 3D
        // "none" reuses "none" fractal type expression (id 12)
		LinkExpression(31, always_1);
		LinkExpression(32, always_2);

        // Fractal types
		LinkExpression(12, always_0);
		LinkExpression(13, always_1);
		LinkExpression(14, always_2);
		LinkExpression(15, always_3);

        // Cellular distance functions
		LinkExpression(16, always_0);
		LinkExpression(17, always_1);
		LinkExpression(18, always_2);
		LinkExpression(19, always_3);

        // Cellular return types
		LinkExpression(20, always_0);
		LinkExpression(21, always_1);
		LinkExpression(22, always_2);
		LinkExpression(23, always_3);
		LinkExpression(24, always_4);
		LinkExpression(25, always_5);
		LinkExpression(26, always_6);

        // Warp types
        // id 6 is reused for "OpenSimplex2"
        LinkExpression(34, always_1);
        LinkExpression(35, always_2);

        // Current noise settings
		LinkExpression(0, current_noise_seed);
		LinkExpression(27, current_noise_type);
		LinkExpression(33, current_noise_rotation_type_3d);
		LinkExpression(28, current_noise_fractal_type);
		LinkExpression(29, current_noise_cellular_function);
		LinkExpression(30, current_noise_cellular_return_type);

        // Current warp settings
        LinkExpression(38, is_warp_enabled);
        LinkExpression(39, current_warp_seed);
        LinkExpression(40, current_warp_type);
        LinkExpression(41, current_warp_rotation_type_3d);
        LinkExpression(42, current_warp_fractal_type);
	}

	// Properties
	try {
        const std::map<std::string, FastNoiseLite::NoiseType> noise_type_ids = {
            {"OpenSimplex2",        FastNoiseLite::NoiseType_OpenSimplex2},
            {"OpenSimplex2S",       FastNoiseLite::NoiseType_OpenSimplex2S},
            {"Cellular",            FastNoiseLite::NoiseType_Cellular},
            {"Perlin",              FastNoiseLite::NoiseType_Perlin},
            {"ValueCubic",          FastNoiseLite::NoiseType_ValueCubic},
            {"Value",               FastNoiseLite::NoiseType_Value}
        };

        const std::map<std::string, FastNoiseLite::RotationType3D> rotation_type_3d_ids = {
            {"None",                FastNoiseLite::RotationType3D_None},
            {"Improve XY planes",   FastNoiseLite::RotationType3D_ImproveXYPlanes},
            {"Improve XZ planes",   FastNoiseLite::RotationType3D_ImproveXZPlanes}
        };

        const std::map<std::string, FastNoiseLite::FractalType> noise_fractal_type_ids = {
            {"None",                FastNoiseLite::FractalType_None},
            {"FBm",                 FastNoiseLite::FractalType_FBm},
            {"Rigid",               FastNoiseLite::FractalType_Ridged},
            {"PingPong",            FastNoiseLite::FractalType_PingPong}
        };

        const std::map<std::string, FastNoiseLite::CellularDistanceFunction> cellular_distance_function_ids = {
            {"Euclidean",           FastNoiseLite::CellularDistanceFunction_Euclidean},
            {"EuclideanSq",         FastNoiseLite::CellularDistanceFunction_EuclideanSq},
            {"Manhattan",           FastNoiseLite::CellularDistanceFunction_Manhattan},
            {"Hybrid",              FastNoiseLite::CellularDistanceFunction_Hybrid}
        };

        const std::map<std::string, FastNoiseLite::CellularReturnType> cellular_return_type_ids = {
            {"CellValue",           FastNoiseLite::CellularReturnType_CellValue},
            {"Distance",            FastNoiseLite::CellularReturnType_Distance},
            {"Distance2",           FastNoiseLite::CellularReturnType_Distance2},
            {"Distance2Add",        FastNoiseLite::CellularReturnType_Distance2Add},
            {"Distance2Sub",        FastNoiseLite::CellularReturnType_Distance2Sub},
            {"Distance2Mul",        FastNoiseLite::CellularReturnType_Distance2Mul},
            {"Distance2Div",        FastNoiseLite::CellularReturnType_Distance2Div}
        };


        const std::map<std::string, FastNoiseLite::DomainWarpType> warp_type_ids = {
            {"OpenSimplex2",        FastNoiseLite::DomainWarpType_OpenSimplex2},
            {"OpenSimplex2Reduced", FastNoiseLite::DomainWarpType_OpenSimplex2Reduced},
            {"BasicGrid",           FastNoiseLite::DomainWarpType_BasicGrid},
        };

        const std::map<std::string, FastNoiseLite::FractalType> warp_fractal_type_ids = {
            {"None",                FastNoiseLite::FractalType_None},
            {"Progressive",         FastNoiseLite::FractalType_DomainWarpProgressive},
            {"Independent",         FastNoiseLite::FractalType_DomainWarpIndependent},
        };


		set_noise_type(noise_type_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Noise type"))));

        set_noise_seed(string_to_seed(edPtr->Props.GetPropertyStr("Noise seed").c_str()));
		set_noise_frequency(edPtr->Props.GetPropertyNum("Noise frequency"));
		set_noise_rotation_type_3d(rotation_type_3d_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Rotation type 3D"))));

		set_noise_fractal_type(noise_fractal_type_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Fractal type"))));
		set_noise_fractal_octaves((int)edPtr->Props.GetPropertyNum("Fractal octaves"));
		set_noise_fractal_lacunarity(edPtr->Props.GetPropertyNum("Fractal lacunarity"));
		set_noise_fractal_gain(edPtr->Props.GetPropertyNum("Fractal gain"));
		set_noise_fractal_weighted(edPtr->Props.GetPropertyNum("Fractal weighted strength"));
		set_noise_fractal_pingpong(edPtr->Props.GetPropertyNum("Fractal PingPong strength"));

		set_noise_cellular_distance_function(cellular_distance_function_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Cellular distance function"))));
		set_noise_cellular_return_type(cellular_return_type_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Cellular return type"))));
		set_noise_cellular_jitter(edPtr->Props.GetPropertyNum("Cellular jitter"));


        {
            std::string dwtype = DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Domain warp type"));
            if(dwtype.compare("Disabled") == 0) {
                disable_warp();
                set_warp_type(0);
            }
            else {
                enable_warp();
                set_warp_type(warp_type_ids.at(dwtype));
            }
        }

        set_warp_amp(edPtr->Props.GetPropertyNum("Domain warp amplitude"));

        set_warp_seed(string_to_seed(edPtr->Props.GetPropertyStr("Domain warp seed").c_str()));
        set_warp_frequency(edPtr->Props.GetPropertyNum("Domain warp frequency"));
        set_warp_rotation_type_3d(rotation_type_3d_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Domain warp rotation type 3D"))));

        set_warp_fractal_type(warp_fractal_type_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("DW fractal type"))));
		set_warp_fractal_octaves((int)edPtr->Props.GetPropertyNum("DW fractal octaves"));
		set_warp_fractal_lacunarity(edPtr->Props.GetPropertyNum("DW fractal lacunarity"));
		set_warp_fractal_gain(edPtr->Props.GetPropertyNum("DW fractal gain"));
		set_warp_fractal_weighted(edPtr->Props.GetPropertyNum("DW fractal weighted strength"));
    }
    catch(std::out_of_range x) {
        DarkEdif::MsgBox::Error(_T("Corrupted properties"), _T("Noise properties may be corrupted.\n%s."), DarkEdif::UTF8ToTString(x.what()).c_str());
    }
}

Extension::~Extension() {
}



REFLAG Extension::Handle() {
	return REFLAG::ONE_SHOT;
}

REFLAG Extension::Display() {
	return REFLAG::DISPLAY;
}


short Extension::FusionRuntimePaused() {
	return 0;
}

short Extension::FusionRuntimeContinued() {
	return 0;
}


// These are called if there's no function linked to an ID
void Extension::UnlinkedAction(int ID) {
	DarkEdif::MsgBox::Error(_T("Extension::UnlinkedAction() called"), _T("Running a fallback for action ID %d. Make sure you ran LinkAction()."), ID);
}

long Extension::UnlinkedCondition(int ID) {
	DarkEdif::MsgBox::Error(_T("Extension::UnlinkedCondition() called"), _T("Running a fallback for condition ID %d. Make sure you ran LinkCondition()."), ID);
	return 0;
}

long Extension::UnlinkedExpression(int ID) {
	DarkEdif::MsgBox::Error(_T("Extension::UnlinkedExpression() called"), _T("Running a fallback for expression ID %d. Make sure you ran LinkExpression()."), ID);
	// Unlinked A/C/E is fatal error , but try not to return null string and definitely crash it
	if ((size_t)ID < Edif::SDK->ExpressionInfos.size() && Edif::SDK->ExpressionInfos[ID]->Flags.ef == ExpReturnType::String)
		return (long)Runtime.CopyString(_T(""));
	return 0;
}
