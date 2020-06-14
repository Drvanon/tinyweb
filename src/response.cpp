#include "response.h"
#include "iostream"

namespace tinyweb {
    Response::Response(ResponseHeader* header_, std::string body_): header(header_), body(body_) {}

    void Response::set_body(std::string body_) {
        body = body_;
    }

    std::string Response::str () {
        if (!header->has_field("Content-Length")){
            header->set_field("Content-Length", std::to_string(body.size()));
        }
        if (header->get_response_code() == 0) {
            header->set_response_code(200, "");
        }
        return header->str() + body;
    }
}