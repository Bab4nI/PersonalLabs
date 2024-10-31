#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <cmath>

const double M_PI = 3.14159265358979323846;

class Point {
public:
    Point();
    double x, y;
};

class Shape {
protected:
    Point* arc = nullptr;
    int n = 0;
public:
    Shape(int numPoints);
    int getNumberOfPoints() const;
    Point* getArrOfPoints() const;
    virtual double area() const = 0;
    virtual Point center() const = 0;
    virtual Shape* rotate(double angle) const = 0;
    virtual Shape* move(double dx, double dy) const = 0;
    void input();
    virtual ~Shape();
};

class Triangle : public Shape {
public:
    Triangle();
    double area() const override;
    Shape* rotate(double angle) const override;
    Shape* move(double dx, double dy) const override;
    Point center() const override;
};

class Square : public Shape {
public:
    Square();
    double area() const override;
    Shape* rotate(double angle) const override;
    Shape* move(double dx, double dy) const override;
    Point center() const override;
};

class FactoryShape {
public:
    static Shape* createShape(char type);
};

class Operations {
private:
    static int left(Point& cur, Point& frst, Point& scnd);
    static bool segmentIntersection(Point& frstA, Point& frstB, Point& scndA, Point& scndB);
    static bool onSegment(Point& cur, Point& frst, Point& scnd);
public:
    static bool isIntersect(Shape* first, Shape* second);
    static int Compare(const Shape* shape1, const Shape* shape2);
    static int isInclude(const Shape* shape1, const Shape* shape2);
};

class Interface {
public: 
    static void runInterface();
protected:
    static void displayCoordinates(const Shape* shape, const std::string& shapeName); 
};

#endif // SHAPE_HPP
