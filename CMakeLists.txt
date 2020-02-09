cmake_minimum_required(VERSION 3.12)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(GetDataByURL VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(GetDataByURL VERSION 0.0.1)
endif()

add_executable(getDataByURL_cli main.cpp)
add_library(getDataByURL getAPI.cpp)


set_target_properties(getDataByURL_cli getDataByURL PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(getDataByURL_cli PRIVATE
    getDataByURL
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -Wextra -pedantic -Werror")

#target_compile_options(getDataByURL_cli PRIVATE)
#target_compile_options(getDataByURL PRIVATE)


find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(testGetAPI testsGetAPI.cpp)

set_target_properties(testGetAPI PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(testGetAPI PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(testGetAPI
    ${Boost_LIBRARIES}
    getDataByURL
)

target_compile_options(testGetAPI PRIVATE)

# Add a test to the project to be run
add_test(testGetAPI testGetAPI)