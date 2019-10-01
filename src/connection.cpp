#include "connection.h"
#include "server.h"

#include <iostream>

using boost::asio::ip::tcp;

void handlewrite(const boost::system::error_code& error, size_t bytes_transferred) {
    std::cout << "Handled write" << std::endl;
}
std::string MESSAGE = "HTTP/1.1 200 No Content\r\n"
"Content-length: 8\r\n"
"\r\n"
"Welcome!";

namespace tinyweb {
    Connection::Connection(boost::asio::io_context& io_context, tinyweb::Server* server): 
      socket_(io_context), owner(server) {}

    void Connection::open(const boost::system::error_code& error) {
        owner->run();

        if (!error) {
            boost::asio::async_write(socket_, boost::asio::buffer(MESSAGE), &handlewrite);
        }
    }

    tcp::socket& Connection::socket() {
        return socket_;
    }
}