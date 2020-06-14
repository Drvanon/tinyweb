#include "route.h"

namespace tinyweb
{
    Route::Route(std::string route_name_, std::function<Response* (Request* )> action_):
        action(action_), route_name(route_name_) {}

    bool Route::match(std::string uri) {
        // Simplification of matching algorithm, to be implemented with regexes.
        return uri == route_name;
    }

    Response* Route::run(tinyweb::Request* request) {
        return action(request);
    }
} // namespace tinyweb
