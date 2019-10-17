#include "connection.h"
#include "server.h"

#include <iostream>
#include <functional>
#include <sstream>

using boost::asio::ip::tcp;

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

        RequestHeader* header = (new RequestHeader());
        header->parse(request_string);

        Request* request = (new Request(header));        
        auto content_length_iter = header->get_fields().find("Content-Length");
        if (content_length_iter != header->get_fields().end()) {
            int content_length;
            try {
                content_length = std::stoi(header->get_fields()["Content-Length"]);
            } catch (...) {
                std::cerr << "Could not get proper content length." << std::endl;
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

    void Connection::make_response (Request request) {
        Response* response = owner->run_route(request);
        socket_.async_write_some(
            boost::asio::buffer(response->str()), 
            boost::bind(      
                &Connection::handle_response, this,
                boost::asio::placeholders::error, 
                boost::asio::placeholders::bytes_transferred
            )
        );
    }

    void Connection::handle_response (const boost::system::error_code& error, long unsigned int bytes_transferred) {
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