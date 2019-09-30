#include <string>
#include <functional>

#include "request.h"
#include "response.h"

namespace tinyweb {
    class Route {
        private:
            std::string route_name;
            std::function<tinyweb::Response(tinyweb::Request)> action;
        
        public:
            Route(std::string route_name, std::function<tinyweb::Response(tinyweb::Request)> action);
            std::string get_name();
            tinyweb::Response run(tinyweb::Request);
    };
}