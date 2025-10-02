/*
##### Задание 1. Полёт нормальный!

###### Что нужно сделать

Напишите программу для аэропорта, проверяющую, правильным ли эшелоном летит самолёт. 

###### Условие:

- скорость самолёта должна быть в диапазоне от 750 до 850 км/ч;
- высота — в диапазоне от 9 000 до 9 500 метров.
*/

#include <iostream>
#include <limits>
#include "custominput.h"

// Ограничения по скорости
const int speed_limit[2] = {750, 850};
// Ограничения по высоте
const int altitude_limit[2] = {9000, 9500};

int m5Task1 () {
    std::cout << "Помощник авиадиспетчера\n";
    std::cout << "-----------------------\n";
    // Скорость, получается от пользователя
    int speed = validated_integral_input<int>("Введите вашу скорость: ", 0);
    // Высота, получается от пользователя
    int altitude = validated_integral_input<int>("Введите вашу высоту: ", 0);
    std::cout << "-----------------------\n";
    std::cout << "[Диспетчер] Борт \"Картошка\", ";
    if (((speed >= speed_limit[0]) && (speed <= speed_limit[1])) && 
        ((altitude >= altitude_limit[0]) && (altitude <= altitude_limit[1]))){
        std::cout << "полет нормальный!";
    } else {
        std::cout << "нарушаем!";
    }
    return 0;
}

int main () {
    return m5Task1();
}