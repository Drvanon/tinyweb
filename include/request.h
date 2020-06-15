#if !defined(REQUEST_H)
#define REQUEST_H

#include "header.h"

namespace tinyweb {
    class Request {
        private:
            RequestHeader* header;
            std::string body;
        public:
            /**
             * @brief Construct a new Request object
             * 
             * Requests are provided to actions when a route (tinyweb::Route) 
             * is being called. 
             * 
             */
            Request();
            Request(RequestHeader* header_);
            Request(RequestHeader* header, std::string body);
            /**
             * @brief Get the header of this request.
             * 
             * @return RequestHeader* 
             */
            RequestHeader* get_header();
            /**
             * @brief Get the uri of request
             * 
             * @return std::string 
             */
            std::string get_uri(); 
            /**
             * @brief Get the body of the request
             * 
             * @return std::string 
             */
            std::string get_body();
            /**
             * @brief Set the body of the request
             * 
             * This is only used when modifying the body 
             * based on the content of the headers.
             * @param body 
             */
            void set_body(std::string body);
            std::string str();
    }; // class Request
} // namespace tinyweb

#endif // REQUEST_H
