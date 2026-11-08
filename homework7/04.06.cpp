#include<cmath>
#include <type_traits>
#include <cassert>


consteval double abs(double number) {
    if (number < 0) {
        return -1 * number;
    }
    return number;
}

consteval double powForMinusOne(int degree) {
    if (degree % 2 == 0) {
        return 1.0;
    }
    return -1.0;
}

consteval double calculatePi(double epsilon) {
    double pi = 0;
    double term_of_leibniz = 1;
    int n = 0;
    do {
        pi += term_of_leibniz;
        ++n;
        term_of_leibniz = powForMinusOne(n) / (2 * n + 1);
    } while (abs(term_of_leibniz) >= epsilon);
    return pi * 4;
}

consteval double calculateE(double epsilon) {
    double e = 1;
    double term_of_macloren = 1;
    int n = 0;
    do {
        e += term_of_macloren;
        ++n;
        term_of_macloren = term_of_macloren / (n + 1);
    } while (abs(term_of_macloren) >= epsilon);
    return e;
}


int main() {
    constexpr double epsilon = 10e-6;
    
    static_assert(abs(calculatePi(epsilon) - 3.141572653) < epsilon );
    static_assert( abs(calculateE(epsilon) - 2.71828182) < epsilon );
    
}