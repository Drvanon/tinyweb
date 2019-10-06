#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <map>
#include <regex>

enum METHODS {
    GET,
    HEAD,
    POST,
    PUT,
    DELETE,
    TRACE,
    CONNECT
};

struct InvalidHeaderException : public std::exception
{
    private:
        std::string reason_;
    public:
        InvalidHeaderException(std::string reason): reason_(reason) {}
        const char * what () const throw ()
        {
            return reason_.c_str();
        }
};

namespace tinyweb{
    class Header {
        private:
            std::map<std::string, std::string> request_fields;
            void parse_version(std::string request_line);
            void parse_method(std::string request_line);
            void parse_uri(std::string request_line);
            void parse_header_fields(std::string line);
            int version_major, version_minor;
            METHODS method;
            std::string uri;
        public:
            Header();
            void parse(std::string request_string);
            Header* from_map(std::map<std::string, std::string>);
            std::string get_version();
            std::string get_uri();
            METHODS get_method();
            std::map<std::string, std::string> get_header_fields();
    };
}

#endif