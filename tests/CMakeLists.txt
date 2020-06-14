set(TEST_SOURCES 
    test.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests tinyweb)