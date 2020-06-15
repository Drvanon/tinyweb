#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

#include "header.h" 

namespace tinyweb {
    /**
     * @brief Response from the server (to a request).
     * 
     * When a route (tinyweb::Route) is requested (tinyweb::Request) on 
     * the server (tinyweb::Server), a response should be created. This
     * is a one to one representation of an HTTP response.  
     */
    class Response {
        private:
            std::string body;
            ResponseHeader* header;
        public:
            Response();
            Response(ResponseHeader* header_, std::string body_);
            void set_mimetype(std::string type);
            void set_body(std::string body_);
            std::string str();
    };
}

#endif