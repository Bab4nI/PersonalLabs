#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int day_;
    int month_;
    int year_;

    bool isLeapYear(int year) const;             // Проверка, является ли год високосным
    int daysInMonth(int month, int year) const;  // Количество дней в месяце

public:
    Date();                                      // Конструктор по умолчанию
    Date(int day, int month, int year);          // Конструктор с параметрами

    void input();                                // Метод для ввода даты с проверкой
    void print() const;                          // Метод для вывода даты
    std::string dayOfWeek() const;               // Метод для определения дня недели

    // Прибавление целого количества дней к дате
    Date& operator+=(int days);
};

#endif // DATE_H
