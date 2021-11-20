#include "Common.h"


///
/// EXTENSION CONSTRUCTOR/DESTRUCTOR
///

#ifdef _WIN32
Extension::Extension(RUNDATA * _rdPtr, EDITDATA * edPtr, CreateObjectInfo * cobPtr) :
	rdPtr(_rdPtr), rhPtr(_rdPtr->rHo.AdRunHeader), Runtime(&_rdPtr->rHo), FusionDebugger(this)
#elif defined(__ANDROID__)
Extension::Extension(RuntimeFunctions & runFuncs, EDITDATA * edPtr, jobject javaExtPtr) :
	runFuncs(runFuncs), javaExtPtr(javaExtPtr, "Extension::javaExtPtr from Extension ctor"), Runtime(runFuncs, this->javaExtPtr), FusionDebugger(this)
#else
Extension::Extension(RuntimeFunctions & runFuncs, EDITDATA * edPtr, void * objCExtPtr) :
	runFuncs(runFuncs), objCExtPtr(objCExtPtr), Runtime(runFuncs, this->objCExtPtr), FusionDebugger(this)
#endif
{
	// Actions
	LinkAction(0, SetSeed);

	LinkAction(11, NoiseRequest3D);
	LinkAction(12, NoiseRequest2D);
	LinkAction(13, NoiseRequest1D);
	LinkAction(14, NoiseRequestLooping1D);
	
	LinkAction(15, CleanupRequest);
	LinkAction(16, CleanupRequests);

	LinkAction(1, SetNoiseType);
	LinkAction(2, SetNoiseFrequency);

	LinkAction(3, SetFractalType);
	LinkAction(4, SetFractalOctaves);
	LinkAction(5, SetFractalLacunarity);
	LinkAction(6, SetFractalWeighted);
	LinkAction(7, SetFractalPingPong);

	LinkAction(8, SetCellularDistanceFunction);
	LinkAction(9, SetCellularReturnType);
	LinkAction(10, SetCellularJitter);

	// Conditions
	LinkCondition(0, IsRequestReady);

	// Expressions
	LinkExpression(0, GetSeed);
	LinkExpression(1, StringToSeed);

	LinkExpression(2, GetNoise3D);
	LinkExpression(3, GetNoise2D);
	LinkExpression(4, GetNoise1D);
	LinkExpression(5, GetLoopingNoise1D);
	
	LinkExpression(31, GetRequestNoise3D);
	LinkExpression(32, GetRequestNoise2D);
	LinkExpression(33, GetRequestNoise1D);
	// TODO: LinkExpression(34, GetRequestLoopingNoise1D);

	LinkExpression(6, OpenSimplex2);
	LinkExpression(7, OpenSimplex2S);
	LinkExpression(8, Cellular);
	LinkExpression(9, Perlin);
	LinkExpression(10, ValueCubic);
	LinkExpression(11, Value);
	
	LinkExpression(12, None);
	LinkExpression(13, FBm);
	LinkExpression(14, Rigid);
	LinkExpression(15, PingPong);
	
	LinkExpression(16, Euclidean);
	LinkExpression(17, EuclideanSq);
	LinkExpression(18, Manhattan);
	LinkExpression(19, Hybrid);
	
	LinkExpression(20, CellValue);
	LinkExpression(21, Distance);
	LinkExpression(22, Distance2);
	LinkExpression(23, Distance2Add);
	LinkExpression(24, Distance2Sub);
	LinkExpression(25, Distance2Mul);
	LinkExpression(26, Distance2Div);

	LinkExpression(27, CurrentNoiseType);
	LinkExpression(28, CurrentFractalType);
	LinkExpression(29, CurrentCellularFunction);
	LinkExpression(30, CUrrentCellularReturnType);

	/*
		This is where you'd do anything you'd do in CreateRunObject in the original SDK

		It's the only place you'll get access to edPtr at runtime, so you should transfer
		anything from edPtr to the extension class here.

	*/

	// Don't use "this" inside these lambda functions, always ext.
	// There can be nothing in the [] section of the lambda.
	// If you're not sure about lambdas, you can remove this debugger stuff without any side effects;
	// it's just an example of how to use the debugger. You can view it in Fusion itself to see.
	FusionDebugger.AddItemToDebugger(
		// reader function for your debug item
		[](Extension *ext, std::tstring &writeTo) {
			writeTo = _T("My text is: ") + ext->exampleDebuggerTextItem;
		},
		// writer function (can be null if you don't want user to be able to edit it in debugger)
		[](Extension *ext, std::tstring &newText)
		{
			ext->exampleDebuggerTextItem = newText;
			return true; // accept the changes
		}, 500, NULL
	);

}

Extension::~Extension() {
	Requests.clear();
}


REFLAG Extension::Handle()
{
	/*
		If your extension will draw to the MMF window you should first
		check if anything about its display has changed :

			if (rdPtr->roc.rcChanged)
			  return REFLAG::DISPLAY;
			else
			  return REFLAG::NONE;

		You will also need to make sure you change this flag yourself
		to 1 whenever you want to redraw your object

		If your extension won't draw to the window, but it still needs
		to do something every MMF loop use :

			return REFLAG::NONE;

		If you don't need to do something every loop, use :

			return REFLAG::ONE_SHOT;

		This doesn't mean this function can never run again. If you want MMF
		to handle your object again (causing this code to run) use this function:

			Runtime.Rehandle();

		At the end of the loop this code will run

	*/

	// Will not be called next loop
	return REFLAG::ONE_SHOT;
}


REFLAG Extension::Display()
{
	/*
		If you return REFLAG_DISPLAY in Handle() this routine will run.
	*/

	// Ok
	return REFLAG::DISPLAY;
}

short Extension::FusionRuntimePaused()
{

	// Ok
	return 0;
}

short Extension::FusionRuntimeContinued()
{

	// Ok
	return 0;
}


// These are called if there's no function linked to an ID

void Extension::UnlinkedAction(int ID)
{
	DarkEdif::MsgBox::Error(_T("Extension::UnlinkedAction() called"), _T("Running a fallback for action ID %d. Make sure you ran LinkAction()."), ID);
}

long Extension::UnlinkedCondition(int ID)
{
	DarkEdif::MsgBox::Error(_T("Extension::UnlinkedCondition() called"), _T("Running a fallback for condition ID %d. Make sure you ran LinkCondition()."), ID);
	return 0;
}

long Extension::UnlinkedExpression(int ID)
{
	DarkEdif::MsgBox::Error(_T("Extension::UnlinkedExpression() called"), _T("Running a fallback for expression ID %d. Make sure you ran LinkExpression()."), ID);
	// Unlinked A/C/E is fatal error , but try not to return null string and definitely crash it
	if ((size_t)ID < ::SDK->ExpressionInfos.size() && ::SDK->ExpressionInfos[ID]->Flags.ef == ExpReturnType::String)
		return (long)Runtime.CopyString(_T(""));
	return 0;
}