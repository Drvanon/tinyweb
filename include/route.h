#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include <functional>

#include "request.h"
#include "response.h"

namespace tinyweb {
    /**
     * @brief Route on the HTTP server
     * 
     * A route represents a requestable WSGI route that can be requested from 
     * the server through a URI. Each route corresponds to an action: a function 
     * that generates a response (tinyweb::Response) for each request (tinyweb::Request).
     * 
     * All routes need to be registered in the server (tinyweb::Server) to be 
     * able to function. 
     */
    class Route {
        private:
            std::string route_name;
            std::function<Response* (Request* )> action;
        public:
            Route(std::string route_name, std::function<Response* (Request* )> action);
            std::string get_name();
            Response* run(Request*);
            bool match(std::string url);
    };
}

#endif // ROUTE_H