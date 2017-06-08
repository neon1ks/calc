#ifndef CALC_LIBS_H
#define CALC_LIBS_H

#include <cstdlib>
#include <list>
#include <string>

struct varElementType {
    std::string str;
    bool defined;
    double number;
};

enum mathElementType {
    none_t,
    variable_t,
    operator_t,
    brackets_t,
    function_t,
    number_t
};

struct mathElement {
    std::string str;
    mathElementType type_t;
    bool error;
    unsigned int i_start;
    unsigned int i_end;
    double number;
    std::list<mathElement> childList;
};

// Проверка скобок
bool check_brackets(const std::string &str);

// Проверка символов в формуле, возвращает размер строки при успешной проверке,
// или индекс неправильного символа
unsigned int check_symbols(const std::string &str);

// Возврашает элемент математического выражения из строки
mathElement getMathElement(const std::string &inStr, unsigned int i);

// является ли строка именем функции
bool is_math_function(const std::string &str);

// является ли символ математическим оператором
bool is_operator(const int ch);

std::list<mathElement> parse_math_expression(const std::string &inStr, bool &error);

std::list<varElementType> get_var_list(void);

bool set_var_element(const std::string &varStr, const double &number);

std::list<mathElement> calculationMath(std::list<mathElement> &mathList);

#endif // CALC_LIBS_H
