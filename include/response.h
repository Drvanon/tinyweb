#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

#include "header.h" 

namespace tinyweb {
    class Response {
        private:
            int code;
            std::string body;
            ResponseHeader* headers;
        public:
            void set_mimetype(std::string type);
            std::string str();
    };
}

#endif