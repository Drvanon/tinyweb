#if !defined(REQUEST_H)
#define REQUEST_H

#include "header.h"

namespace tinyweb {
    class Request {
        public:
            tinyweb::Header* header;
    };
}

#endif // REQUEST_H
