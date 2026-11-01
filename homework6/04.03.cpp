#include <cassert>
#include <algorithm>
#include <array>


template <typename T> T calculateMin(T x) {
    return x;
}

template <typename T> T calculateMax(T x) {
    return x;
}

template <typename T, typename ... Ts> T calculateSum(T x, Ts ... xs) {
    return (x + ... + xs);
}

template <typename T, typename ... Ts> T calculateMin(T x, Ts ... xs) {
    return std::min(x, calculateMin(xs...));
}

template <typename T, typename ... Ts> T calculateMax(T x, Ts ... xs) {
    return std::max(x, calculateMax(xs...));
}

template <typename T, typename ... Ts> std::array<T, 4> calculateMathStatistics(T x, Ts ... xs) {
    std::array<T, 4> output = {};
    output[0] = calculateSum(x, xs...);
    output[1] = output[0] / (1.0 + sizeof...(xs));
    output[2] = calculateMin(x, xs...);
    output[3] = calculateMax(x, xs...);
    return output;
}

int main() {
    // Тест 1: Несколько положительных чисел
    {
        auto stats = calculateMathStatistics(10.5, 5.5, 20.0, 15.0);
        
        assert(stats[0] == 51.0);   // sum: 10.5 + 5.5 + 20.0 + 15.0 = 51.0
        assert(stats[1] == 12.75);  // average: 51.0 / 4 = 12.75
        assert(stats[2] == 5.5);    // min
        assert(stats[3] == 20.0);   // max
    }
    
    // Тест 2: Отрицательные числа
    {
        auto stats = calculateMathStatistics(-5.0, -10.0, -3.5, -8.0);
        
        assert(stats[0] == -26.5);  // sum: -5.0 + -10.0 + -3.5 + -8.0 = -26.5
        assert(stats[1] == -6.625); // average: -26.5 / 4 = -6.625
        assert(stats[2] == -10.0);  // min
        assert(stats[3] == -3.5);   // max
    }
    
    // Тест 3: Одно число
    {
        auto stats = calculateMathStatistics(42.0);
        
        assert(stats[0] == 42.0);   // sum
        assert(stats[1] == 42.0);   // average: 42.0 / 1 = 42.0
        assert(stats[2] == 42.0);   // min
        assert(stats[3] == 42.0);   // max
    }
    
    // Тест 4: Смешанные положительные и отрицательные
    {
        auto stats = calculateMathStatistics(-10.0, 20.0, -5.0, 15.0, 0.0);
        
        assert(stats[0] == 20.0);   // sum: -10.0 + 20.0 + -5.0 + 15.0 + 0.0 = 20.0
        assert(stats[1] == 4.0);    // average: 20.0 / 5 = 4.0
        assert(stats[2] == -10.0);  // min
        assert(stats[3] == 20.0);   // max
    }
    
    // Тест 5: Дробные числа с точным представлением
    {
        auto stats = calculateMathStatistics(1.5, 2.5, 3.5);
        
        assert(stats[0] == 7.5);    // sum: 1.5 + 2.5 + 3.5 = 7.5
        assert(stats[1] == 2.5);    // average: 7.5 / 3 = 2.5
        assert(stats[2] == 1.5);    // min
        assert(stats[3] == 3.5);    // max
    }
    
    // Тест 6: Два числа
    {
        auto stats = calculateMathStatistics(100.0, 200.0);
        
        assert(stats[0] == 300.0);  // sum
        assert(stats[1] == 150.0);  // average: 300.0 / 2 = 150.0
        assert(stats[2] == 100.0);  // min
        assert(stats[3] == 200.0);  // max
    }

}