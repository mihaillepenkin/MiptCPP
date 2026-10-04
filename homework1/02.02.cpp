#include<iostream>
#include<cmath>
#include<print>


int main() {
    const double epsilon = 10e-6;
    double a = 0;
    double b = 0;
    double c = 0;
    std::cin >> a >> b >> c;

    if (std::abs(a - 0) < epsilon) {
        if (std::abs(b - 0) < epsilon && std::abs(c - 0) < epsilon) {
            std::print("Infinity solution\n");
        } else if (std::abs(b - 0) < epsilon && std::abs(c - 0) >= epsilon) {
            std::print("No solution\n");
        } else {
            std::print("One solution - {}\n", c / b);
        }
    } else {
        double discriminant = b * b - 4 * a * c;
        if (std::abs(discriminant - 0) < epsilon) {
            std::print("One solution - {}\n", -b / (2 * a));
        } else {
             if (discriminant < 0) {
                std::print("No one solution in rational numbers\n");
            } else {
                double x1 = (-b + std::sqrt(discriminant)) / (2 * a);
                double x2 = (-b - std::sqrt(discriminant)) / (2 * a);
                std::print("First solution - {}, Second solution - {}\n", x1, x2);
            }
        }
    }
    
}