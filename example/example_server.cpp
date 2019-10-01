#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "tinyweb.h"

int main(int argc, char const *argv[])
{
    try {
        boost::asio::io_context context;

        tinyweb::Server server(context, 8080);
        server.run();
        context.run();
    } catch (std::exception& e) {
        std::cout << "Got error: " << e.what() << std::endl;
    }

    return 0;
}
