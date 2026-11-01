#include <cassert>
#include <vector>

template <typename C> void handle( C & container, int x) {
    container.push_back(x);
}

template <typename C, typename T> void handle( C &, T) {
    return;
}

template <typename C, typename ... Ts> void handle( C & container, Ts ... xs) {
    (handle(container, xs), ...);
}


int main() {
    // Тест 1: Только int значения
    {
        std::vector<int> vec;
        handle(vec, 1, 2, 3, 4, 5);
        
        assert(vec.size() == 5);
        assert(vec[0] == 1);
        assert(vec[1] == 2);
        assert(vec[2] == 3);
        assert(vec[3] == 4);
        assert(vec[4] == 5);
    }

    // Тест 2: Смешанные типы - только int должны вставиться
    {
        std::vector<int> vec;
        handle(vec, 10, 2.5, 20, "hello", 30, true, 40, 'a', 50);
        
        assert(vec.size() == 5);
        assert(vec[0] == 10);
        assert(vec[1] == 20);
        assert(vec[2] == 30);
        assert(vec[3] == 40);
        assert(vec[4] == 50);
    }

    // Тест 3: Нет int значений - контейнер должен остаться пустым
    {
        std::vector<int> vec;
        handle(vec, 1.5, 2.5, 3.5, "test", true, 'x');
        
        assert(vec.empty());
        assert(vec.size() == 0);
    }

    // Тест 4: Один int
    {
        std::vector<int> vec;
        handle(vec, 42);
        
        assert(vec.size() == 1);
        assert(vec[0] == 42);
    }

    // Тест 5: Отрицательные int значения
    {
        std::vector<int> vec;
        handle(vec, -1, -2.5, -3, -4.0f, -5);
        
        assert(vec.size() == 3);  // -1, -3, -5
        assert(vec[0] == -1);
        assert(vec[1] == -3);
        assert(vec[2] == -5);
    }

    // Тест 6: Ноль как int
    {
        std::vector<int> vec;
        handle(vec, 0, 0.0, 1, 2.0);
        
        assert(vec.size() == 2);  // 0 и 1
        assert(vec[0] == 0);
        assert(vec[1] == 1);
    }


    // Тест 8: Bool не должен вставляться (bool != int в контексте перегрузки шаблонов)
    {
        std::vector<int> vec;
        handle(vec, true, false, 1, 2);
        
        assert(vec.size() == 2);  // Только 1 и 2
        assert(vec[0] == 1);
        assert(vec[1] == 2);
    }

    // Тест 9: Char не должен вставляться
    {
        std::vector<int> vec;
        handle(vec, 'a', 'b', 65, 66);
        
        assert(vec.size() == 2);  // Только 65 и 66
        assert(vec[0] == 65);
        assert(vec[1] == 66);
    }

    // Тест 10: Long не должен вставляться (long != int)
    {
        std::vector<int> vec;
        handle(vec, 1L, 2L, 3, 4);
        
        assert(vec.size() == 2);  // Только 3 и 4
        assert(vec[0] == 3);
        assert(vec[1] == 4);
    }
}    