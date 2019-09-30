#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <functional>

#include "request.h"
#include "response.h"
#include "route.h"

namespace tinyweb {
    class Server {
        private:
            std::vector<tinyweb::Route> routes;
        public:
            void run(std::string host, int port);
            void add_route(tinyweb::Route route);
    };
}

#endif // SERVER_H
