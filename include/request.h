#if !defined(REQUEST_H)
#define REQUEST_H

#include "header.h"

namespace tinyweb {
    class Request {
        private:
            Header* header;
            std::string body;
        public:
            Request();
            Request (Header* header_);
            Request(Header* header, std::string body);
            Header* get_header(); 
            std::string get_body(); 
            std::string str();
    }; // class Request
} // namespace tinyweb

#endif // REQUEST_H
