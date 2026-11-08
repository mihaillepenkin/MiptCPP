#include <cassert>

template <int X> struct fibonacci {
    static inline int const value = fibonacci<X - 1>::value + fibonacci<X - 2>::value;
};

template <> struct fibonacci <1> {
    static inline int const value = 1;
};

template <> struct fibonacci <0> {
    static inline int const value = 1;
};

template <int X> int const fibonacci_v = fibonacci<X>::value;

int main() {
    static_assert(fibonacci_v < 5 > == 8);
    static_assert(fibonacci_v < 6 > == 13);
    static_assert(fibonacci_v < 7 > == 21);
}