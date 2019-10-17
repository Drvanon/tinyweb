#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <functional>

#include "request.h"
#include "response.h"

namespace tinyweb {
    class Route {
        private:
            std::string route_name;
            std::function<Response(Request)> action;
        public:
            Route(std::string route_name, std::function<Response(Request)> action);
            std::string get_name();
            virtual Response* run(Request) = 0;
            bool match(std::string url);
    };
}

#endif // ROUTE_H