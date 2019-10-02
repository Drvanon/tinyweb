#include "connection.h"
#include "server.h"

#include <iostream>
#include <functional>

using boost::asio::ip::tcp;

std::string MESSAGE = "HTTP/1.1 200 No Content\r\n"
"Content-length: 8\r\n"
"\r\n"
"Welcome!";

namespace tinyweb {
    Connection::Connection(boost::asio::io_context& io_context, tinyweb::Server* server): 
      socket_(io_context), owner(server) {}

    void Connection::handle_request (const boost::system::error_code& error, long unsigned int bytes_transferred) {
        std::cout << "Received request:\n" << std::string(request_header) << "<ends here" << std::endl;
    }

    void Connection::handle_response (const boost::system::error_code& error, long unsigned int bytes_transferred) {
        std::cout << "Sent response" << std::endl;
    }

    void Connection::open(const boost::system::error_code& error) {
        owner->run();

        if (!error) {
            boost::system::error_code error;
             
            socket_.async_read_some(
                boost::asio::buffer(request_header), 
                boost::bind(
                    &Connection::handle_request, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred
                )
            );
            boost::asio::async_write(
                socket_, 
                boost::asio::buffer(MESSAGE), 
                boost::bind(
                    &Connection::handle_response, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred 
                )
            );
        }
    }

    tcp::socket& Connection::socket() {
        return socket_;
    }
}