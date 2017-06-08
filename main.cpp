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

    unsigned int i_check = check_symbols(inStr);
    if (inStr.size() != i_check) {
        std::cout << "Sembols error\n";
        std::cout << "i_check = " << i_check << std::endl;
        std::cout << "size    = " << inStr.size() << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!check_brackets(inStr)) {
        std::cout << "Brackets error\n";
        exit(EXIT_FAILURE);
    }

    mathElement t;
    std::list<mathElement> mathList;

    for (unsigned int i = 0; i < inStr.size(); i++) {

        t = getStrElement(inStr, i);

        if (t.error) {
            std::cout << "Error parse math\n";
            exit(EXIT_FAILURE);
        }
        
        
        if (t.type_t != none_t) {
            i = t.i_end;
            if (t.type_t == brackets_t) i++;
            mathList.push_back(t);
        }
        else {
            mathList.push_back(t);
            break;
        }

        
        
        
    }

    unsigned int j = 0;
    for (std::list<mathElement>::iterator it = mathList.begin(); it != mathList.end(); it++) {
		j++;
		std::cout << j << ")   ";
		
		switch (it->type_t)
		{
			case variable_t:
				std::cout << "variable_t   ";
				break;
			case operator_t:
				std::cout << "operator_t   ";
				break;
			case brackets_t:
				std::cout << "brackets_t   ";
				break;
			case math_t:
				std::cout << "math_t       ";
				break;
			case number_t:
				std::cout << "number_t     ";
				break;
			default:
				std::cout << "none_t       ";
		}
		
		std::cout << it->i_start << "   ";
		std::cout << it->i_end   << "   ";
		
        std::cout << it->str << std::endl;
	}



    return 0;
}

