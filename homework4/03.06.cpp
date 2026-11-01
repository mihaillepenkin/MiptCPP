#include<vector>
#include<numbers>
#include<cmath>
#include <cassert>

class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;

    virtual double perimeter() const = 0;
};

class Polygon : public Shape {};

class Circle final : public Shape {
public:
    Circle(int input_radius) : radius(input_radius) {}

    double area() const override {
        return std::numbers::pi * radius * radius;
    }

    double perimeter() const override {
        return std::numbers::pi * 2 * radius;
    }

private:
    int radius = 0;
};

class Triangle final : public Polygon {
public:
    Triangle(double input_a, double input_b, double input_c) : a(input_a), b(input_b), c(input_c) {}

    double area() const override {
        return std::sqrt((a + b + c) / 2  * (b + c - a) / 2 * (a + c - b) / 2 * (a + b - c) / 2);
    }

    double perimeter() const override {
        return a + b + c;
    }

private:
    double a = 0;
    double b = 0;
    double c = 0;
};

class Rectangle : public Polygon {
public:
    Rectangle(double input_a, double input_b) : a(input_a), b(input_b) {}

    double area() const override {
        return a * b;
    }

    double perimeter() const override {
        return (a + b) * 2;
    }

private:
    double a = 0;
    double b = 0;
};

class Square final : public Rectangle {
public:    
    Square(double a) : Rectangle(a, a) {}
};

bool approx_equal(double a, double b, double epsilon = 1e-6) {
    return std::abs(a - b) < epsilon;
}

int main() {
    Circle c(10);
    assert(approx_equal(c.area(), 100.0 * std::numbers::pi));
    assert(approx_equal(c.perimeter(), 20.0 * std::numbers::pi));

    Triangle t(3.0, 4.0, 5.0);
    assert(approx_equal(t.area(), 6.0));
    assert(approx_equal(t.perimeter(), 12.0));

    Rectangle r(4.0, 5.0);
    assert(approx_equal(r.area(), 20.0));
    assert(approx_equal(r.perimeter(), 18.0));

    Square s(5.0);
    assert(approx_equal(s.area(), 25.0));
    assert(approx_equal(s.perimeter(), 20.0));
}