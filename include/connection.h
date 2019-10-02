#include <string>
#include <functional>

#include <boost/asio.hpp>

#pragma once
#include "server.fwd.h"
#include "connection.fwd.h"

using boost::asio::ip::tcp;

const int MAX_REQUEST_HEADER = 3000;

namespace tinyweb {
  class Connection {
    private:
        tcp::socket socket_;
        tinyweb::Server *owner;
        char request_header[MAX_REQUEST_HEADER];

        void handle_request (
            const boost::system::error_code& error, 
            long unsigned int bytes_transferred
        );

        void handle_response (
            const boost::system::error_code& error, 
            long unsigned int bytes_transferred
        );
    public:
        Connection(boost::asio::io_context& io_context_, tinyweb::Server *server);
        ~Connection();
        tcp::socket& socket();
        void open(const boost::system::error_code& error);
  }; // class Connection
} // namespace tinyweb
