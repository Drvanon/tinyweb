#include <string>
#include <functional>

#include <boost/asio.hpp>

#include "header.h"
#include "request.h"
#include "response.h"

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
        boost::asio::streambuf input_stream;

        void handle_request (
            const boost::system::error_code& error, 
            long unsigned int bytes_transferred
        );

        void handle_request_body (
            const boost::system::error_code& error, 
            size_t bytes_transferred,
            Request* request 
        );

        void handle_response (
            const boost::system::error_code& error, 
            long unsigned int bytes_transferred
        );

        void make_response (Request* request);
    public:
        Connection(boost::asio::io_context& io_context_, tinyweb::Server *server);
        ~Connection();
        tcp::socket& socket();
        void open(const boost::system::error_code& error);
  }; // class Connection
} // namespace tinyweb
