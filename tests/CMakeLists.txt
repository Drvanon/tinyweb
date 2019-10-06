# Catch2
set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/extern/catch2)
add_library(Catch2::Catch IMPORTED INTERFACE)
set_property(TARGET Catch2::Catch PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${CATCH_INCLUDE_DIR}")

set(TEST_SOURCES 
    test.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests Catch2::Catch tinyweb)