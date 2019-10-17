#include "route.h"

namespace tinyweb
{
    bool Route::match(std::string uri) {
        // Simplification of matching algorithm, to be implemented with regexes.
        return uri == route_name;
    }
} // namespace tinyweb
