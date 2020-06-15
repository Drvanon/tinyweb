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
    /**
     * @brief Interface between sockets and routes
     * 
     * In the server one registers routes that will receive the
     * requests (tinyweb::Request) coming in on the sockets via 
     * connections (tinyweb::Connection).
     * 
     */
    class Server {
        private:
            std::vector<tinyweb::Route*> routes;
            boost::asio::io_context& io_context_;
            tcp::acceptor acceptor_;
            std::string host;
            int port;
            void accept_handler(const boost::system::error_code& error, Connection *connection);
        public:
            /**
             * @brief Construct a new Server object
             * 
             * @param io_context IO context responsible for handling the sockets.
             * @param port Port that the server should be listening to.
             */
            Server(boost::asio::io_context& io_context, int port);
            /**
             * @brief Start accepting connections on the port.
             * 
             */
            void run();
            /**
             * @brief Add a new route to this server.
             * 
             * Note that order matters. If a match is made with a specific route,
             * that route will run on a first come first serve basis. It is therefore
             * logical to structure the routes in such a way that the specific ones
             * are added first and the more general ones (e.g. a 404 catch all) last.
             * 
             * Also note that a 404 response has already been created, though it can be
             * replaced simply by adding a catchall.
             * 
             * @param route 
             */
            void add_route(Route* route);
            /**
             * @brief Run a specific route for a request.
             * 
             * This method is used internally by connections that call this function
             * when the request has been obtained completely.
             * 
             * @param request 
             * @return Response* 
             */
            Response* run_route(Request* request);
    };
}

#endif // SERVER_H
