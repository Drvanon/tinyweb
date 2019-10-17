#include "header.h"

#include <sstream>
#include <iostream>
#include <regex>

std::string get_first_line(std::string input) {
    std::istringstream f(input);
    std::string line;
    std::getline(f, line);
    return line;
}

namespace tinyweb {
    RequestHeader::RequestHeader () {}

    RequestHeader* RequestHeader::from_map(std::map<std::string, std::string> map) {
        RequestHeader* header = (new RequestHeader());
        header->fields = map;
        return header;
    }

    void RequestHeader::parse_version(std::string request_line) {
        std::regex version_regex("HTTP\\/([0-9])\\.([0-9])");
        std::smatch sm;
        std::regex_search (request_line, sm, version_regex);

        if (sm.size() != 3) {
            throw InvalidHeaderException("RequestHeader invalid: HTTP version corrupt.");
        }

        // First match is "HTTP/1.1", the ones after that are the major and minor version.
        this->version_major = std::stoi(sm[1]);
        this->version_minor = std::stoi(sm[2]);
    }

    std::string RequestHeader::get_version() {
        return std::to_string(this->version_major) + "." + std::to_string(this->version_minor);
    }

    void RequestHeader::parse_method(std::string request_line) {
        std::regex method_regex ("^GET|^HEAD|^POST|^PUT|^DELETE|^TRACE|^CONNECT");
        std::smatch sm;
        std::regex_search (request_line, sm, method_regex);
        
        if (sm.size() != 1) {
            throw InvalidHeaderException("RequestHeader invalid: No valid method present.");
        } else {
            this->method = string_to_method(sm.str(0));
        }         
    }

    tinyweb::METHODS RequestHeader::get_method() {
        return this->method;
    }

    void RequestHeader::parse_uri(std::string request_line) {
        std::regex uri_regex (" http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\\(\\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+ | \\* | (?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\\(\\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+ ");
        std::smatch sm;
        std::regex_search (request_line, sm, uri_regex);

        if (sm.size() != 1) {
            throw InvalidHeaderException("RequestHeader invalid: No valid URI present.");
        }

        std::string match = sm.str(0);
        this->uri = match.substr(1, match.size() - 2);
    }

    std::string RequestHeader::get_uri() {
        return this->uri;
    }

    void RequestHeader::parse_header_fields(std::string line) {
        std::regex header_regex ("([\\w-]*): (.*)");
        std::smatch sm;
        std::regex_search (line, sm, header_regex);

        if (sm.size() != 3) {
            throw InvalidHeaderException("RequestHeader invalid: corrupt header line.");
        }

        this->fields[sm.str(1)] = sm.str(2);
    }

    std::map<std::string, std::string> RequestHeader::get_fields() {
        return this->fields;
    }
    
    void RequestHeader::parse(std::string request_string) {
        std::istringstream f(request_string);
        std::string line;
        std::getline(f, line);
        
        parse_version(line);
        parse_method(line);
        parse_uri(line);

        while (getline(f, line)) {
            if (line == "\r") {
                break;
            }

            parse_header_fields(line);
        }
    }

    std::string RequestHeader::str () { 
        return (
            method_to_string(method) + " " + uri + " HTTP/" + get_version() + "\n"

        ); 
    }

    void ResponseHeader::set_response_code(int code, std::string reason) {
        if ( 99 > code > 999 ) {
            throw BadResponseException("Status code out of bounds");
        }
        if (reason == "") {
            switch (code) {
                case 100: reason_phrase = "Continue"; break;
                case 101: reason_phrase = "Switching Protocols"; break;
                case 200: reason_phrase = "OK"; break;
                case 201: reason_phrase = "Created"; break;
                case 202: reason_phrase = "Accepted"; break;
                case 203: reason_phrase = "Non-Authoritative Information"; break;
                case 204: reason_phrase = "No Content"; break;
                case 205: reason_phrase = "Reset Content"; break;
                case 206: reason_phrase = "Partial Content"; break;
                case 300: reason_phrase = "Multiple Choices"; break;
                case 301: reason_phrase = "Moved Permanently"; break;
                case 302: reason_phrase = "Found"; break;
                case 303: reason_phrase = "See Other"; break;
                case 304: reason_phrase = "Not Modified"; break;
                case 305: reason_phrase = "Use Proxy"; break;
                case 307: reason_phrase = "Temporary Redirect"; break;
                case 400: reason_phrase = "Bad Request"; break;
                case 401: reason_phrase = "Unauthorized"; break;
                case 402: reason_phrase = "Payment Required"; break;
                case 403: reason_phrase = "Forbidden"; break;
                case 404: reason_phrase = "Not Found"; break;
                case 405: reason_phrase = "Method Not Allowed"; break;
                case 406: reason_phrase = "Not Acceptable"; break;
                case 407: reason_phrase = "Proxy Authentication "; break;
                case 408: reason_phrase = "Request Timeout"; break;
                case 409: reason_phrase = "Conflict"; break;
                case 410: reason_phrase = "Gone"; break;
                case 411: reason_phrase = "Length Required"; break;
                case 412: reason_phrase = "Precondition Failed"; break;
                case 413: reason_phrase = "Payload Too Large"; break;
                case 414: reason_phrase = "URI Too Long"; break;
                case 415: reason_phrase = "Unsupported Media Type"; break;
                case 416: reason_phrase = "Range Not Satisfiable"; break;
                case 417: reason_phrase = "Expectation Failed"; break;
                case 426: reason_phrase = "Upgrade Required"; break;
                case 500: reason_phrase = "Internal Server Error"; break;
                case 501: reason_phrase = "Not Implemented"; break;
                case 502: reason_phrase = "Bad Gateway"; break;
                case 503: reason_phrase = "Service Unavailable"; break;
                case 504: reason_phrase = "Gateway Timeout"; break;
                case 505: reason_phrase = "HTTP Version Not "; break;
                default: reason_phrase = "No message";
            }
        } else {
            reason_phrase = reason;
        }
    }

    std::string ResponseHeader::str() {
        std::string fields_string;
        std::map<std::string, std::string>::iterator it;
        for (it = fields.begin(); it != fields.end(); it++) {
            fields_string += it->first + ": " + it->second + "\r\n";
        }
        return "HTTP/1.1 " + std::to_string(status_code) + " " + reason_phrase + "\r\n"
            + fields_string + "\r\n";
    }
}
