#include <iostream>
#include <cmath>
#include <print>

int main() {
    int index_of_fibonacci = 0;

    std::cin >> index_of_fibonacci;

    const int five = 5;
    const double sqrt_of_fife = std::sqrt(five);

    const double numerator = std::pow(1 + sqrt_of_fife, index_of_fibonacci) - std::pow(1 - sqrt_of_fife, index_of_fibonacci);
    const double denominator = std::pow(2, index_of_fibonacci) * sqrt_of_fife;
    
    const double number_of_fibonacci_in_double = std::round(numerator / denominator);
    const int number_of_fibonacci = static_cast < int > (number_of_fibonacci_in_double);

    std::print("{}\n", number_of_fibonacci);
}