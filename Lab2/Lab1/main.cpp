#include <iostream>
#include "Date.hpp"

using namespace std;

int main() {
    Date date;

    cout << "Enter a date:\n";
    date.input();

    cout << "You entered: ";
    date.print();

    cout << "Day of the week: " << date.dayOfWeek() << endl;

    int daysToAdd;
    cout << "Enter number of days to add: ";
    cin >> daysToAdd;
    
    date += daysToAdd;

    cout << "New date is: " << endl;
    date.print();
    cout << "And new day of the week is: " << endl;
    cout << date.dayOfWeek() << endl;

    return 0;
}
