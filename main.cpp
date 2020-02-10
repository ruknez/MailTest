#include <iostream>
#include <string>
#include <string.h>
#include "getAPI.h"

int main(int args, char **argv)
{
    if (args != 2)
    {
        std::cerr << "Try `" << std::string(argv[0]) << " --help' for more options." << std::endl;
        return -1;
    }
    if (strcmp(argv[1], "--help") == 0)
    {
        std::cout << "Usage: " << std::string(argv[0]) << " URL" << std::endl;
    }

    try
    {
        download(argv[1]);
        //download("http://code.jquery.com/jquery-1.11.1.js");
        // download ("https://download.geofabrik.de/russia.html");
        // download("http://bbgentoo.ilb.ru/distfiles/google-chrome-stable_48.0.2564.116-1_i386.deb");
    }
    catch (const std::invalid_argument &ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    catch (const std::runtime_error &ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "I catch unknown exception \n";
    }

    return 0;
}
