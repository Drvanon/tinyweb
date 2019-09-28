#ifndef SERVER_H
#define SERVER_H

#include <map>
#include <string>
#include <functional>

#include "request.h"
#include "response.h"

namespace tinyweb {
    class Server {
        private:
            std::map<std::string,std::function<Response(Request)>> routes;
        public:
            void run(std::string host, int port);
            void add_route(std::string name, std::function<Response(Request)>);
    };
}

#endif // SERVER_H
