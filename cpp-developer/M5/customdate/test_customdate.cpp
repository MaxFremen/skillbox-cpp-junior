#include <iostream>
#include "customdate.h"

/*
* @brief Показательное использование класса Date и его функций
* @todo Собрать тесты в отдельный файл?
* */
int testCustomDate() {
    Date my_date = Date(2025, 9, 23);

    // Инициализация без параметров запрещена
    std::cout << "Проверка инициализации без параметров: \n";
    try {
        Date my_uninitialized_date = Date();
    }
    catch (const std::invalid_argument &e) {
        std::cerr << e.what() << '\n';
    }

    // Исклчение для некорректной даты
    std::cout << "Проверка инициализации неправильной даты: \n";
    try {
        Date invalid_date_test(2025, 2, 29);
    }
    catch (const std::invalid_argument &e) {
        std::cerr << e.what() << '\n';
    }

    // Геттеры
    std::cout << "Геттеры: \n";
    std::cout << "Год: " << my_date.year() << "\n";
    std::cout << "Месяц: " << my_date.month() << "\n";
    std::cout << "День: " << my_date.day() << "\n";
    std::cout << "День недели (0=Суббота): " << my_date.weekday() << "\n";

    // Печатает 2025-09-23
    std::cout << "Печатает дату: \n";
    std::cout << my_date << "\n";

    // Печатает 2025-09-23
    std::cout << "Печатает дату методом print(): \n";
    my_date.print();

    // Получает дату от пользователя парсером
    std::cout << "Введите дату в формате YYYY-MM-DD: ";
    try {
        Date parsedDate = Date::parseFromStream(std::cin);
        std::cout << "Вы ввели дату: " << parsedDate << "\n";
    }
    catch (const std::invalid_argument &e) {
        std::cerr << e.what() << "\n";
    }

    // Получает дату от пользователя из потока (такое себе)
    std::cout << "Введите дату в формате YYYY-MM-DD: ";
    Date cinDate(1, 1, 1);  // Создается "пустая" дата - не хорошо
    try {
        std::cin >> cinDate;  // Неизменяемый объект - изменяется. Плохо.
    }
    catch (const std::invalid_argument &e) {
        std::cerr << e.what() << "\n";
    }
    std::cout << "Вы ввели дату: " << cinDate << "\n";

    // Сравнения
    Date smaller_date(2025, 9, 22);
    Date larger_date(2025, 9, 24);

    std::cout << "Неравенство дат: \n";
    std::cout << my_date << " != " << smaller_date << " : " << std::boolalpha << (my_date != smaller_date) << "\n";

    std::cout << "Равенство дат: \n";
    Date equal_date(2025, 9, 23);
    std::cout << my_date << " = " << equal_date << " : " << std::boolalpha << (my_date == equal_date) << "\n";

    std::cout << "Сравнение дат (меньше): \n";
    std::cout << smaller_date << " < " << my_date << " : " << std::boolalpha << (smaller_date < my_date) << "\n";
    
    std::cout << "Сравнение дат (больше): \n";
    std::cout << larger_date << " > " << my_date << " : " << std::boolalpha << (larger_date > my_date) << "\n";

    std::cout << "Сравнение дат (меньше или равно): \n";
    std::cout << smaller_date << " <= " << my_date << " : " << std::boolalpha << (smaller_date <= my_date) << "\n";

    std::cout << "Сравнение дат (больше или равно): \n";
    std::cout << larger_date << " >= " << my_date << " : " << std::boolalpha << (larger_date >= my_date) << "\n";
    return 0;
}

int testDateInterval() {
    Date start_date(2025, 9, 23);
    Date end_date(2025, 10, 23);

    DateInterval interval(start_date, end_date);
    std::cout << "Интервал между " << start_date << " и " << end_date << " составляет " 
              << interval.days() << " дней.\n";

    // Геттеры
    std::cout << "Геттеры: \n";
    std::cout << "Количество дней: " << interval.days() << "\n";
    std::cout << "Количество недель: " << interval.weeks() << "\n";

    return 0;
}

int main() {
    testCustomDate();
    testDateInterval();
    return 0;
}