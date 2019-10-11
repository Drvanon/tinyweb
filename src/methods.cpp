#include "methods.h"

namespace tinyweb
{
    METHODS string_to_method (std::string str) {
        METHODS method;
        if (str == "GET") {
            method = METHODS::GET;
        } else if (str == "HEAD") {
            method = METHODS::HEAD;
        } else if (str == "POST") {
            method = METHODS::POST;
        } else if (str == "PUT") {
            method = METHODS::PUT;
        } else if (str == "DELETE") {
            method = METHODS::DELETE;
        } else if (str == "TRACE") {
            method = METHODS::TRACE;
        } else if (str == "CONNECT") {
            method = METHODS::CONNECT;
        }

        return method;
    }

    std::string method_to_string (METHODS method) {
        std::string str;
        if (method == METHODS::GET) {
            str == "GET";
        } else if (method == METHODS::HEAD) {
            str == "HEAD";
        } else if (method == METHODS::POST) {
            str == "POST";
        } else if (method == METHODS::PUT) {
            str == "PUT";
        } else if (method == METHODS::DELETE) {
            str == "DELETE";
        } else if (method == METHODS::TRACE) {
            str == "TRACE";
        } else if (method == METHODS::CONNECT) {
            str == "CONNECT";
        }
        return str;
    }
} // namespace tinyweb
    