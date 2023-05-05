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
		LinkAction(0, set_seed);

		LinkAction(1, set_noise_type);
		LinkAction(2, set_noise_frequency);
		LinkAction(12, set_rotation_type_3d);

		LinkAction(3, set_fractal_type);
		LinkAction(4, set_fractal_octaves);
		LinkAction(5, set_fractal_lacunarity);
		LinkAction(11, set_fractal_gain);
		LinkAction(6, set_fractal_weighted);
		LinkAction(7, set_fractal_pingpong);

		LinkAction(8, set_cellular_distance_function);
		LinkAction(9, set_cellular_return_type);
		LinkAction(10, set_cellular_jitter);
	}

	// Conditions
	{
	}

	// Expressions
	{
		LinkExpression(0, get_seed);
		LinkExpression(1, string_to_seed);

		LinkExpression(2, get_noise3D);
		LinkExpression(3, get_noise2D);
		LinkExpression(4, get_noise1D);
		LinkExpression(5, get_looping_noise1D);

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

		LinkExpression(27, current_noise_type);
		LinkExpression(33, current_rotation_type_3d);
		LinkExpression(28, current_fractal_type);
		LinkExpression(29, current_cellular_function);
		LinkExpression(30, current_cellular_return_type);
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

        const std::map<std::string, FastNoiseLite::FractalType> fractal_type_ids = {
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


		set_seed(string_to_seed(edPtr->Props.GetPropertyStr("Seed").c_str()));

		set_noise_type(noise_type_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Noise type"))));
		set_noise_frequency(edPtr->Props.GetPropertyNum("Noise frequency"));
		set_rotation_type_3d(rotation_type_3d_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Rotation type 3D"))));

		set_fractal_type(fractal_type_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Fractal type"))));
		set_fractal_octaves((int)edPtr->Props.GetPropertyNum("Fractal octaves"));
		set_fractal_lacunarity(edPtr->Props.GetPropertyNum("Fractal lacunarity"));
		set_fractal_gain(edPtr->Props.GetPropertyNum("Fractal gain"));
		set_fractal_weighted(edPtr->Props.GetPropertyNum("Fractal weighted strength"));
		set_fractal_pingpong(edPtr->Props.GetPropertyNum("Fractal PingPong strength"));

		set_cellular_distance_function(cellular_distance_function_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Cellular distance function"))));
		set_cellular_return_type(cellular_return_type_ids.at(DarkEdif::TStringToUTF8(edPtr->Props.GetPropertyStr("Cellular return type"))));
		set_cellular_jitter(edPtr->Props.GetPropertyNum("Cellular jitter"));
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
