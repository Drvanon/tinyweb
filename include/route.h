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
            /**
             * @brief Construct a new Route object
             * 
             * A route represents an action that should be executed should a 
             * specific URL be called. 
             * 
             * @param route_name String that can be regexed to.
             * @param action Function that will be executed when the URL matches.
             */
            Route(std::string route_name, std::function<Response* (Request* )> action);
            /**
             * @brief Get the name of this route.
             * 
             * @return std::string 
             */
            std::string get_name();
            /**
             * @brief Run the action corresponding to this route.
             * 
             * @return Response* 
             */
            Response* run(Request*);
            /**
             * @brief Match the url to the route name. 
             * 
             * @param url 
             * @return true If the url and name match.
             * @return false If the url does not match the name.
             */
            bool match(std::string url);
    };
}

#endif // ROUTE_H