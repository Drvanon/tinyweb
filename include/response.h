#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

#include "header.h" 

namespace tinyweb {
    class Response {
        int code;
        std::string body;
        tinyweb::Header* headers;

        void set_mimetype(std::string type);
        std::string str();
    };
}

#endif