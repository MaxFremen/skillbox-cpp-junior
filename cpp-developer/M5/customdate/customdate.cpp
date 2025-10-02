/*
* @file customdate.cpp
* @brief Класс для базовых операций с датами на основе Григорианского календаря
* */

#include "customdate.h"

// ==================== Date ====================

// Константы

// Количество дней в обычном году
const int Date::monthDays_[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Приватные методы

/* 
* @brief Проверяет, является ли год високосным
* */
bool Date::is_leapYear(int y) {
    return (y % 4 == 0) && ((y % 100 != 0) || (y % 400 == 0));
}

/*
* @brief Проверяет, является ли месяц Февралём в високосном году
* */
bool Date::is_leapMonth(int y, int m) {
    return (m == 2) && is_leapYear(y);
}

/* 
* @brief Вычисляет количество дней в месяце в зависимости от года
* @returns Количество дней в месяце
* */
int Date::daysInMonth(int y, int m) {
    return monthDays_[m - 1] + (is_leapMonth(y, m) ? 1 : 0);
}

/*
* @brief Проверяет, является ли дата корректной
* */
bool Date::is_validDate(int y, int m, int d) {
    if (y < 1 || m < 1 || m > 12 || d < 1 || d > 31) {
        return false;
    }
    if (d > daysInMonth(y, m)) { return false; }
    return true;
}

/* 
* @brief Вычисляет количество дней с опорной даты
* @attention Опорная дата может быть только с 01.01 любого года
* @todo Отправить целиком в класс dateinterval. Тут он не нужен(??)
* */
long int Date::daysSinceEpoch_(int y, int m, int d) {
    /*
    * @brief Опорная дата для вычислений
    * @attention Месяц и день опорной даты должны быть 1 (01.01)
    * @todo Добавить возможность использования любой опорной даты
    * */
    struct epoch {
        int year = 1;
        int month = 1;
        int day = 1;
    };

    long int days = d;
    for (int year = epoch().year; year < y; ++year) {
        days += is_leapYear(year) ? 366 : 365;
    }
    for (int month = epoch().month; month < m; ++month) {
        days += daysInMonth(y, month);
    }
    return days;
}

/*
* @brief День недели по алгоритму Целлера
* @returns День недели (0 = Суббота, 1 = Воскресенье, ...)
* @todo: Сделать возможность смещать 0 на любой день недели
* */
int Date::weekdayZeller(int y, int m, int d) {
    if (m == 1 || m == 2) {
        m += 12;
        y--;
    }
    int k = y % 100;
    int j = y / 100;
    // День недели (0 = Суббота)
    int h = (d + (13 * (m + 1)) / 5 + k + (k / 4) + (j / 4) + 5 * j) % 7;
    return h;
}

// Конструкторы

/*
* @brief Дефолтный конструктор
* @note Поскольку дата без параметров не имеет смысла, бросаем исключение
* @throws std::invalid_argument - Дата не инициализирована
* @todo: Проработать взаимодействие с cin: пока может менять дату.
* */ 
Date::Date() {
    throw std::invalid_argument("Date not initialized");
}

/*
* @brief Конструктор даты с параметрами 
* @param year - Год
* @param month - Месяц
* @param day - День
* @throws std::invalid_argument - Некорректная дата
* */
Date::Date(int year, int month, int day) {
    // Проверка правильности даты
    if (!is_validDate(year, month, day)) {
        throw std::invalid_argument("Invalid date");
    }
    // Год
    year_ = year;
    // Месяц
    month_ = month;
    // День
    day_ = day;
}

// Публичные методы

// Геттер года
int Date::year() const { return year_; }
// Геттер месяца
int Date::month() const { return month_; }
// Геттер дня
int Date::day() const { return day_; }
// Геттер дня недели
int Date::weekday() const { return weekdayZeller(year_, month_, day_); }
// Геттер количества дней с опорной даты
long int Date::daysSinceEpoch() const { return daysSinceEpoch_(year_, month_, day_); }

/*
* @brief Печатает дату в фрмате ISO 8060 (YYYY-MM-DDD)
* @note Используются ведущие нули для заполнения
* */
std::ostream &operator<<(std::ostream &os, const Date &dt) {
    // stringstream используется для форматирования только ЭТОЙ строки
    std::ostringstream tmp;
    tmp << std::setw(4) << std::setfill('0') << dt.year_ << "-"
        << std::setw(2) << std::setfill('0') << dt.month_ << "-"
        << std::setw(2) << std::setfill('0') << dt.day_;
    os << tmp.str();
    return os;
}

/*
* @brief Метод для удобства
* @note Используются ведущие нули для заполнения
* @todo Расширить функционал для выбора формата вывода. Использовать локаль?
* */
void Date::print() const {
    std::cout << *this << "\n";
}

/*
* @brief Создает новую дату из потока stdin в формате ISO 8060
* */
Date Date::parseFromStream(std::istream &is) {
    // Временные компоненты даты
    int y{0}, m{0}, d{0};
    // Поглотители разделителя даты
    char sep1, sep2;
    is >> y >> sep1 >> m >> sep2 >> d;
    return Date(y, m, d);
}

/*
* @brief Получает дату из потока stdin в формате ISO 8060
* @warning Изменяет объект даты, в который происходит парсинг
* @todo Исключить возможность изменения. Все даты должны быть неизменяемые.
* @warning Ничего не бросает если ввод ошибочный
* */
std::istream &operator>>(std::istream &is, Date &dt) {
    // Временные компоненты даты
    int y{0}, m{0}, d{0};
    // Поглотители разделителя даты
    char sep1, sep2;
    std::cin >> y >> sep1 >> m >> sep2 >> d;
    if (!dt.is_validDate(y, m, d)) {
        is.setstate(std::ios::failbit);
    } else {
        dt.year_ = y;
        dt.month_ = m;
        dt.day_ = d;
    }
    return is;
}

/*
* @brief Перегрузка оператора равентва
* @note Сравнение двух дат по частям - год, месяц, день
* */
bool Date::operator==(const Date &other) const {
    return (year_ == other.year_) && (month_ == other.month_) && (day_ == other.day_);
}

// @brief Перегрузка оператора неравенства
bool Date::operator!=(const Date &other) const {
    return !(*this == other);  // Буквально - НЕ равно
}

/*
* @brief Перегрузка оператора меньше
* @note Сравнение от большей части к меньшей - год, месяц, день
* */
bool Date::operator<(const Date &other) const {
    if (year_ != other.year_) { return year_ < other.year_; }
    if (month_ != other.month_) { return month_ < other.month_; }
    return day_ < other.day_;
}

// Перегрузка оператора больше
bool Date::operator>(const Date &other) const {
    return other < *this;  // Просто поменяли стороны сравнения
}

// Перегрузка оператора меньше или равно
bool Date::operator<=(const Date &other) const {
    return !(*this > other);  // Не больше, значит меньше или равна
}

// Перегрузка оператора больше или равно
bool Date::operator>=(const Date &other) const {
    return !(*this < other);  // Не меньше, значит больше или равна
}

// @todo Реализовать инкремент и декремент даты (операторы ++ и --)

// @todo Релизовать математические операции с датами? лучше в классе Duration?

// ==================== DateInterval ====================

/*
* @brief Конструктор по умолчанию для Длительности
* @note Поскольку длительность имеет ограниченный смысл без привязки к дате,
*       то по умолчанию она равна нулю (0 дней)
* */
DateInterval::DateInterval() {
    days_ = 0;
}

/*
* @brief Конструктор с параметром количества дней
* @param days - Количество дней
* */
DateInterval::DateInterval(long int days) {
    days_ = days;
}

/* @brief Конструктор с параметрами двух дат
* @param start - Начальная дата
* @param end - Конечная дата
* @note Вычисляет количество дней между двумя датами
* */
DateInterval::DateInterval(const Date &start, const Date &end) {
    long int startDays = start.daysSinceEpoch();
    long int endDays = end.daysSinceEpoch();
    days_ = endDays - startDays;
}

// Публичные методы

// Геттер Количество дней
long int DateInterval::days() const { return days_; }
// Геттер Количество недель
int DateInterval::weeks() const { return days_ / 7;}