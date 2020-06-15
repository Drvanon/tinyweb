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
            /**
             * @brief Construct a new Response object
             * 
             * @param header_ 
             * @param body_ 
             */
            Response(ResponseHeader* header_, std::string body_);
            void set_mimetype(std::string type);
            /**
             * @brief Set the body of the response.
             * 
             * @param body_ 
             */
            void set_body(std::string body_);
            /**
             * @brief Get the string representation of this request.
             * 
             * Note that the "Content-Length" header field will be set automatically
             * if it is not set already. Similarly, if the status code is not set 
             * manually it will be set to "200 OK". These changes are persistent.
             * 
             * @return std::string 
             */
            std::string str();
    };
}

#endif