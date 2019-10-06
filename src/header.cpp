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
    Header::Header () {}

    Header* Header::from_map(std::map<std::string, std::string> map) {
        Header* header = (new Header());
        header->request_fields = map;
        return header;
    }

    void Header::parse_version(std::string request_line) {
        std::regex version_regex("HTTP\\/([0-9])\\.([0-9])");
        std::smatch sm;
        std::regex_search (request_line, sm, version_regex);

        if (sm.size() != 3) {
            throw InvalidHeaderException("Header invalid: HTTP version corrupt.");
        }

        // First match is "HTTP/1.1", the ones after that are the major and minor version.
        this->version_major = std::stoi(sm[1]);
        this->version_minor = std::stoi(sm[2]);
    }

    std::string Header::get_version() {
        return std::to_string(this->version_major) + "." + std::to_string(this->version_minor);
    }

    void Header::parse_method(std::string request_line) {
        std::regex method_regex ("^GET|^HEAD|^POST|^PUT|^DELETE|^TRACE|^CONNECT");
        std::smatch sm;
        std::regex_search (request_line, sm, method_regex);
        
        if (sm.size() != 1) {
            throw InvalidHeaderException("Header invalid: No valid method present.");
        } else if (sm[0] == "GET") {
            this->method = METHODS::GET;
        } else if (sm[0] == "HEAD") {
            this->method = METHODS::HEAD;
        } else if (sm[0] == "POST") {
            this->method = METHODS::POST;
        } else if (sm[0] == "PUT") {
            this->method = METHODS::PUT;
        } else if (sm[0] == "DELETE") {
            this->method = METHODS::DELETE;
        } else if (sm[0] == "TRACE") {
            this->method = METHODS::TRACE;
        } else if (sm[0] == "CONNECT") {
            this->method = METHODS::CONNECT;
        }         
    }

    METHODS Header::get_method() {
        return this->method;
    }

    void Header::parse_uri(std::string request_line) {
        std::regex uri_regex (" http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\\(\\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+ | \\* | (?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\\(\\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+ ");
        std::smatch sm;
        std::regex_search (request_line, sm, uri_regex);

        if (sm.size() != 1) {
            throw InvalidHeaderException("Header invalid: No valid URI present.");
        }

        std::string match = sm.str(0);
        this->uri = match.substr(1, match.size() - 2);
    }

    std::string Header::get_uri() {
        return this->uri;
    }

    void Header::parse_header_fields(std::string line) {
        std::regex header_regex ("([\\w-]*): (.*)");
        std::smatch sm;
        std::regex_search (line, sm, header_regex);

        if (sm.size() != 3) {
            throw InvalidHeaderException("Header invalid: corrupt header line.");
        }

        this->request_fields[sm.str(1)] = sm.str(2);
    }

    std::map<std::string, std::string> Header::get_header_fields() {
        return this->request_fields;
    }
    
    void Header::parse(std::string request_string) {
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
}
