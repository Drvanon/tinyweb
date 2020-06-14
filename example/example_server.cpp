#include <iostream>
#include <string>
#include <map>
#include <functional>

#include "tinyweb.h"

tinyweb::Response* action(tinyweb::Request* request) {
    std::cout << "In custom run" << std::endl;
    tinyweb::ResponseHeader* header = new tinyweb::ResponseHeader();
    header->set_response_code(200, "");
    std::string response_text = "Hello World!";
    tinyweb::Response* response = new tinyweb::Response(header, response_text);
    header->set_field("Content-Length", std::to_string(response_text.size()));
    
    return response;
}

int main(int argc, char const *argv[]) {
    try {
        boost::asio::io_context context;

        tinyweb::Server server(context, 8080);
        tinyweb::Route* myRoute = new tinyweb::Route("/", &action);

        server.add_route(myRoute);
        server.run();
        context.run();
    } catch (std::exception& e) {
        std::cout << "Got error: " << e.what() << std::endl;
    }

    return 0;
}
