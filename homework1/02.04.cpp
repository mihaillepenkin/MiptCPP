#include<print>

int main() {
    for (auto i = 1uz; i < 10; i++) {
        for (auto j = 0uz; j < 10; j++) {
            for (auto z = 0uz; z < 10; z++) {
                if (i * i * i + j * j * j + z * z * z == i * 100 + j * 10 + z) {
                    std::print("{}\n", i * 100 + j * 10 + z);
                }
            }
        }
    }
}