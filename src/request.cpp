#include "request.h"

namespace tinyweb {
    Request::Request () {}
    Request::Request (RequestHeader* header_): header(header_) {}
    Request::Request (RequestHeader* header_, std::string body_): header(header_), body(body_) {}

    std::string Request::get_body() {
        return body;
    }

    RequestHeader* Request::get_header() {
        return header;
    } 

    std::string Request::str () {
        return header->str() + body;
    }

    std::string Request::get_uri () {
        return header->get_uri();
    }

    void Request::set_body(std::string body_) {
        body = body_;
    }
}