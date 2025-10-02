#ifndef CUSTOMDATE_H
#define CUSTOMDATE_H

#include <iostream>
#include <iomanip>

// ==================== Date ====================

/*
* @brief Даты на основе Григорианского календаря
* */
class Date {
    private:

        // Год
        int year_{1970};
        // Месяц
        int month_{1};
        // День
        int day_{1};

        // Количество дней в обычном году
        static const int monthDays_[12];

        /* 
        * @brief Проверяет, является ли год високосным
        * */
        static bool is_leapYear(int y);

        /*
        * @brief Проверяет, является ли месяц Февралём в високосном году
        * */
        static bool is_leapMonth(int y, int m);

        /* 
        * @brief Вычисляет количество дней в месяце в зависимости от года
        * @returns Количество дней в месяце
        * */
        static int daysInMonth(int y, int m); 

        /*
        * @brief Проверяет, является ли дата корректной
        * */
        static bool is_validDate(int y, int m, int d);

        /* 
        * @brief Вычисляет количество дней с опорной даты
        * @attention Опорная дата может быть только с 01.01 любого года
        * @todo Отправить целиком в класс dateinterval. Тут он не нужен.
        * */
        static long int daysSinceEpoch_(int y, int m, int d);

        /*
        * @brief День недели по алгоритму Целлера
        * @returns День недели (0 = Суббота, 1 = Воскресенье, ...)
        * */
        static int weekdayZeller(int y, int m, int d);

    public:

        // Дефолтный конструктор
        Date();

        // Конструктор даты с параметрами 
        explicit Date(int year, int month, int day);        

        // Геттер года
        int year() const;
        // Геттер месяца
        int month() const;
        // Геттер дня
        int day() const;
       // Геттер дня недели
        int weekday() const;
        // Геттер количества дней с опорной даты
        long int daysSinceEpoch() const;

        /*
        * @brief Печатает дату в фрмате ISO 8060 (YYYY-MM-DDD)
        * @note Используются ведущие нули для заполнения
        * */
        friend std::ostream &operator<<(std::ostream &os, const Date &dt);

        /*
        * @brief Метод для удобства печати даты
        * @note Используются ведущие нули для заполнения
        * @todo Расширить функционал для выбора формата вывода. Использовать локаль?
        * */
        void print() const;

        /*
        * @brief Создает объект класса из потока stdin в формате ISO 8060
        * */
        static Date parseFromStream(std::istream &is);

        /*
        * @brief Получает дату из потока stdin в формате ISO 8060
        * */
        friend std::istream &operator>>(std::istream &is, Date &dt);

        /*
        * @brief Перегрузка оператора равентва
        * @note Сравнение двух дат по частям - год, месяц, день
        * */
        bool operator==(const Date &other) const;

        // Перегрузка оператора неравенства
        bool operator!=(const Date &other) const;

        /*
        * @brief Перегрузка оператора меньше
        * @note Сравнение от большей части к меньшей - год, месяц, день
        * */
        bool operator<(const Date &other) const;

        // Перегрузка оператора больше
        bool operator>(const Date &other) const;

        // Перегрузка оператора меньше или равно
        bool operator<=(const Date &other) const;

        // Перегрузка оператора больше или равно
        bool operator>=(const Date &other) const;

        // @todo Реализовать инкремент и декремент даты (операторы ++ и --)

        // @todo Релизовать математические операции с датами? лучше в классе Duration?
};

// ==================== DateInterval ====================

/*
* @brief Интервалы между датами (продолжительность) в днях
* */
class DateInterval {
    private:
        // Количество дней
        long int days_{0};

    public:
        // Дефолтный конструктор
        DateInterval();

        // Конструктор с параметром количества дней
        explicit DateInterval(long int days);

        // Конструктор с параметрами двух дат
        DateInterval(const Date &start, const Date &end);

        // Геттеры
        long int days() const;
        int weeks() const;
};

#endif