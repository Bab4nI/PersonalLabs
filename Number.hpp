#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <string>

using namespace std;

class Number{
public:
    Number();
    Number(const string& value);

    virtual Number* add(const Number& other) const = 0;
    virtual Number* subtract(const Number& other) const = 0;

    string getValue() const;
    virtual ~Number() = default;

protected:
    virtual bool isValid() const = 0;
    string value_;
};

class NumberBit : public Number{
    public:
        NumberBit(const string& value);

        Number* add(const Number& other) const override;
        Number* subtract(const Number& other) const override;

    protected:
        bool isValid() const override;
};

class NumberHex : public Number{
    public:
        NumberHex(const string& value);

        Number* add(const Number& other) const override;
        Number* subtract(const Number& other) const override;

    protected:
        bool isValid() const override;
};

class NumberInterface {
    public:
        void start();
};

#endif