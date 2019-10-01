#include "server.h"
#include <iostream>

namespace tinyweb {
    Server::Server(boost::asio::io_context& io_context, int port): 
        io_context_(io_context), 
        acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {}

    void Server::run() {
        Connection* connection = new Connection(io_context_, this);
        acceptor_.async_accept(
            connection->socket(),
            boost::bind(
                &tinyweb::Connection::open, connection,
                boost::asio::placeholders::error
            )
        );
    }

    void Server::add_route(tinyweb::Route route) {}
}