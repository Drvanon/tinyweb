#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <vector>
#include <functional>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "request.h"
#include "response.h"
#include "route.h"

#include "connection.h"

using boost::asio::ip::tcp;

namespace tinyweb {
    class Server {
        private:
            std::vector<tinyweb::Route*> routes;
            boost::asio::io_context& io_context_;
            tcp::acceptor acceptor_;
            std::string host;
            int port;
            void accept_handler(const boost::system::error_code& error, Connection *connection);
        public:
            Server(boost::asio::io_context& io_context, int port);
            void run();
            void add_route(Route* route);
            Response* run_route(Request request);
    };
}

#endif // SERVER_H
