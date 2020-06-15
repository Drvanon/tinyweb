#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <map>
#include <regex>

#include "methods.h"

/**
 * @brief An invalid header has been created (often while parsing a string).
 * 
 */
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

/**
 * @brief A bad response has been constructed.
 * 
 */
struct BadResponseException : public std::exception
{
    private:
        /**
         * @brief Reason for the exception
         * 
         */
        std::string reason_;
    public:
        /**
         * @brief Construct a new Bad Response Exception object
         * 
         * @param reason 
         */
        BadResponseException(std::string reason): reason_(reason) {}
        const char * what () const throw ()
        {
            return reason_.c_str();
        }
};

namespace tinyweb{
    class IHeader {
        protected:
            /**
             * @brief Map to represent the HTTP fields.
             * 
             */
            std::map<std::string, std::string> fields;
            /**
             * @brief Method that this route accepts.
             * 
             */
            METHODS method;
        public:
            /**
             * @brief Get a map representation of the HTTP fields.
             * 
             * @return std::map<std::string, std::string> 
             */
            virtual std::map<std::string, std::string> get_fields() = 0;
            /**
             * @brief Set a header field 
             * 
             * Note that this is internally represented as a map and therefore can 
             * not store multiple values (yet).
             * 
             * @param field 
             * @param body 
             */
            virtual void set_field(std::string field, std::string body) = 0;
            /**
             * @brief Check if this header has a specific field.
             * 
             * @param field 
             * @return true 
             * @return false 
             */
            virtual bool has_field(std::string field);
            /**
             * @brief Get the string representation of this header.
             * 
             * @return std::string 
             */
            virtual std::string str() = 0;
            virtual ~IHeader() {}
    };

    class RequestHeader: public IHeader {
        private:
            void parse_version(std::string request_line);
            void parse_uri(std::string request_line);
            
            /**
             * @brief Parse a field line of a header. 
             * 
             * @param line 
             */
            void parse_header_field(std::string line);
            void parse_method(std::string request_line);
            int version_major, version_minor;
            std::string uri;
        public:
            RequestHeader ();
            /**
             * @brief Get the HTTP version 
             * 
             * @return std::string 
             */
            std::string get_version();
            /**
             * @brief Get the uri string 
             * 
             * @return std::string 
             */
            std::string get_uri();
            /**
             * @brief Get the HTTP method 
             * 
             * @return METHODS 
             */
            METHODS get_method();

            /**
             * @brief Parse a request string and store it's information in self.
             * 
             * @param request_string 
             */
            virtual void parse(std::string string);
            /**
             * @brief Get the string representation of the tinyweb::RequestHeader.
             * 
             * @return std::string 
             */
            virtual std::string str();
            virtual void set_field(std::string field, std::string body);
            virtual std::map<std::string, std::string> get_fields();
    };

    class ResponseHeader: public IHeader {
        private:
            int status_code = 0;
            std::string reason_phrase;
        public:
            /**
             * @brief Construct a new Response Header object
             * 
             * This class is meant to represent headers to HTTP responses.
             * 
             */
            ResponseHeader();
            ~ResponseHeader();
            /**
             * @brief Set the response 
             * 
             * If an empty string is provided the reason will automatically be set
             * to a standard reason as defined in the HTTP specifications.
             * 
             * @param code 
             * @param reason 
             */
            void set_response_code(int code, std::string reason);
            /**
             * @brief Get the response code if it has been set.
             * 
             * The response code is initialized to 0.
             * 
             * @return int 
             */
            int get_response_code();
            
            virtual std::map<std::string, std::string> get_fields();
            virtual void set_field(std::string field, std::string body);

            /**
             * @brief Get the string representation of this HTTP response.
             * 
             * @return std::string 
             */
            virtual std::string str();
    }; 
}

#endif