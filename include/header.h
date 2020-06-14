#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <map>
#include <regex>

#include "methods.h"

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

struct BadResponseException : public std::exception
{
    private:
        std::string reason_;
    public:
        BadResponseException(std::string reason): reason_(reason) {}
        const char * what () const throw ()
        {
            return reason_.c_str();
        }
};

namespace tinyweb{
    class IHeader {
        protected:
            std::map<std::string, std::string> fields;
            METHODS method;
        public:
            virtual void parse(std::string string) = 0;
            virtual std::map<std::string, std::string> get_fields() = 0;
            virtual void set_field(std::string field, std::string body) = 0;
            virtual std::string str() = 0;
            virtual ~IHeader() {}
    };

    class RequestHeader: public IHeader {
        private:
            void parse_version(std::string request_line);
            void parse_uri(std::string request_line);
            void parse_header_fields(std::string line);
            void parse_method(std::string request_line);
            int version_major, version_minor;
            std::string uri;
        public:
            RequestHeader ();
            std::string get_version();
            std::string get_uri();
            METHODS get_method();

            virtual void parse(std::string string);
            virtual std::map<std::string, std::string> get_fields();
            virtual std::string str();
            virtual void set_field(std::string field, std::string body);
    };

    class ResponseHeader: public IHeader {
            int status_code;
            std::string reason_phrase;
        public:
            ResponseHeader();
            ~ResponseHeader();
            void set_response_code(int code, std::string reason);
            
            virtual void parse(std::string string);
            
            virtual std::map<std::string, std::string> get_fields();
            virtual void set_field(std::string field, std::string body);
            virtual std::string str();
    }; 
}

#endif