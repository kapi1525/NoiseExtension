#include "Common.h"
#include "DarkEdif.h"



inline float AsFloat(const json_value& json) {
	if(json.type == json_double) {
		return (float)double(json);
	} else {
		DarkEdif::MsgBox::Error(_T("Incorect type"), _T("Expected type %d but got %d."), json_double, json.type);
		return 0.f;
	}
}

inline int AsInt(const json_value& json) {
	if(json.type == json_integer) {
		return (int)long long(json);
	} else {
		DarkEdif::MsgBox::Error(_T("Incorect type"), _T("Expected type %d but got %d."), json_integer, json.type);
		return 0;
	}
}

inline unsigned int AsUInt(const json_value& json) {
	if(json.type == json_integer) {
		return (unsigned int)long long(json);
	} else {
		DarkEdif::MsgBox::Error(_T("Incorect type"), _T("Expected type %d but got %d."), json_integer, json.type);
		return 0u;
	}
}



inline void ResetProps(EDITDATA* edPtr) {
	// Set default object settings from DefaultState.
	const json_value& Props = CurLang["Properties"];

	edPtr->editdata_rev = 1;

	// Read defaults from json file.
	edPtr->noise_seed = AsInt(Props[0]["DefaultState"]);

	edPtr->noise_type = AsUInt(Props[1]["DefaultState"]);
	edPtr->noise_frequency = AsFloat(Props[2]["DefaultState"]);

	edPtr->fractal_type = AsUInt(Props[4]["DefaultState"]);
	edPtr->fractal_octaves = AsInt(Props[5]["DefaultState"]);
	edPtr->fractal_lacunarity = AsFloat(Props[6]["DefaultState"]);
	edPtr->fractal_gain = AsFloat(Props[7]["DefaultState"]);
	edPtr->fractal_weighted_strength = AsFloat(Props[8]["DefaultState"]);
	edPtr->fractal_pingpong_strength = AsFloat(Props[9]["DefaultState"]);

	edPtr->cellular_distance_func = AsUInt(Props[11]["DefaultState"]);
	edPtr->cellular_ret_type = AsUInt(Props[12]["DefaultState"]);
	edPtr->cellular_jitter = AsFloat(Props[13]["DefaultState"]);

	edPtr->eHeader.extVersion = Extension::Version;
}



inline EDITDATA* NewEDITDATA() {
	return (EDITDATA*)GlobalAlloc(GPTR,sizeof(EDITDATA));
}

inline void HeaderCopy(EDITDATA* target, void* source) {
	memcpy(&target->eHeader, &((EDITDATA*)source)->eHeader, sizeof(extHeader));
	target->eHeader.extSize = sizeof(EDITDATA);
}

inline void DebugVersionUpdateLog(const TCHAR* string) {
	#ifdef _DEBUG
	DarkEdif::MsgBox::Info(_T("Update"), string);
	#endif
}



// Update EDITDATA from versions v0.9.3 - v0.9.1
inline EDITDATA* UpdateEDITDATA_prerev(EDITDATA_prerev* edPtr) {
	DebugVersionUpdateLog(_T("EDITDATA was updated from v0.9.3 - v0.9.1 EDITDATA layout."));

	EDITDATA* new_edPtr = NewEDITDATA();
	HeaderCopy(new_edPtr, edPtr);
	ResetProps(new_edPtr);

	// Move over everything we can
	new_edPtr->noise_seed = edPtr->noise_seed;
	new_edPtr->noise_type = edPtr->noise_type;
	new_edPtr->noise_frequency = edPtr->noise_frequency;
	new_edPtr->fractal_type = edPtr->fractal_type;
	new_edPtr->fractal_octaves = edPtr->fractal_octaves;
	new_edPtr->fractal_lacunarity = edPtr->fractal_lacunarity;
	new_edPtr->fractal_weighted_strength = edPtr->fractal_weighted_strength;
	new_edPtr->fractal_pingpong_strength = edPtr->fractal_pingpong_strength;
	new_edPtr->cellular_distance_func = edPtr->cellular_distance_func;
	new_edPtr->cellular_ret_type = edPtr->cellular_ret_type;
	new_edPtr->cellular_jitter = edPtr->cellular_jitter;

	// There was an aditional fractal type in properties by mistake
	if(new_edPtr->fractal_type == 4) {
		new_edPtr->fractal_type = 3;
	}

	return new_edPtr;
}



// Update EDITDATA from versions v0.9.0 and older.
inline EDITDATA* UpdateEDITDATA_old(EDITDATA_bare* edPtr) {
	DebugVersionUpdateLog(_T("EDITDATA was updated from v0.9.0 and older EDITDATA layout."));

	EDITDATA* new_edPtr = NewEDITDATA();
	HeaderCopy(new_edPtr, edPtr);
	ResetProps(new_edPtr);

	return new_edPtr;
}



EDITDATA* FusionAPI UpdateEditStructure(mv* mV, EDITDATA_bare* oldEdPtr) {
#pragma DllExportHint
	if(oldEdPtr->eHeader.extVersion < 13) {
		return UpdateEDITDATA_old(oldEdPtr);
	}

	if(oldEdPtr->eHeader.extVersion < 16) {
		return UpdateEDITDATA_prerev((EDITDATA_prerev*)oldEdPtr);
	}

	// No update
	return nullptr;
}



// ============================================================================
// ROUTINES USED UNDER FRAME EDITOR
// ============================================================================

#if EditorBuild


// Called once object is created or modified, just after setup.
// Also called before showing the "Insert an object" dialog if your object
// has no icon resource
int FusionAPI MakeIconEx(mv * mV, cSurface * pIconSf, TCHAR * lpName, ObjInfo * oiPtr, EDITDATA * edPtr) {
#pragma DllExportHint
	pIconSf->Delete();
	pIconSf->Clone(*SDK->Icon);

	pIconSf->SetTransparentColor(RGB(255, 0, 255));
	return 0;
}


// Called when you choose "Create new object". It should display the setup box
// and initialize everything in the datazone.
int FusionAPI CreateObject(mv * mV, LevelObject * loPtr, EDITDATA * edPtr) {
#pragma DllExportHint
	if (!IS_COMPATIBLE(mV))
		return -1;

	Edif::Init(mV, edPtr);
	
	if (edPtr->eHeader.extSize < sizeof(EDITDATA)) {
		void* newEd = mvReAllocEditData(mV, edPtr, sizeof(EDITDATA));
		if (!newEd)
			return DarkEdif::MsgBox::Error(_T("Invalid properties"), _T("Failed to allocate enough size for properties."), sizeof(EDITDATA)), -1;
		edPtr = (EDITDATA *) newEd;
	}

	ResetProps(edPtr);
	return 0;
}


// Displays the object under the frame editor
void FusionAPI EditorDisplay(mv *mV, ObjectInfo * oiPtr, LevelObject * loPtr, EDITDATA * edPtr, RECT * rc) {
#pragma DllExportHint
	cSurface * Surface = WinGetSurface((int) mV->IdEditWin);
	if (!Surface)
		return;

	// If you don't have this function run in Edittime.cpp, SDK Updater will be disabled for your ext
	// Don't comment or preprocessor-it out if you're removing it; delete the line entirely.
	DarkEdif::SDKUpdater::RunUpdateNotifs(mV, edPtr);

	::SDK->Icon->Blit(*Surface, rc->left, rc->top, BMODE_TRANSP, BOP_COPY, 0);
}



// ============================================================================
// PROPERTIES
// ============================================================================

enum class noise_propid {
	noise_seed = PROPID_EXTITEM_CUSTOM_FIRST,

	noise_type,
	noise_frequency,

	fractal_type = noise_frequency + 2,
	fractal_octaves,
	fractal_lacunarity,
	fractal_gain,
	fractal_weighted_strength,
	fractal_pingpong_strength,

	cellular_distance_func = fractal_pingpong_strength + 2,
	cellular_ret_type,
	cellular_jitter,

	version = cellular_jitter + 2
};


// Inserts properties into the properties of the object.
BOOL FusionAPI GetProperties(mv * mV, EDITDATA * edPtr, BOOL bMasterItem) {
#pragma DllExportHint
	mvInsertProps(mV, edPtr, SDK->EdittimeProperties.get(), PROPID_TAB_GENERAL, TRUE);
	return TRUE;
}


// Called when the properties are removed from the property window.
void FusionAPI ReleaseProperties(mv * mV, EDITDATA * edPtr, BOOL bMasterItem) {
#pragma DllExportHint
}


// Returns the value of properties that have a value.
// Note: see GetPropCheck for checkbox properties
Prop* FusionAPI GetPropValue(mv * mV, EDITDATA * edPtr, unsigned int PropID) {
#pragma DllExportHint	
	Prop* prop_ptr = nullptr;

	switch(noise_propid(PropID))
	{
		case noise_propid::noise_seed:
			prop_ptr = new Prop_Str(std::to_tstring(edPtr->noise_seed).c_str());
			break;
			
		case noise_propid::noise_type:
			prop_ptr = new Prop_UInt(edPtr->noise_type);
			break;

		case noise_propid::noise_frequency:
			prop_ptr = new Prop_Float(edPtr->noise_frequency);
			break;
			

		case noise_propid::fractal_type:
			prop_ptr = new Prop_UInt(edPtr->fractal_type);
			break;
			
		case noise_propid::fractal_octaves:
			prop_ptr = new Prop_SInt(edPtr->fractal_octaves);
			break;
			
		case noise_propid::fractal_lacunarity:
			prop_ptr = new Prop_Float(edPtr->fractal_lacunarity);
			break;

		case noise_propid::fractal_gain:
			prop_ptr = new Prop_Float(edPtr->fractal_gain);
			break;
			
		case noise_propid::fractal_weighted_strength:
			prop_ptr = new Prop_Float(edPtr->fractal_weighted_strength);
			break;
			
		case noise_propid::fractal_pingpong_strength:
			prop_ptr = new Prop_Float(edPtr->fractal_pingpong_strength);
			break;
			

		case noise_propid::cellular_distance_func:
			prop_ptr = new Prop_UInt(edPtr->cellular_distance_func);
			break;
			
		case noise_propid::cellular_ret_type:
			prop_ptr = new Prop_UInt(edPtr->cellular_ret_type);
			break;
			
		case noise_propid::cellular_jitter:
			prop_ptr = new Prop_Float(edPtr->cellular_jitter);
			break;

			
		case noise_propid::version:
			// TODO: Read version from json file.
			prop_ptr = new Prop_Str(DarkEdif::UTF8ToTString(std::string(CurLang["Properties"][15]["DefaultState"])).c_str());
			break;
	}

	return prop_ptr;
}


// Returns the checked state of properties that have a check box.
BOOL FusionAPI GetPropCheck(mv * mV, EDITDATA * edPtr, unsigned int PropID_) {
#pragma DllExportHint
	return FALSE;   // No checkboxes here
}


// Called by Fusion after a property has been modified.
void FusionAPI SetPropValue(mv * mV, EDITDATA * edPtr, unsigned int PropID, void * Param) {
#pragma DllExportHint

	switch(noise_propid(PropID))
	{
		case noise_propid::noise_seed:
			{
				std::string Text = DarkEdif::TStringToANSI(std::tstring(((Prop_Str*)Param)->String));

				unsigned int Seed = 0;

				for (size_t i = 0; i < Text.length(); i++) {
					if (Text.at(i) >= '0' && Text.at(i) <= '9') {
						Seed = Seed * 10;
						Seed = Seed + (Text.at(i) - 48);
					}
					else {
						Seed = Seed * 100;
						srand((int)Text.at(i) + i);
						Seed = Seed + rand() % 99;
					}
				}

				edPtr->noise_seed = Seed;
			}
			break;

		case noise_propid::noise_type:
			edPtr->noise_type = ((Prop_UInt*)Param)->Value;
			break;

		case noise_propid::noise_frequency:
			edPtr->noise_frequency = ((Prop_Float*)Param)->Value;
			break;
			

		case noise_propid::fractal_type:
			edPtr->fractal_type = ((Prop_UInt*)Param)->Value;
			break;
			
		case noise_propid::fractal_octaves:
			edPtr->fractal_octaves = ((Prop_SInt*)Param)->Value;
			break;
			
		case noise_propid::fractal_lacunarity:
			edPtr->fractal_lacunarity = ((Prop_Float*)Param)->Value;
			break;
			
		case noise_propid::fractal_gain:
			edPtr->fractal_gain = ((Prop_Float*)Param)->Value;
			break;
			
		case noise_propid::fractal_weighted_strength:
			edPtr->fractal_weighted_strength = ((Prop_Float*)Param)->Value;
			break;
			
		case noise_propid::fractal_pingpong_strength:
			edPtr->fractal_pingpong_strength = ((Prop_Float*)Param)->Value;
			break;
			

		case noise_propid::cellular_distance_func:
			edPtr->cellular_distance_func = ((Prop_UInt*)Param)->Value;
			break;
			
		case noise_propid::cellular_ret_type:
			edPtr->cellular_ret_type = ((Prop_UInt*)Param)->Value;
			break;
			
		case noise_propid::cellular_jitter:
			edPtr->cellular_jitter = ((Prop_Float*)Param)->Value;
			break;
		

		default:
			LOGE(_T("SetPropValue tried to set property that dosent exist!"));
			break;
	}
}


// Called by Fusion when the user modifies a checkbox in the properties.
void FusionAPI SetPropCheck(mv * mV, EDITDATA * edPtr, unsigned int PropID, BOOL checked) {
#pragma DllExportHint
}


// Called by Fusion when the user clicks the button of a Button or EditButton property.
/*BOOL FusionAPI EditProp(mv * mV, EDITDATA * edPtr, unsigned int PropID) {
#pragma DllExportHint
	// Example
	// -------
/*
	if (nPropID==PROPID_EDITCONTENT)
	{
		if ( EditObject(mV, NULL, NULL, edPtr) )
			return TRUE;
	}
*\/

	return FALSE;
}*/


// Called by Fusion to request the enabled state of a property.
/*BOOL FusionAPI IsPropEnabled(mv * mV, EDITDATA * edPtr, unsigned int PropID) {
#pragma DllExportHint
	// Example
	// -------
/*
	switch (nPropID) {

	case PROPID_CHECK:
		return (edPtr->nComboIndex != 0);
	}
*\/
	return TRUE;
}*/


// Called when a property is initialized and its creation parameter is NULL (in the PropData).
// Allows you, for example, to change the content of a combobox property according to specific settings in the EDITDATA structure.
/*LPARAM FusionAPI GetPropCreateParam(mv *mV, EDITDATA *edPtr, unsigned int PropID) {
#pragma DllExportHint
	// Example
	// -------
	//	if ( PropID == PROPID_COMBO )
	//	{
	//		switch (edPtr->sType)
	//		{
	//		case TYPE1:
	//			return (LPARAM)ComboList1;
	//		case TYPE2:
	//			return (LPARAM)ComboList2;
	//		}
	//	}

	return NULL;
}*/


// Called after a property has been initialized.
// Allows you, for example, to free memory allocated in GetPropCreateParam.
/*void FusionAPI ReleasePropCreateParam(mv *mV, EDITDATA *edPtr, unsigned int PropID, LPARAM lParam) {
#pragma DllExportHint
}*/




// ============================================================================
// ROUTINES USED WHEN BUILDING
// ============================================================================

// This routine is called by Fusion when an Android build is prepared before building.
// It enables you to modify the Android manifest file to add your own content, or otherwise check the Android build.
// It is called in the Extensions[\Unicode] MFX, for any extension in the MFA that defines PrepareAndroidBuild,
// including exts that have no corresponding Data\Runtime\Android file and would create a not-compatible build warning.
/*void FusionAPI PrepareAndroidBuild(mv* mV, EDITDATA* edPtr, LPCTSTR androidDirectoryPathname) {
#pragma DllExportHint
	// Erase the manifest file so the build will fail
	std::tstring manifestPath = androidDirectoryPathname;
	manifestPath += _T("app\\src\\main\\AndroidManifest.xml"sv);
	// Open manifestPath as a file, say with
	// _tfopen(manifestPath.c_str(), _T("ab"))
	// and you're free to edit the manifest
}*/
#endif // EditorBuild
