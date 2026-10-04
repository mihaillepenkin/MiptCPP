#include<iostream>
#include<utility>
#include<cmath>
#include<print>

void bubble_sort(double* array, int length) {
    for (auto i = 0; i < length; ++i) {
         for (auto j = 0; j < length - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
}

double calculate_standard_deviation(double * array, int length, double avarage_sum) {
    if (length <= 1) {
        return 0;
    }     
    double standard_deviation = 0;
    for (auto i = 0; i < length; ++i) {
        standard_deviation += (array[i] - avarage_sum) * (array[i] - avarage_sum);
    }
    standard_deviation /= length - 1;
    standard_deviation = std::sqrt(standard_deviation);

    return standard_deviation;
}

int append(double * & array, double new_value, int length, int capacity) {
    if (length > capacity - 1) {
        capacity *= 2;
        double * array_tmp = new double[capacity];
        for (auto i = 0; i < length; ++i) {
            array_tmp[i] = array[i];
        }
        delete[] array;
        array = array_tmp;
    }
    array[length] = new_value;
    return capacity;
}

int main() {
    int n = 0;
    double avarage_sum = 0;
    double median = 0;
    double min = 0;
    double max = 0;
    double standard_deviation = 0;
    double* array = new double[1]();
    double tmp = 0;
    int capacity = 1;


    while (std::cin >> tmp) {
        capacity = append(array, tmp, n, capacity);
        avarage_sum += array[n++];
    }

    if (n == 0) {
        delete[] array;
        std::print("length of array must be not 0\n");
        return 1;
    }

    avarage_sum /= n;
    standard_deviation = calculate_standard_deviation(array, n, avarage_sum);
    bubble_sort(array, n);
    if (n % 2 == 0) {
        median = (array[n / 2 - 1] + array[n / 2]) / 2;
    } else {
        median = array[n / 2];
    }
    min = array[0];
    max = array[n - 1];

    delete[] array;

    std::print("Max value - {}, Min Value - {}, Median - {}, Average sum - {}, Standard deviation - {}\n", max, min, median, avarage_sum, standard_deviation);
}