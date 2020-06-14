#include "response.h"

namespace tinyweb {
    Response::Response(ResponseHeader* header_, std::string body_): header(header_), body(body_) {}

    void Response::set_body(std::string body_) {
        body = body_;
    }

    std::string Response::str () {
        return header->str() + body;
    }
}