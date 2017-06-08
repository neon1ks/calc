#ifndef CALC_LIBS_H
#define CALC_LIBS_H

#include <list>
#include <string>

enum mathElementType {
    none_t,
    variable_t,
    operator_t,
    brackets_t,
    math_t,
    number_t
};

struct mathElement {
    std::string str;
    mathElementType type_t;
    bool error;
    unsigned int i_start;
    unsigned int i_end;
};

// Проверка скобок
bool check_brackets(const std::string &str);

// Проверка символов в формуле, возвращает размер строки при успешной проверке,
// или индекс неправильного символа
unsigned int check_symbols(const std::string &str);

// Возврашает элемент математического выражения из строки
mathElement getStrElement(const std::string &inStr, unsigned int i);

// является ли строка именем функции
bool is_math_function(const std::string &str);

// является ли символ математическим оператором
bool is_operator(const char &ch);

#endif // CALC_LIBS_H
