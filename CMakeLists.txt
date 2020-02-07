cmake_minimum_required(VERSION 3.12)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(TestGetByURL VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(TestGetByURL VERSION 0.0.1)
endif()

add_executable(testGetByURL_cli main.cpp)
add_library(testGetByURL getAPI.cpp)


set_target_properties(testGetByURL_cli testGetByURL PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(testGetByURL_cli PRIVATE
    testGetByURL
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -Wextra -pedantic -Werror")

target_compile_options(testGetByURL_cli PRIVATE)
target_compile_options(testGetByURL PRIVATE)