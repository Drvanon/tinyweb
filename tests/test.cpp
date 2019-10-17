#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <catch.hpp>
#include <regex>
#include <string> 

#include "header.h"

TEST_CASE( "Regex functions", "[regex]") {
    tinyweb::RequestHeader *header = new tinyweb::RequestHeader();
    
    header->parse("GET http://localhost/ HTTP/1.1");
    REQUIRE( header->get_version() == "1.1");
    REQUIRE( header->get_method() == tinyweb::GET );
    REQUIRE( header->get_uri() == "http://localhost/" );

    header->parse("POST * HTTP/2.1");
    REQUIRE( header->get_version() == "2.1");
    REQUIRE( header->get_method() == tinyweb::POST );
    REQUIRE( header->get_uri() == "*" );

    header->parse("CONNECT /asdqwe/qweasd/?klasmd=123 HTTP/3.3");
    REQUIRE( header->get_version() == "3.3" );
    REQUIRE( header->get_method() == tinyweb::CONNECT );
    REQUIRE( header->get_uri() == "/asdqwe/qweasd/?klasmd=123" );

    header->parse(
        "GET /ad/asd/ HTTP/1.1\r\n"
        "Content-Length: 500\r\n"
        "Other-Header: Sometext\r\n"
        "\r\n"
    );
    REQUIRE( header->get_fields()["Content-Length"] == "500");
    REQUIRE( header->get_fields()["Other-Header"] == "Sometext");
    REQUIRE( header->get_fields().size() == 2);

    REQUIRE_THROWS( header->parse("HTTP/") );
    REQUIRE_THROWS( header->parse("1.1") );
    REQUIRE_THROWS( header->parse("12.1") );
    REQUIRE_THROWS( header->parse("HTTP/12.1") );
    REQUIRE_THROWS( header->parse("HTTP//1.1") );

    REQUIRE_THROWS( header->parse("ASDLKM /asdasd/asd/ HTTP/1.1") );
    REQUIRE_THROWS( header->parse("GET HTTP/1.1") );
    REQUIRE_THROWS( header->parse("GET /aqwe/qwe?asdd=asd HTTP//1.2") );
}