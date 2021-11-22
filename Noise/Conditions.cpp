#include "Common.h"


bool Extension::request_ready(const TCHAR* name) {
    noise_request* r = requests[name];
    return r->ready;
}