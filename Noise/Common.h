#pragma once

#define MMFEXT

#ifdef RUN_ONLY
	#define CurLang (*::SDK->json.u.object.values[::SDK->json.u.object.length - 1].value)
#else
	const extern struct _json_value & CurrentLanguage();
	#define CurLang CurrentLanguage()
#endif

#include <map>

#include "Edif.h"
#include "json.h"
#include "Resource.h"
#include "DarkEdif.h"

#include "FastNoiseLite.h"
#include "noise-requests.h"


// edPtr : Used at edittime and saved in the MFA/CCN/EXE files
struct EDITDATA {
	// Header - required
	extHeader		eHeader;

	// Keep DarkEdif variables as last. Undefined behaviour otherwise.
	int				DarkEdif_Prop_Size;
	char			DarkEdif_Props[];

	// =====
	// DarkEdif functions, use within Extension ctor.
	// =====
	bool IsPropChecked(int propID);						// Returns property checked or unchecked.
	std::tstring GetPropertyStr(const char * propName);	// Returns std::tstring property setting from property name.
	std::tstring GetPropertyStr(int propID);			// Returns std::tstring property string from property ID.
};

class Extension;

struct RUNDATA {
	// Main header - required
	HeaderObject rHo;

	// Required
	Extension * pExtension;
};

#include "Extension.h"
