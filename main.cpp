#include "libs.h"
#include <cstdio>
#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>

void print_math_expression(const std::list<mathElement> &mathList, const unsigned int level);

int main(int argc, char **argv)
{

    if (argc < 2) {
        std::cout << "calc \"mathematical expression\"\n";
        exit(EXIT_FAILURE);
    }

    std::string inStr = argv[1];
    //std::cout << inStr << std::endl;

    std::cout << std::endl;

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

    bool error = false;
    std::list<mathElement> mathList = parse_math_expression(inStr, error);

    if (error == true) {
        std::cout << "Parse error\n";
        exit(EXIT_FAILURE);
    }

    //print_math_expression(mathList, 0);

    std::cout << "Input variables: \n";
    std::list<varElementType> varList = get_var_list();

    if (!(varList.empty())) {
        double d;
        for (std::list<varElementType>::const_iterator it = varList.begin(); it != varList.end(); it++) {
            std::cout << "  Input " << it->str << ": ";
            std::cin >> d;
            set_var_element(it->str, d);
        }
    }
    /*
    std::cout << "Список переменных: \n";
    varList = get_var_list();

    if (!(varList.empty())) {
        for (std::list<varElementType>::const_iterator it = varList.begin(); it != varList.end(); it++) {
            std::cout << "  " << it->str << " = " << it->number << std::endl;
        }
    }
*/
    while (mathList.size() > 1 ||
           (mathList.size() == 1 &&
            (mathList.begin()->type_t == variable_t || mathList.begin()->type_t == brackets_t))) {

        mathList = calculationMath(mathList);
    }

    std::list<mathElement>::const_iterator it = mathList.begin();

    std::cout << std::endl
              << it->number << std::endl;

    return 0;
}

void print_math_expression(const std::list<mathElement> &mathList, const unsigned int level)
{
    unsigned int j = 0;
    for (std::list<mathElement>::const_iterator it = mathList.begin(); it != mathList.end(); it++) {

        for (unsigned int i = 0; i < level; i++) {
            std::cout << "    ";
        }

        j++;
        printf("%4d)  ", j);
        //std::cout << j << ")   ";

        switch (it->type_t) {
        case variable_t:
            std::cout << "variable_t   ";
            break;
        case operator_t:
            std::cout << "operator_t   ";
            break;
        case brackets_t:
            std::cout << "brackets_t   ";
            break;
        case function_t:
            std::cout << "function_t   ";
            break;
        case number_t:
            std::cout << "number_t     ";
            break;
        default:
            std::cout << "none_t       ";
        }

        //std::cout << it->i_start << "   ";
        //std::cout << it->i_end   << "   ";

        printf("%4d  ", it->i_start);
        printf("%4d    ", it->i_end);

        std::cout << it->str << std::endl;

        if (it->type_t == brackets_t) {
            print_math_expression(it->childList, level + 1);
            if (level == 0)
                std::cout << std::endl;
        }
    }
    return;
}
