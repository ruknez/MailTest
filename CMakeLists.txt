cmake_minimum_required(VERSION 3.10)

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

target_link_libraries(getDataByURL  stdc++fs)

target_link_libraries(getDataByURL_cli
    getDataByURL
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -Wextra -pedantic -Werror")

#target_compile_options(getDataByURL_cli PRIVATE)
#target_compile_options(getDataByURL PRIVATE)
if(BUILD_TESTS)

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

endif(BUILD_TESTS)

install(TARGETS getDataByURL_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(testGetAPI testGetAPI)
