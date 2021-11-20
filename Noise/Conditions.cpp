#include "Common.h"


bool Extension::IsRequestReady(const TCHAR* name) {
    NoiseRequest* r;
    r = Requests[name];

    return r->Ready;
}