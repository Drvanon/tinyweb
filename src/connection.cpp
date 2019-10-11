#include "connection.h"
#include "server.h"

#include <iostream>
#include <functional>
#include <sstream>

using boost::asio::ip::tcp;

std::string MESSAGE = "HTTP/1.1 200 No Content\r\n"
"Content-length: 8\r\n"
"\r\n"
"Welcome!";

namespace tinyweb {
    Connection::Connection(boost::asio::io_context& io_context, tinyweb::Server* server): 
      socket_(io_context), owner(server) {}

    void Connection::handle_request (const boost::system::error_code& error, size_t bytes_transferred) {
        input_stream.commit(bytes_transferred);

        std::string request_string (
            buffers_begin(input_stream.data()), 
            buffers_begin(input_stream.data()) + bytes_transferred
            );
        input_stream.consume(bytes_transferred);
        std::cout << "Received request:\n" << request_string << "<ends here" << std::endl;

        Header* header = (new Header());
        header->parse(request_string);

        auto content_length_iter = header->get_header_fields().find("Content-Length");
        if (content_length_iter != header->get_header_fields().end()) {
            std::cout <<  "Got content length header" << std::endl;
            int content_length;
            try {
                content_length = std::stoi(header->get_header_fields()["Content-Length"]);
            } catch (...) {
                std::cout << "Could not get proper content length." << std::endl;
            }
            if (input_stream.in_avail() < content_length) {
                socket_.async_read_some(
                    boost::asio::buffer(input_stream.prepare(content_length)), 
                    boost::bind(
                        &Connection::handle_request_body, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred
                    )
                );
            } else {
                handle_request_body(error, content_length);
            }
        }
    }

    void Connection::handle_request_body (const boost::system::error_code& error, size_t bytes_transferred) {
        input_stream.commit(bytes_transferred);
        std::string body (
            buffers_begin(input_stream.data()), 
            buffers_begin(input_stream.data()) + bytes_transferred
            );
        input_stream.consume(bytes_transferred);
    }

    void Connection::handle_response (const boost::system::error_code& error, long unsigned int bytes_transferred) {
        std::cout << "Sent response" << std::endl;
    }

    void Connection::open(const boost::system::error_code& error) {
        owner->run();

        if (!error) {
            boost::system::error_code error;

            boost::asio::async_read_until(
                socket_,
                input_stream, 
                "\r\n\r\n",
                boost::bind(
                    &Connection::handle_request, this,
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