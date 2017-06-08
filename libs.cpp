#include "libs.h"
#include <cctype>

bool check_brackets(const std::string &str)
{
    int b = {0};
    for (unsigned int i = 0; i < str.size(); i++) {
        if (str[i] == '(')
            b++;
        if (str[i] == ')')
            b--;
        if (b < 0) {
            return false;
        }
    }
    if (b != 0) {
        return false;
    }
    return true;
}

unsigned int check_symbols(const std::string &str)
{
    unsigned int i = 0;
    for (; i < str.size(); i++) {
        if (!is_operator(str[i]) &&
            !isalnum(str[i]) &&
            str[i] != '_' && str[i] != '.' && str[i] != ',' &&
            str[i] != '(' && str[i] != ')') {
            break;
        }
    }
    return i;
}

mathElement getStrElement(const std::string &inStr, unsigned int index)
{
    mathElement element = {"", none_t, false, 0, 0};

    for (; index < inStr.size(); index++) {
        if (!isspace(inStr[index])) {
            break;
        }
    }

    if (index == inStr.size()) {
        element.type_t = none_t;
        element.i_start = index;
        element.i_end = index;
    }
    else if (isalpha(inStr[index]) || inStr[index] == '_') {

        element.str.push_back(inStr[index]);
        element.i_start = index;
        element.i_end = index;

        for (; index < inStr.size(); index++) {
            if (isalnum(inStr[index]) || inStr[index] == '_') {
                element.str.push_back(inStr[index]);
                element.i_end = index;
            }
            else {
                if (is_math_function(element.str))
                    element.type_t = math_t;
                else
                    element.type_t = variable_t;
                break;
            }
        }
    }
    else if (inStr[index] == '(') {

        int len = 0;
        int b = 1;
        index++;
        element.type_t = brackets_t;

        for (; index < inStr.size(); index++) {
            if (inStr[index] == ')') {
                b--;
                if (b == 0)
                    break;
            }
            if (b < 0)
                break;

            if (b > 0) {
                element.str.push_back(inStr[index]);
                if (len == 0)
                    element.i_start = index;
                element.i_end = index;
                len++;
            }

            if (inStr[index] == '(')
                b++;
        }
        if (b != 0)
            element.error = true;
        if (len == 0)
            element.error = true;
    }
    else if (isdigit(inStr[index]) || inStr[index] == '.' || inStr[index] == ',') {

        element.type_t = number_t;
        element.str.push_back(inStr[index]);
        element.i_start = index;
        element.i_end = index;

        for (; index < inStr.size(); index++) {
            if (isdigit(inStr[index]) || inStr[index] == '.' || inStr[index] == ',') {
                element.str.push_back(inStr[index]);
                element.i_end = index;
            }
            else
                break;
        }

        unsigned int lenDot = 0;
        for (unsigned int j = 0; j < element.str.size(); j++) {
            if (element.str[j] == '.')
                lenDot++;
            if (element.str[j] == ',') {
                element.str[j] = '.';
                lenDot++;
            }
        }

        if (lenDot > 1)
            element.error = true;
        if (element.str.compare(".") == 0)
            element.error = true;
    }
    else if (is_operator(inStr[index])) {
        element.type_t = operator_t;
        element.i_start = index;
        element.i_end = index;
        element.str.push_back(inStr[index]);
    }
    else {
        element.type_t = none_t;
        element.i_start = index;
        element.i_end = index;
        element.error = true;
    }
    return element;
}

bool is_math_function(const std::string &str)
{
    bool status = false;

    if (str.compare("sin") == 0) {
        status = true;
    }
    else if (str.compare("cos") == 0) {
        status = true;
    }
    else {
        status = false;
    }

    return false;
}

bool is_operator(const char &ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
        return true;
    }
    return false;
}
