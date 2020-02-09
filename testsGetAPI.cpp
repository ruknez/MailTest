#define BOOST_TEST_MODULE testGetAPI

#include "getAPI.h"

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

BOOST_AUTO_TEST_SUITE(testGetAPI) // Начало набора тесто

BOOST_AUTO_TEST_CASE(testCreatFileName)
{
    BOOST_CHECK(creatFileName("bbgentoo.ilb.ru/distfiles/google-chrome-stable_48.0.2564.116-1_i386.deb") == "google-chrome-stable_48.0.2564.116-1_i386.deb");
    BOOST_CHECK(creatFileName("bbgentoo.ilb.ru") == "index.html");
}

BOOST_AUTO_TEST_CASE(testparsingURL)
{
    auto [path, domain, port] = parsingURL("http://bbgentoo.ilb.ru/distfiles/google-chrome-stable_48.0.2564.116-1_i386.deb");
    BOOST_CHECK(domain == "bbgentoo.ilb.ru");
    BOOST_CHECK(path == "/distfiles/google-chrome-stable_48.0.2564.116-1_i386.deb");
    BOOST_CHECK(port == 80);
    BOOST_CHECK_THROW(parsingURL("bbgentoo.ilb.ru/distfiles/google-chrome-stable_48.0.2564.116-1_i386.deb"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testisAnswerOk)
{
    std::string inputOKdata = "HTTP/1.1 200 OK Date: Sat, 08 Feb 2020 21:30:43 GMT Server: Apache Last-Modified: Wed, 24 Feb 2016 08:38:45 GMT ETag: 2d564a8-52c7ffe736f40";
    BOOST_CHECK(isAnswerOk(inputOKdata) == true);

    std::string inputNOTOKdata = "Not OK answer HTTP/1.1 404 Not Found Date: Sat, 08 Feb 2020 21:45:58 GMT Server: Apache Content-Length: 19";
    BOOST_CHECK(isAnswerOk(inputNOTOKdata) == false);
}

BOOST_AUTO_TEST_SUITE_END() // Конец набора тестов
