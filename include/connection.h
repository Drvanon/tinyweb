#include <string>
#include <functional>

#include <boost/asio.hpp>

#pragma once
#include "server.fwd.h"
#include "connection.fwd.h"

using boost::asio::ip::tcp;

namespace tinyweb {
  class Connection {
    private:
        tcp::socket socket_;
        tinyweb::Server *owner;
    public:
        Connection(boost::asio::io_context& io_context_, tinyweb::Server *server);
        ~Connection();
        tcp::socket& socket();
        void open(const boost::system::error_code& error);
  }; // class Connection
} // namespace tinyweb
