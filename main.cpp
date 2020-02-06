#include <iostream>
#include <string>
#include <string.h>
#include "getRequest.h"


int main(int args, char **argv)
{
    if (args != 2)
    {
        std::cerr << "Try `" << std::string(argv[0]) << " --help' for more options." << std::endl;
        return -1;
    }
    if (strcmp (argv[1], "--help") == 0)
    {
        std::cout << "Usage: " <<  std::string(argv[0]) << " URL" << std::endl;
    }

        // http://bbgentoo.ilb.ru/distfiles/google-chrome-stable_48.0.2564.116-1_i386.deb
    //download("http://code.jquery.com/jquery-1.11.1.js", "./jquery-1.11.1.js");

    download("http://bbgentoo.ilb.ru/distfiles/google-chrome-stable_48.0.2564.116-1_i386.deb", "lolo1.deb");
   // download("http://google.com", "./google1");

    return 0;
}
