#include "Number.hpp"
#include <stdexcept>
#include <bitset>
#include <iostream>

using namespace std;

Number::Number() : value_("0") {};
Number::Number(const string& value) : value_(value) {};

string Number::getValue() const{
    return value_;
}

NumberBit::NumberBit(const string& value) : Number(value){
    if (!isValid()) {
        throw invalid_argument("Некорректный ввод двоичного числа");
    }
}

bool NumberBit::isValid() const {
    if (value_.empty()) {
        return false;
    }
    
    if (value_[0] == '-') {
        for (size_t i = 1; i < value_.size(); ++i) {
            if (value_[i] != '0' && value_[i] != '1') {
                return false;
            }
        }
    } else {
        for (char c : value_) {
            if (c != '0' && c != '1') {
                return false; 
            }
        }
    }

    return true;
}

Number* NumberBit::add(const Number& other) const{
    int thisValue = stoi(value_, nullptr, 2);
    int otherValue = stoi(other.getValue(), nullptr, 2); //Конверсия в int
    int result = thisValue + otherValue;    

    string binaryResult = bitset<32>(result).to_string(); //В 2-ую СС
    binaryResult.erase(0, binaryResult.find_first_not_of('0')); //Удаление ведущих нулей

    return new NumberBit(binaryResult);
}

Number* NumberBit::subtract(const Number& other) const {
    int thisValue = stoi(value_, nullptr, 2);
    int otherValue = stoi(other.getValue(), nullptr, 2);
    int result = thisValue - otherValue;

    string binaryResult;
    if (result < 0) {
        binaryResult = "-" + bitset<32>(-result).to_string();
        binaryResult.erase(1, binaryResult.find_first_not_of('0', 1) - 1);
    } else {
        binaryResult = bitset<32>(result).to_string();
        binaryResult.erase(0, binaryResult.find_first_not_of('0'));
    }

    if (binaryResult.empty() || binaryResult == "-") {
        binaryResult = "0";
    }

    return new NumberBit(binaryResult);
}
NumberHex::NumberHex(const string& value) : Number(value){
    if (!isValid()) {
        throw invalid_argument("Некорректный ввод шестнадцатеричного числа");
    }
}

bool NumberHex::isValid() const {
    if (value_.empty()) {
        return false;
    }
    
    if (value_[0] == '-') {
        for (size_t i = 1; i < value_.size(); ++i) {
            if (!((value_[i] >= '0' && value_[i] <= '9') || 
                  (value_[i] >= 'A' && value_[i] <= 'F') || 
                  (value_[i] >= 'a' && value_[i] <= 'f'))) {
                return false;
            }
        }
    } else {
        for (char c : value_) {
            if (!((c >= '0' && c <= '9') || 
                  (c >= 'A' && c <= 'F') || 
                  (c >= 'a' && c <= 'f'))) {
                return false;
            }
        }
    }

    return true;
}

Number* NumberHex::add(const Number& other) const{
    int thisValue = stoi(value_, nullptr, 16);
    int otherValue = stoi(other.getValue(), nullptr, 16);
    int result = thisValue + otherValue;    

    char buffer[10];
    sprintf(buffer, "%X", result); 
    return new NumberHex(buffer);
}

Number* NumberHex::subtract(const Number& other) const {
    int thisValue = std::stoi(value_, nullptr, 16);
    int otherValue = std::stoi(other.getValue(), nullptr, 16);
    int result = thisValue - otherValue;

    char buffer[10];
    sprintf(buffer, "%X", std::abs(result));

    std::string hexResult(buffer);
    if (result < 0) {
        hexResult = "-" + hexResult;
    }

    return new NumberHex(hexResult);
}

void NumberInterface::start() {
    system("chcp 1251");
    bool cont = true, validInput;
    int choice;
    Number* first_ptr = nullptr; 
    Number* second_ptr = nullptr; 

    while(cont) {
        cout << "Нажмите \"1\", чтобы работать с двоичными числами, чтобы работать с шестнадцатиричными - \"2\"" << endl;
        cin >> choice;

        while(choice != 1 && choice != 2) {
            cout << "Некорректный символ выбора" << endl;
            cin >> choice;
        }

        if(choice == 1) {
            string firstVal, secondVal;
            
            validInput = false;
            while(!validInput){
                try {
                    cout << "Введите 2 двоичных числа: " << endl;
                    cin >> firstVal >> secondVal;
                    first_ptr = new NumberBit (firstVal);;
                    second_ptr = new NumberBit (secondVal);
                    validInput = true;
                } catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                    
                    delete first_ptr;
                    delete second_ptr;

                    first_ptr = nullptr;
                    second_ptr = nullptr;
                }
            }
        } else {
            string firstVal, secondVal;
            validInput = false;

            while(!validInput){      
                cout << "Введите два шестнадцатеричных числа: " << endl;
                cin >> firstVal >> secondVal;

                try {
                    first_ptr = new NumberHex (firstVal);
                    second_ptr = new NumberHex (secondVal);
                    validInput = true;
                } catch (const invalid_argument& e) {
                    cout << e.what() << endl;
                    
                    delete first_ptr;
                    delete second_ptr;

                    first_ptr = nullptr;
                    second_ptr = nullptr;
                }         
            }        
        }

        choice = 1;
        while(choice == 1) {
            cout << "Чтобы сложить числа, нажмите \"1\", чтобы вычесть - \"2\"" << endl;
            cin >> choice;

            while(choice != 1 && choice != 2) {
                cout << "Некорректный символ выбора" << endl;
                cin >> choice;
            }

            if(choice == 1) {
                Number* sum = first_ptr->add(*second_ptr);
                cout << "Сумма (в соответствующей СС) " << sum->getValue() << endl;
                delete sum; 
            } else {
                Number* sub = first_ptr->subtract(*second_ptr);
                cout << "Разность (в соответствующей СС) " << sub->getValue() << endl;
                delete sub;
            }

            cout << "Чтобы продолжить работу с этими числами, нажмие \"1\", чтобы ввести новые - \"2\", чтобы прекратить работу программы - \"3\"" << endl;
            cin >> choice;

            while(choice != 1 && choice != 2 && choice != 3) {
                cout << "Некорректный символ выбора" << endl;
                cin >> choice;
            }

            if(choice == 3){
                cont = false;

                delete first_ptr;
                delete second_ptr;

                first_ptr = nullptr;
                second_ptr = nullptr;
            }
                      
            else if(choice == 2) {
                delete first_ptr;
                delete second_ptr;

                first_ptr = nullptr;
                second_ptr = nullptr;
            }
        }
    }
}
