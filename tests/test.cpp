#include <cassert>
#include <regex>
#include <string> 
#include <map>
#include <iostream>

#include "tinyweb.h"

#define ASSERT_THROWS( expression )             \
    do {                                        \
        bool thrown = false;                    \
        try {                                   \
            expression;                         \
        } catch (...) {                         \
            thrown = true;                      \
        }                                       \
        assert((#expression, thrown));          \
    } while (false)                             \

void test_header () {
    tinyweb::RequestHeader *header = new tinyweb::RequestHeader();
    header->set_field("Field1", "Body1");
    header->set_field("Field2", "Body2");
    header->set_field("Field3", "Body3");
    header->set_field("Field4", "Body4");
    header->set_field("Field5", "Body5");

    std::map<std::string, std::string> expected = {
        { "Field1", "Body1" },
        { "Field2", "Body2" },
        { "Field3", "Body3" },
        { "Field4", "Body4" },
        { "Field5", "Body5" },
    };

    assert( header->get_fields() == expected );
    assert( header->has_field("Field1") );
    assert( !header->has_field("Does not exist") );
}

void test_response() {
    tinyweb::ResponseHeader* header = new tinyweb::ResponseHeader();
    header->set_field("Field1", "Body1");
    header->set_field("Field2", "Body2");
    tinyweb::Response* response = new tinyweb::Response(
        header, 
        "Hello"
    );
    std::string a = "ABC";
    std::string b = "ABC";
    assert(a == b);    
    std::string response_string = response->str();
    std::string expected_string = "HTTP/1.1 200 OK\r\n"
    "Content-Length: 5\r\n"
    "Field1: Body1\r\n"
    "Field2: Body2\r\n"
    "\r\n"
    "Hello";
    assert(response_string == expected_string);
}


void test_regex_functions() {
    tinyweb::RequestHeader *header = new tinyweb::RequestHeader();
    
    header->parse("GET http://localhost/ HTTP/1.1");
    assert( header->get_version() == "1.1");
    assert( header->get_method() == tinyweb::GET );
    assert( header->get_uri() == "http://localhost/" );

    header->parse("POST * HTTP/2.1");
    assert( header->get_version() == "2.1");
    assert( header->get_method() == tinyweb::POST );
    assert( header->get_uri() == "*" );

    header->parse("CONNECT /asdqwe/qweasd/?klasmd=123 HTTP/3.3");
    assert( header->get_version() == "3.3" );
    assert( header->get_method() == tinyweb::CONNECT );
    assert( header->get_uri() == "/asdqwe/qweasd/?klasmd=123" );

    header->parse(
        "GET /ad/asd/ HTTP/1.1\r\n"
        "Content-Length: 500\r\n"
        "Other-Header: Sometext\r\n"
        "\r\n"
    );
    assert( header->get_fields()["Content-Length"] == "500");
    assert( header->get_fields()["Other-Header"] == "Sometext");
    assert( header->get_fields().size() == 2);

    ASSERT_THROWS( header->parse("HTTP/") );
    ASSERT_THROWS( header->parse("1.1") );
    ASSERT_THROWS( header->parse("12.1") );
    ASSERT_THROWS( header->parse("HTTP/12.1") );
    ASSERT_THROWS( header->parse("HTTP//1.1") );

    ASSERT_THROWS( header->parse("ASDLKM /asdasd/asd/ HTTP/1.1") );
    ASSERT_THROWS( header->parse("GET HTTP/1.1") );
    ASSERT_THROWS( header->parse("GET /aqwe/qwe?asdd=asd HTTP//1.2") );
}

int main () {
    test_regex_functions();
    test_header();
    test_response();
    std::cout << "All tests ran succesfully!" << std::endl;
    return 0;
}