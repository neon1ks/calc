#include "libs.h"
#include <cctype>
#include <cmath>

static std::list<varElementType> varList;

void add_in_var_list(const std::string varStr);

double calc_function(const std::string &funcStr, const double &number);

bool is_begin_number(const int ch);

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
            !isalnum(str[i]) && !isspace(str[i]) &&
            str[i] != '_' && str[i] != '.' && str[i] != ',' &&
            str[i] != '(' && str[i] != ')') {
            break;
        }
    }
    return i;
}

mathElement getMathElement(const std::string &inStr, unsigned int index, mathElementType prevType)
{
    mathElement element = {"", none_t, false, 0, 0, 0.0};

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
        index++;

        for (; index < inStr.size(); index++) {
            if (isalnum(inStr[index]) || inStr[index] == '_') {
                element.str.push_back(inStr[index]);
                element.i_end = index;
            }
            else
                break;
        }

        if (is_math_function(element.str)) {
            element.type_t = function_t;
        }
        else {
            element.type_t = variable_t;
            add_in_var_list(element.str);
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
        if (element.error == false) {
            element.childList = parse_math_expression(element.str, element.error);
        }
    }
    else if (is_begin_number(inStr[index]) ||
             ((inStr[index] == '+' || inStr[index] == '-') &&
              (prevType == none_t || prevType == operator_t || prevType == function_t) &&
              (index + 1 < inStr.size() && is_begin_number(inStr[index + 1])))) {

        element.type_t = number_t;
        element.str.push_back(inStr[index]);
        element.i_start = index;
        element.i_end = index;
        index++;

        for (; index < inStr.size(); index++) {
            if (is_begin_number(inStr[index])) {
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
        else if (element.str.compare("+.") == 0)
            element.error = true;
        else if (element.str.compare("-.") == 0)
            element.error = true;

        if (element.error == false) {
            element.number = atof(element.str.c_str());
        }
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
    else if (str.compare("tan") == 0) {
        status = true;
    }
    else if (str.compare("lg") == 0) {
        status = true;
    }
    else if (str.compare("ln") == 0) {
        status = true;
    }

    return status;
}

bool is_operator(const int ch)
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
        return true;
    }
    return false;
}

std::list<mathElement> parse_math_expression(const std::string &inStr, bool &error)
{

    mathElement t;
    std::list<mathElement> mathList;
    error = false;
    mathElementType prevType = none_t;

    for (unsigned int i = 0; i < inStr.size(); i++) {

        t = getMathElement(inStr, i, prevType);

        prevType = t.type_t;

        if (t.error) {
            error = true;
            break;
        }
        if (t.type_t != none_t) {
            i = t.i_end;
            if (t.type_t == brackets_t)
                i++;
            mathList.push_back(t);
        }
        else {
            mathList.push_back(t);
            break;
        }
    }
    return mathList;
}

void add_in_var_list(const std::string varStr)
{
    varElementType t;

    t.str = varStr;
    t.defined = false;
    t.number = 0;

    if (varList.empty()) {
        varList.push_back(t);
    }
    else {
        bool found = false;
        for (std::list<varElementType>::const_iterator it = varList.begin(); it != varList.end(); it++) {
            if (varStr.compare(it->str) == 0) {
                found = true;
                break;
            }
        }
        if (found == false) {
            varList.push_back(t);
        }
    }
}

std::list<varElementType> get_var_list(void)
{
    return varList;
}

bool set_var_element(const std::string &varStr, const double &number)
{
    bool status = false;
    for (std::list<varElementType>::iterator it = varList.begin(); it != varList.end(); it++) {
        if (varStr.compare(it->str) == 0) {
            status = true;
            it->defined = true;
            it->number = number;
            break;
        }
    }
    return status;
}

std::list<mathElement> calculationMath(std::list<mathElement> &mathList)
{
    std::list<mathElement>::iterator nextElement;
    std::list<mathElement>::iterator prevElement;
    std::list<mathElement>::iterator nowElement;

    bool found = false;

    for (std::list<mathElement>::iterator it = mathList.begin(); it != mathList.end(); it++) {
        if (it->type_t == variable_t) {
            for (std::list<varElementType>::iterator it2 = varList.begin(); it2 != varList.end(); it2++) {
                if (it->str.compare(it2->str) == 0) {
                    it->number = it2->number;
                    it->type_t = number_t;
                    it->i_start = 0;
                    it->i_end = 0;
                    it->str.erase();
                    it->error = false;

                    return mathList;
                }
            }
        }
    }

    for (std::list<mathElement>::iterator it = mathList.begin(); it != mathList.end(); it++) {
        if (it->type_t == brackets_t) {

            while (it->childList.size() > 1 ||
                   (it->childList.size() == 1 &&
                    (it->childList.begin()->type_t == variable_t ||
                     it->childList.begin()->type_t == brackets_t))) {

                it->childList = calculationMath(it->childList);
            }

            it->number = it->childList.begin()->number;
            it->type_t = number_t;
            it->i_start = 0;
            it->i_end = 0;
            it->str.erase();
            it->error = false;
            it->childList.erase(it->childList.begin());

            return mathList;
        }
    }

    for (std::list<mathElement>::iterator it = mathList.begin(); it != mathList.end(); it++) {
        if (it->type_t == function_t) {
            nextElement = std::next(it);

            double d;
            d = calc_function(it->str, nextElement->number);

            it->number = d;
            it->type_t = number_t;
            it->i_start = 0;
            it->i_end = 0;
            it->str.erase();
            it->error = false;

            mathList.erase(nextElement);
            return mathList;
        }
    }

    for (std::list<mathElement>::iterator it = mathList.begin(); it != mathList.end(); it++) {
        if (it->type_t == operator_t) {
            if (it->str.compare("^") == 0) {
                nowElement = it;
                found = true;
                break;
            }
        }
    }

    if (found == false) {
        for (std::list<mathElement>::iterator it = mathList.begin(); it != mathList.end(); it++) {
            if (it->type_t == operator_t) {
                if (it->str.compare("*") == 0 || it->str.compare("/") == 0) {
                    nowElement = it;
                    found = true;
                    break;
                }
            }
        }
    }

    if (found == false) {
        for (std::list<mathElement>::iterator it = mathList.begin(); it != mathList.end(); it++) {
            if (it->type_t == operator_t) {
                if (it->str.compare("+") == 0 || it->str.compare("-") == 0) {
                    nowElement = it;
                    break;
                }
            }
        }
    }

    prevElement = std::prev(nowElement);
    nextElement = std::next(nowElement);

    double d;
    double a = prevElement->number;
    double b = nextElement->number;

    if (nowElement->str.compare("*") == 0) {
        d = a * b;
    }
    else if (nowElement->str.compare("/") == 0) {
        d = a / b;
    }
    else if (nowElement->str.compare("+") == 0) {
        d = a + b;
    }
    else if (nowElement->str.compare("-") == 0) {
        d = a - b;
    }
    else if (nowElement->str.compare("^") == 0) {
        d = pow(a, b);
    }

    nowElement->number = d;
    nowElement->type_t = number_t;
    nowElement->i_start = 0;
    nowElement->i_end = 0;
    nowElement->str.erase();
    nowElement->error = false;

    mathList.erase(nextElement);
    mathList.erase(prevElement);

    return mathList;
}

double calc_function(const std::string &funcStr, const double &number)
{
    double d;

    if (funcStr.compare("sin") == 0) {
        d = sin(number);
    }
    else if (funcStr.compare("cos") == 0) {
        d = cos(number);
    }
    else if (funcStr.compare("tan") == 0) {
        d = tan(number);
    }
    else if (funcStr.compare("lg") == 0) {
        d = log10(number);
    }
    else if (funcStr.compare("ln") == 0) {
        d = log(number);
    }

    return d;
}

bool is_begin_number(const int ch)
{
    if (isdigit(ch) || ch == '.' || ch == ',') {
        return true;
    }
    return false;
}
