#if !defined(REQUEST_H)
#define REQUEST_H

#include "header.h"

namespace tinyweb {
    class Request {
        private:
            RequestHeader* header;
            std::string body;
        public:
            Request();
            Request(RequestHeader* header_);
            Request(RequestHeader* header, std::string body);
            RequestHeader* get_header();
            std::string get_uri(); 
            std::string get_body();
            void set_body(std::string body);
            std::string str();
    }; // class Request
} // namespace tinyweb

#endif // REQUEST_H
