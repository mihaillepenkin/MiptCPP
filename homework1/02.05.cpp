#include<print>
#include<cmath>

const double epsilon = 10e-6;

int main() {
    double e = 0;
    double pi = 0;

    std::size_t n = 0;

    double term_of_macloren = 1;
    double term_of_leibniz = 1;

    do {
        e += term_of_macloren;
        pi += term_of_leibniz;
        ++n;
        term_of_macloren = term_of_macloren / (n + 1);
        term_of_leibniz = std::pow(-1, n) / (2 * n + 1);
    } while (std::abs(term_of_macloren - 0) >= epsilon || std::abs(term_of_leibniz - 0) >= epsilon);

    e += 1;
    pi *= 4;

    std::print("e = {}, pi = {}\n", e, pi);
}