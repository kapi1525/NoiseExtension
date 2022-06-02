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

		LinkAction(3, set_fractal_type);
		LinkAction(4, set_fractal_octaves);
		LinkAction(5, set_fractal_lacunarity);
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

		LinkExpression(6, open_simplex2);
		LinkExpression(7, open_simplex2s);
		LinkExpression(8, cellular);
		LinkExpression(9, perlin);
		LinkExpression(10, value_cubic);
		LinkExpression(11, value);
		
		LinkExpression(12, none);
		LinkExpression(13, fbm);
		LinkExpression(14, rigid);
		LinkExpression(15, pingpong);
		
		LinkExpression(16, euclidean);
		LinkExpression(17, euclidean_sq);
		LinkExpression(18, manhattan);
		LinkExpression(19, hybrid);
		
		LinkExpression(20, cell_value);
		LinkExpression(21, distance);
		LinkExpression(22, distance2);
		LinkExpression(23, distance2_add);
		LinkExpression(24, distance2_sub);
		LinkExpression(25, distance2_mul);
		LinkExpression(26, distance2_div);

		LinkExpression(27, current_noise_type);
		LinkExpression(28, current_fractal_type);
		LinkExpression(29, current_cellular_function);
		LinkExpression(30, current_cellular_return_type);
	}

	// Properties
	{
		set_seed(string_to_seed(edPtr->GetPropertyStr(0).c_str()));
		set_noise_type(edPtr->GetPropertyInt(1));
		set_noise_frequency(edPtr->GetPropertyFloat(2));
		set_fractal_type(edPtr->GetPropertyInt(3));
		set_fractal_octaves(edPtr->GetPropertyInt(4));
		set_fractal_lacunarity(edPtr->GetPropertyFloat(5));
		set_fractal_weighted(edPtr->GetPropertyFloat(6));
		set_fractal_pingpong(edPtr->GetPropertyFloat(7));
		set_cellular_distance_function(edPtr->GetPropertyInt(8));
		set_cellular_return_type(edPtr->GetPropertyInt(9));
		set_cellular_jitter(edPtr->GetPropertyFloat(10));
	}
}

Extension::~Extension() {
}


int EDITDATA::GetPropertyInt(int propID) {
	if (propID < 0 || (size_t)propID > CurLang["Properties"].u.array.length) {
		return 0;
	}

	const json_value &prop = CurLang["Properties"][propID];

	if (!_stricmp(prop["Type"], "Editbox Number") || !_stricmp(prop["Type"], "Combo Box")) {
		return *(int *)PropIndex(this, propID, nullptr);
	}
	else {
		return 0;
	}
}

float EDITDATA::GetPropertyFloat(int propID) {
	if (propID < 0 || (size_t)propID > CurLang["Properties"].u.array.length) {
		return 0.f;
	}

	const json_value &prop = CurLang["Properties"][propID];

	if (!_stricmp(prop["Type"], "Editbox Float")) {
		return *(float *)PropIndex(this, propID, nullptr);
	}
	else {
		return 0.f;
	}
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
	if ((size_t)ID < ::SDK->ExpressionInfos.size() && ::SDK->ExpressionInfos[ID]->Flags.ef == ExpReturnType::String)
		return (long)Runtime.CopyString(_T(""));
	return 0;
}
