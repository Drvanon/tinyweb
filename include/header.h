#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <map>

namespace tinyweb{
    class Header {
        private:
            std::map<std::string, std::string> headers_;
        public:
            std::string get_headers();
            Header* from_map(std::map<std::string, std::string>);
    };
}

#endif