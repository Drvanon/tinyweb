#include <iostream>

#include "server.h"
#include "route.h"

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

    void Server::add_route(Route* route) {
        routes.push_back(route);
    }

    Response* Server::run_route(Request* request) {
        std::cout << "Got request: " << request->str() << std::endl;
        for (Route* route: routes) {
            if (route->match(request->get_uri())){
                Response* response = route->run(request);
                return response;
            }
        }

        ResponseHeader* header = new ResponseHeader();
        header->set_response_code(404, "");
        std::string text = "Page not found.";
        Response* route_not_found = new Response(header, text);
        return route_not_found;
    }
}