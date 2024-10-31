#include "Date.hpp"
#include <iostream>
#include <stdexcept> 
#include <string>
#include <iomanip>

using namespace std;

// Конструктор по умолчанию
Date::Date() : day_(1), month_(1), year_(2000) {}

// Конструктор с параметрами
Date::Date(int day, int month, int year) : day_(1), month_(1), year_(2000) {
    if (year < 2000) {
        throw invalid_argument("Year must be 2000 or greater!");
    }
    if (month < 1 || month > 12) {
        throw invalid_argument("Invalid month!");
    }
    if (day < 1 || day > daysInMonth(month, year)) {
        throw invalid_argument("Invalid day!");
    }
    
    day_ = day;
    month_ = month;
    year_ = year;
}

// Ввод даты с проверкой
void Date::input() {
    try {
        cout << "Enter year (>= 2000): ";
        cin >> year_;
        if (year_ < 2000) throw invalid_argument("Year must be 2000 or greater!");
        
        cout << "Enter month (1-12): ";
        cin >> month_;
        if (month_ < 1 || month_ > 12) throw invalid_argument("Invalid month!");
        
        cout << "Enter day: ";
        cin >> day_;
        if (day_ < 1 || day_ > daysInMonth(month_, year_)) throw invalid_argument("Invalid day!");
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

// Вывод даты
void Date::print() const {
    cout << setw(2) << setfill('0') << day_ 
    << "." << setw(2) << setfill('0') << month_ 
    << "." << setw(2) << setfill('0') << year_ << endl;
}

// Проверка, является ли год високосным
bool Date::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Определение количества дней в месяце
int Date::daysInMonth(int month, int year) const {
    switch (month) {
        case 2: return isLeapYear(year) ? 29 : 28; //Февраль високосного года
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
    }
}

Date& Date::operator+=(int days) {
    while (days > 0) {
        int DaysLimit = daysInMonth(month_, year_);

        day_++; // Увеличиваем день

        if (day_ > DaysLimit) {
            day_ = 1; 
            month_++;

            if (month_ > 12) {
                month_ = 1;
                year_++;
            }
        }

        days--;
    }

    return *this;
}

// Определение дня недели по дате (формула Зеллера)
string Date::dayOfWeek() const {
    int y = year_;
    int m = month_;
    int d = day_;
    
    if (m < 3) {
        m += 12;
        y--;
    }
    
    int k = y % 100;
    int j = y / 100;
    int h = (d + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;

    string daysOfWeek[] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
    return daysOfWeek[h];
}