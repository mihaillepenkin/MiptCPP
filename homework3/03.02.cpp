#include<iostream>
#include<print>
#include<numbers>
#include<cmath>
#include <cassert>

class Circle {
private:
    double radius;
public:
    Circle(double radius) : radius(radius) {}

    double perimeter() const {
        return 2 * radius * std::numbers::pi;
    }

    double area() const {
        return std::numbers::pi * radius * radius;
    }
};


class Triangle {
private:
    double a;
    double b;
    double c;
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

    double perimeter() const {
        return a + b + c;
    }

    double area() const {
        return std::sqrt((a + b + c) / 2  * (b + c - a) / 2 * (a + c - b) / 2 * (a + b - c) / 2);
    }
};

class Square {
private:
    double a;
public:
    Square(double a) : a(a) {}

    double perimeter() const {
        return 4 * a;
    }

    double area() const {
        return a * a;
    }
};

int main() {
    const double epsilon = 10e-6;
    Square square = Square(5);
    Circle circle = Circle(4);
    Triangle triangle = Triangle(3, 4, 5);

    assert(std::abs(square.area() - 25) < epsilon);
    assert(std::abs(square.perimeter() - 20) < epsilon);

    assert(std::abs(circle.area() - 50.265482) < epsilon);
    assert(std::abs(circle.perimeter() - 25.132741) < epsilon);

    assert(std::abs(triangle.area() - 6) < epsilon);
    assert(std::abs(triangle.perimeter() - 12) < epsilon);

    std::print("always ok\n");
}