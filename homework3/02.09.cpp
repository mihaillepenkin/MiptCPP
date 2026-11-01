#include<cmath>
#include<iostream>
#include<print>
#include<numeric>

int gcd_recursive(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd_recursive(b, a % b);
}

int lcm_recursive(int a, int b) {
    return (a * b) / gcd_recursive(a, b);
}

int gcd_iterative(int a, int b) {
    while (b != 0) {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int lcm_iterative(int a, int b) {
    return (a * b) / gcd_iterative(a, b);
}

int main() {
    int first = 0, second = 0;
    std::cin >> first >> second;

    int a = std::max(first, second);
    int b = std::min(first, second);

    std::print("gcd with recursi - {}, gcd with iterative - {}, std::gcd - {}\n", gcd_recursive(a, b), gcd_iterative(a, b), std::gcd(a, b));

    std::print("lcm with recursi - {}, lcm with iterative - {}, std::lcm - {}\n", lcm_recursive(a, b), lcm_iterative(a, b), std::lcm(a, b));
}