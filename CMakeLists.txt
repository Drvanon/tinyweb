cmake_minimum_required (VERSION 2.6)
project (tinyweb)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(TINYWEB_SOURCES 
    src/response.cpp
    src/server.cpp
    src/request.cpp
    src/header.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(tinyweb ${TINYWEB_SOURCES})
link_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable (example example/example_server.cpp)
target_link_libraries(example tinyweb)