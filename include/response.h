#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

#include "header.h" 

namespace tinyweb {
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