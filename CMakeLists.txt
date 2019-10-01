cmake_minimum_required (VERSION 2.6)
project (tinyweb)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(Boost 1.40.0 REQUIRED COMPONENTS system)
find_package(Threads)

set(TINYWEB_SOURCES 
    src/response.cpp
    src/connection.cpp
    src/server.cpp
    src/request.cpp
    src/header.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${Boost_INCLUDE_DIR})

add_library(tinyweb ${TINYWEB_SOURCES})
add_executable (example example/example_server.cpp)

target_link_libraries(tinyweb PUBLIC ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(example PUBLIC tinyweb)
