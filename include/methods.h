#include <string>

namespace tinyweb
{
    enum METHODS {
        GET,
        HEAD,
        POST,
        PUT,
        DELETE,
        TRACE,
        CONNECT
    };

    METHODS string_to_method (std::string str);
    std::string method_to_string (METHODS method);
} // namespace tinyweb
