#include "Common.h"


bool Extension::IsRequestReady(const TCHAR* name) {
    return Requests[name]->Ready;
}