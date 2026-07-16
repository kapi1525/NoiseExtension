#pragma once

// Do not move XXXEXT after #include of DarkEdif.h!
#define MMFEXT		// Fusion 2.x, Fusion 2.x Dev

#include "DarkEdif.hpp"

#ifdef _DEBUG
#define JSON_COMMENT_MACRO "(Debug) "
#else
#define JSON_COMMENT_MACRO ""
#endif

#pragma pack (push, 1)
// Binary block used in Fusion editor and saved in the MFA/CCN/EXE files
struct EDITDATA final
{
	NO_DEFAULT_CTORS_OR_DTORS(EDITDATA);
	// Header - required, must be first variable in EDITDATA
	extHeader eHeader;

    #if EditorBuild
    static DarkEdif::Properties::PropertyReader* UserConverter();
    #endif

	// Keep Properties variable last; its size varies.
	DarkEdif::Properties Props;
};
#pragma pack (pop)

// Edittime.cpp
__declspec(dllexport) int FusionAPI MakeIconEx(mv * mV, cSurface * pIconSf, TCHAR * lpName, ObjInfo * oiPtr, EDITDATA * edPtr) asm ("MakeIconEx");
__declspec(dllexport) int FusionAPI CreateObject(mv * mV, LevelObject * loPtr, EDITDATA * edPtr) asm ("CreateObject");
__declspec(dllexport) void FusionAPI EditorDisplay(mv * mV, ObjectInfo * oiPtr, LevelObject * loPtr, EDITDATA * edPtr, DarkEdif::Rect * rc) asm ("EditorDisplay");
__declspec(dllexport) BOOL FusionAPI IsTransparent(mv* mV, LevelObject* loPtr, EDITDATA* edPtr, int dx, int dy) asm ("IsTransparent");
__declspec(dllexport) BOOL FusionAPI SetEditSize(mv* mV, EDITDATA* edPtr, int cx, int cy) asm ("SetEditSize");
__declspec(dllexport) void FusionAPI GetObjectRect(mv * mV, DarkEdif::Rect * rc, LevelObject * loPtr, EDITDATA * edPtr) asm ("GetObjectRect");
__declspec(dllexport) BOOL FusionAPI EditObject(mv *mV, ObjInfo * oiPtr, LevelObject * loPtr, EDITDATA * edPtr) asm ("EditObject");
__declspec(dllexport) BOOL FusionAPI GetProperties(mv * mV, EDITDATA * edPtr, BOOL bMasterItem) asm ("GetProperties");
__declspec(dllexport) void FusionAPI ReleaseProperties(mv * mV, EDITDATA * edPtr, BOOL bMasterItem) asm ("ReleaseProperties");
__declspec(dllexport) void * FusionAPI GetPropValue(mv * mV, EDITDATA * edPtr, unsigned int PropID) asm ("GetPropValue");
__declspec(dllexport) BOOL FusionAPI GetPropCheck(mv * mV, EDITDATA * edPtr, unsigned int PropID) asm ("GetPropCheck");
__declspec(dllexport) void FusionAPI SetPropValue(mv * mV, EDITDATA * edPtr, unsigned int PropID, void * Param) asm ("SetPropValue");
__declspec(dllexport) void FusionAPI SetPropCheck(mv * mV, EDITDATA * edPtr, unsigned int PropID, BOOL checked) asm ("SetPropCheck");
__declspec(dllexport) BOOL FusionAPI EditProp(mv * mV, EDITDATA * edPtr, unsigned int PropID) asm ("EditProp");
__declspec(dllexport) BOOL FusionAPI IsPropEnabled(mv * mV, EDITDATA * edPtr, unsigned int PropID) asm ("IsPropEnabled");
__declspec(dllexport) LPARAM FusionAPI GetPropCreateParam(mv *mV, EDITDATA *edPtr, unsigned int PropID) asm ("GetPropCreateParam");
__declspec(dllexport) void FusionAPI ReleasePropCreateParam(mv *mV, EDITDATA *edPtr, unsigned int PropID, LPARAM lParam) asm ("ReleasePropCreateParam");

// DarkEdif.cpp
__declspec(dllexport) void FusionAPI DuplicateObject(mv* mV, ObjInfo* oiPtr, EDITDATA* edPtr) asm ("DuplicateObject");
__declspec(dllexport) int FusionAPI EnumElts(mv* mV, EDITDATA* edPtr, ENUMELTPROC enumProc, ENUMELTPROC undoProc, LPARAM p1, LPARAM p2) asm ("EnumElts");
__declspec(dllexport) HGLOBAL FusionAPI UpdateEditStructure(mv * mV, void * OldEdPtr) asm ("UpdateEditStructure");
__declspec(dllexport) std::uint16_t * FusionAPI GetDebugTree(RUNDATA *rdPtr) asm ("GetDebugTree");
__declspec(dllexport) void FusionAPI GetDebugItem(TCHAR *pBuffer, RUNDATA *rdPtr, int id) asm ("GetDebugItem");
__declspec(dllexport) void FusionAPI EditDebugItem(RUNDATA *rdPtr, int id) asm ("EditDebugItem");

// Edif.cpp
__declspec(dllexport) void DarkEdif_Invalid_Parameter(const wchar_t* /*expression - NULL*/, const wchar_t* /*function - NULL */,
	const wchar_t* /* file - NULL */, unsigned int /* line = 0 */, uintptr_t /* pReserved - irrelevant */) asm ("DarkEdif_Invalid_Parameter");

// Edif.General.cpp
__declspec(dllexport) int FusionAPI Initialize(mv *mV, int quiet) asm ("Initialize");
__declspec(dllexport) int FusionAPI Free(mv *mV) asm ("Free");
__declspec(dllexport) void FusionAPI UnloadObject(mv * mV, EDITDATA * edPtr, int reserved) asm ("UnloadObject");
__declspec(dllexport) const TCHAR ** FusionAPI GetDependencies() asm ("GetDependencies");
__declspec(dllexport) std::int16_t FusionAPI GetRunObjectInfos(mv* mV, kpxRunInfos* infoPtr) asm ("GetRunObjectInfos");
__declspec(dllexport) std::uint32_t FusionAPI GetInfos(int info) asm ("GetInfos");
__declspec(dllexport) std::int16_t FusionAPI CreateRunObject(RUNDATA * rdPtr, EDITDATA * edPtr, CreateObjectInfo * cobPtr) asm ("CreateRunObject");
__declspec(dllexport) std::int16_t FusionAPI DestroyRunObject(RUNDATA * rdPtr, long fast) asm ("DestroyRunObject");
__declspec(dllexport) REFLAG FusionAPI HandleRunObject(RUNDATA * rdPtr) asm ("HandleRunObject");
__declspec(dllexport) std::uint16_t FusionAPI GetRunObjectDataSize(RunHeader * rhPtr, EDITDATA * edPtr) asm ("GetRunObjectDataSize");
__declspec(dllexport) std::int16_t FusionAPI PauseRunObject(RUNDATA * rdPtr) asm ("PauseRunObject");
__declspec(dllexport) std::int16_t FusionAPI ContinueRunObject(RUNDATA * rdPtr) asm ("ContinueRunObject");
__declspec(dllexport) short FusionAPI DisplayRunObject(RUNDATA* rdPtr) asm ("DisplayRunObject");
__declspec(dllexport) cSurface* FusionAPI GetRunObjectSurface(RUNDATA * rdPtr) asm ("GetRunObjectSurface");
__declspec(dllexport) sMask* FusionAPI GetRunObjectCollisionMask(RUNDATA * rdPtr, LPARAM flags) asm ("GetRunObjectCollisionMask");
__declspec(dllexport) void FusionAPI GetZoneInfos(RUNDATA * rdPtr) asm ("GetZoneInfos");
__declspec(dllexport) short FusionAPI DisplayRunObject(RUNDATA* rdPtr) asm ("DisplayRunObject");

// Edif.Runtime.cpp
__declspec(dllexport) void FusionAPI GetRunObjectFont(RUNDATA* rdPtr, LOGFONT* pLf) asm ("GetRunObjectFont");
__declspec(dllexport) COLORREF FusionAPI GetRunObjectTextColor(RUNDATA* rdPtr) asm ("GetRunObjectTextColor");
__declspec(dllexport) void FusionAPI SetRunObjectFont(RUNDATA* rdPtr, LOGFONT* pLf, RECT* pRc) asm ("SetRunObjectFont");
__declspec(dllexport) void FusionAPI SetRunObjectTextColor(RUNDATA* rdPtr, COLORREF rgb) asm ("SetRunObjectTextColor");

// Edif.Edittime.cpp
__declspec(dllexport) void FusionAPI GetObjInfos(mv * mV, EDITDATA * edPtr, TCHAR * ObjName, TCHAR * ObjAuthor,
    TCHAR * ObjCopyright, TCHAR * ObjComment, TCHAR * ObjHttp) asm ("GetObjInfos");
__declspec(dllexport) const TCHAR * FusionAPI GetHelpFileName() asm ("GetHelpFileName");
__declspec(dllexport) void FusionAPI GetConditionTitle(mv *mV, short code, short param, TCHAR * strBuf, short maxLen) asm ("GetConditionTitle");
__declspec(dllexport) void FusionAPI GetActionTitle(mv *mV, short code, short param, TCHAR * strBuf, short maxLen) asm ("GetActionTitle");
__declspec(dllexport) void FusionAPI GetExpressionParam(mv *mV, short code, short param, TCHAR * strBuf, short maxLen) asm ("GetExpressionParam");
__declspec(dllexport) void FusionAPI GetExpressionTitle(mv *mV, short code, TCHAR * strBuf, short maxLen) asm ("GetExpressionTitle");
__declspec(dllexport) void FusionAPI GetConditionString(mv *mV, short code, TCHAR * strPtr, short maxLen) asm ("GetConditionString");
__declspec(dllexport) void FusionAPI GetActionString(mv *mV, short code, TCHAR * strPtr, short maxLen) asm ("GetActionString");
__declspec(dllexport) void FusionAPI GetExpressionString(mv * mV, short code, TCHAR * strPtr, short maxLen) asm ("GetExpressionString");
__declspec(dllexport) std::int16_t FusionAPI GetConditionCodeFromMenu(mv* mV, short menuId) asm ("GetConditionCodeFromMenu");
__declspec(dllexport) std::int16_t FusionAPI GetActionCodeFromMenu(mv* mV, short menuId) asm ("GetActionCodeFromMenu");
__declspec(dllexport) std::int16_t FusionAPI GetExpressionCodeFromMenu(mv* mV, short menuId) asm ("GetExpressionCodeFromMenu");
__declspec(dllexport) HMENU FusionAPI GetConditionMenu(mv* mV, ObjectInfo* oiPtr, EDITDATA* edPtr) asm ("GetConditionMenu");
__declspec(dllexport) HMENU FusionAPI GetActionMenu(mv* mV, ObjectInfo* oiPtr, EDITDATA* edPtr) asm ("GetActionMenu");
__declspec(dllexport) HMENU FusionAPI GetExpressionMenu(mv* mV, ObjectInfo* oiPtr, EDITDATA* edPtr) asm ("GetExpressionMenu");
__declspec(dllexport) void * FusionAPI GetConditionInfos(mv *mV, short code) asm ("GetConditionInfos");
__declspec(dllexport) void * FusionAPI GetActionInfos(mv * mV, short code) asm ("GetActionInfos");
__declspec(dllexport) void * FusionAPI GetExpressionInfos(mv * mV, short code) asm ("GetExpressionInfos");
__declspec(dllexport) unsigned int FusionAPI GetTextCaps(mv* mV, EDITDATA* edPtr) asm ("GetTextCaps");
// BOOL FusionAPI GetTextFont(mv* mV, EDITDATA* edPtr, LOGFONT* Font, asm ("GetTextFont");
// BOOL FusionAPI SetTextFont(mv* mV, EDITDATA* edPtr, LOGFONT* Font, asm ("SetTextFont");
__declspec(dllexport) COLORREF FusionAPI GetTextClr(mv* mV, EDITDATA* edPtr) asm ("GetTextClr");
__declspec(dllexport) void FusionAPI SetTextClr(mv* mV, EDITDATA* edPtr, COLORREF color) asm ("SetTextClr");
__declspec(dllexport) unsigned int FusionAPI GetTextAlignment(mv* mV, EDITDATA* edPtr) asm ("GetTextAlignment");
__declspec(dllexport) void FusionAPI SetTextAlignment(mv* mV, EDITDATA* edPtr, unsigned int alignFlags) asm ("SetTextAlignment");
__declspec(dllexport) void FusionAPI PrepareFlexBuild(mv * pMV, EDITDATA * edPtr, const wchar_t * wTempFolder) asm ("PrepareFlexBuild");

#include "Extension.hpp"
