#include "libs.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char **argv)
{

    if (argc < 2) {
        std::cout << "calc \"math\"\n";
        exit(EXIT_FAILURE);
    }

    std::string inStr = argv[1];
    std::cout << inStr << std::endl;

    if (!check_symbols(inStr)) {
        std::cout << "Sembols error\n";
        exit(EXIT_FAILURE);
    }

    if (!check_brackets(inStr)) {
        std::cout << "Brackets error\n";
        exit(EXIT_FAILURE);
    }

    std::list<mathElement *> flist;

    unsigned int index = 0;
    return 0;
}

