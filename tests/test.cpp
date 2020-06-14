#include <cassert>
#include <regex>
#include <string> 

#include "header.h"

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
    return 0;
}