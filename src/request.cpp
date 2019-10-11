#include "request.h"

namespace tinyweb {
    Request::Request () {}
    Request::Request (Header* header_): header(header_) {}
    Request::Request (Header* header_, std::string body_): header(header_), body(body_) {}

    std::string Request::get_body() {
        return body;
    }

    Header* Request::get_header() {
        return header;
    } 

    std::string Request::str () {
        return header->str() + body;
    }
}