/*Очень хотелось посмотреть, как работают модули совместно. Наверное, усложнил*/

#ifndef CUSTOMINPUT_H
#define CUSTOMINPUT_H

#include <iostream>
#include <limits>

/*
* @brief Получает ввод от пользователя: Целое число в диапазоне.
* @details Мучает пользователя до тех пор, пока ввод не удовлетворит
* требованиям
* @param prompt Приглашение с описанием вводимых данных
* @param lower Нижняя граница диапазона проверки ввода, defaults -inf
* @param upper Верхняя граница диапазона проверки ввода, defaults +inf
* @return Проверенный на соответствие ввод пользователя в ожидаемом типе
*/
template <typename Integral,
          typename std::enable_if<std::is_integral<Integral>::value, int>::type = 0>
Integral validated_integral_input(
    const char* prompt,
    const Integral &lower = std::numeric_limits<Integral>::min(),
    const Integral &upper = std::numeric_limits<Integral>::max()
) {
    Integral user_input;
    while(true){
        std::cout << prompt;
        std::cin >> user_input;
        if(std::cin.fail() || user_input < lower || user_input > upper){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод. Попробуйте еще раз.\n";
        } else {
            // Исключение ввода нескольких чисел в одной строке
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        };
    }
    return user_input;
}

#endif