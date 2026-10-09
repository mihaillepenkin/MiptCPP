#include<print>
#include<cmath>
#include<vector>

std::size_t calculate_kollatz_length(unsigned long long int start, std::vector<std::size_t> & cache) {
    if (start == 1) {
        return 0;
    }
    if (start < 101 && cache[start] != 0) {
        return cache[start];
    }
    std::size_t length = 0;
    if (start % 2 == 0) {
        length = 1 + calculate_kollatz_length(start / 2, cache);
    } else {
        length = 2 + calculate_kollatz_length((3 * start + 1) / 2, cache);
    }
    if (start < 101) {
        cache[start] = length;
    }
    return length;
}

int main() {
    std::vector<std::size_t> cache(101);

    auto max_length = 0uz;
    auto start_of_max_length = 0;

    for (auto i = 1; i < 101; ++i) {
        cache[i] = calculate_kollatz_length(i, cache);
        if (cache[i] > max_length) {
            max_length = cache[i];
            start_of_max_length = i;
        }
    }

    std::print("Max length - {}, start with - {}\n", max_length, start_of_max_length);
}