#include "header.h"


std::string tinyweb::Header::get_headers() {
    return "";
}
tinyweb::Header* tinyweb::Header::from_map(std::map<std::string, std::string>) {
    return (new tinyweb::Header());
}

