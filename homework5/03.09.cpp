#include <array>
#include <cstdint>
#include <iostream>
#include <cassert>
#include <sstream>

class IPv4 {
public:
    IPv4 operator++(int) & {
        IPv4 tmp = *this;
        for (auto i = 3; i > -1; --i) {
            if (++bytes[i] != 0) {
                break;
            }
        }
        return tmp;
    }

    IPv4 operator--(int) & {
        IPv4 tmp = *this;
        for (auto i = 3; i > -1; --i) {
            if (--bytes[i] != 255) {
                break;
            }
        }
        return tmp;
    }

    IPv4 & operator++() {
        for (auto i = 3; i > -1; --i) {
            if (++bytes[i] != 0) {
                break;
            }
        }
        return *this;
    }

    IPv4 & operator--() {
        for (auto i = 3; i > -1; --i) {
            if (--bytes[i] != 255) {
                break;
            }
        }
        return *this;
    }

    friend bool operator< (IPv4 const & lhs, IPv4 const & rhs)
    {
        return (lhs.bytes[0] < rhs.bytes[0]) || 
        ((lhs.bytes[0] == rhs.bytes[0]) && (lhs.bytes[1] < rhs.bytes[1])) ||
        ((lhs.bytes[0] == rhs.bytes[0]) && (lhs.bytes[1] == rhs.bytes[1]) && (lhs.bytes[2] < rhs.bytes[2])) ||
        ((lhs.bytes[0] == rhs.bytes[0]) && (lhs.bytes[1] == rhs.bytes[1]) && (lhs.bytes[2] == rhs.bytes[2]) && (lhs.bytes[3] < rhs.bytes[3]));
    }

    friend bool operator> (IPv4 const & lhs, IPv4 const & rhs) { return  (rhs < lhs); }

    friend bool operator<=(IPv4 const & lhs, IPv4 const & rhs) { return !(lhs > rhs); }

    friend bool operator>=(IPv4 const & lhs, IPv4 const & rhs) { return !(lhs < rhs); }


    friend bool operator==(IPv4 const & lhs, IPv4 const & rhs)
    {
        return !(lhs < rhs) && !(rhs < lhs);
    }


    friend auto & operator>>(std::istream & stream, IPv4 & ip)
    {
        unsigned int a, b, c, d;
        if ( (((stream >> a).ignore() >> b).ignore() >> c).ignore() >> d) {
            if (a > 255 || b > 255 || c > 255 || d > 255) {
                stream.setstate(std::ios::failbit);
            } else {
                ip.bytes[0] = static_cast<std::uint8_t>(a);
                ip.bytes[1] = static_cast<std::uint8_t>(b);
                ip.bytes[2] = static_cast<std::uint8_t>(c);
                ip.bytes[3] = static_cast<std::uint8_t>(d);
            }
        }
        return stream;
    }


    friend auto & operator<<(std::ostream & stream, IPv4 const & ip)
    {
        return stream << static_cast<int>(ip.bytes[0]) << '.' << static_cast<int>(ip.bytes[1]) << '.' << static_cast<int>(ip.bytes[2]) << '.' << static_cast<int>(ip.bytes[3]);
    }

    IPv4(uint8_t a, uint8_t b, uint8_t c, uint8_t d) : bytes({a, b, c, d}) {}
    IPv4() : bytes({0, 0, 0, 0}) {}

private:
    std::array<std::uint8_t, 4> bytes = {0, 0, 0, 0};
};

int main() {

    // 1. Тест конструктора по умолчанию
    {
        IPv4 ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "0.0.0.0" && "IP по умолчанию должен быть 0.0.0.0");
    }

    // 2. Тест префиксного инкремента
    {
        IPv4 ip(192, 168, 1, 100);
        ++ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "192.168.1.101" && "Инкремент последнего октета");
    }

    // 3. Тест постфиксного инкремента
    {
        IPv4 ip(192, 168, 1, 100);
        IPv4 old = ip++;
        std::ostringstream oss1, oss2;
        oss1 << old;
        oss2 << ip;
        assert(oss1.str() == "192.168.1.100" && "Постфикс возвращает старое значение");
        assert(oss2.str() == "192.168.1.101" && "После постфикса значение увеличено");
    }

    // 4. Тест переноса между октетами при инкременте
    {
        IPv4 ip(192, 168, 1, 255);
        ++ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "192.168.2.0" && "Перенос: 192.168.1.255 -> 192.168.2.0");
    }

    // 5. Тест переноса через несколько октетов
    {
        IPv4 ip(192, 255, 255, 255);
        ++ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "193.0.0.0" && "Перенос: 192.255.255.255 -> 193.0.0.0");
    }

    // 6. Тест переполнения при инкременте
    {
        IPv4 ip(255, 255, 255, 255);
        ++ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "0.0.0.0" && "Переполнение: 255.255.255.255 -> 0.0.0.0");
    }

    // 7. Тест префиксного декремента
    {
        IPv4 ip(192, 168, 1, 100);
        --ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "192.168.1.99" && "Декремент последнего октета");
    }

    // 8. Тест постфиксного декремента
    {
        IPv4 ip(192, 168, 1, 100);
        IPv4 old = ip--;
        std::ostringstream oss1, oss2;
        oss1 << old;
        oss2 << ip;
        assert(oss1.str() == "192.168.1.100" && "Постфикс возвращает старое значение");
        assert(oss2.str() == "192.168.1.99" && "После постфикса значение уменьшено");
    }

    // 9. Тест переноса при декременте
    {
        IPv4 ip(192, 168, 1, 0);
        --ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "192.168.0.255" && "Перенос: 192.168.1.0 -> 192.168.0.255");
    }

    // 10. Тест переполнения при декременте
    {
        IPv4 ip(0, 0, 0, 0);
        --ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "255.255.255.255" && "Переполнение: 0.0.0.0 -> 255.255.255.255");
    }

    // 11. Тест оператора <
    {
        IPv4 ip1(192, 168, 1, 1);
        IPv4 ip2(192, 168, 1, 2);
        IPv4 ip3(192, 168, 2, 0);
        IPv4 ip4(193, 0, 0, 0);
        
        assert(ip1 < ip2 && "192.168.1.1 < 192.168.1.2");
        assert(ip2 < ip3 && "192.168.1.2 < 192.168.2.0");
        assert(ip3 < ip4 && "192.168.2.0 < 193.0.0.0");
        assert(!(ip2 < ip1) && "192.168.1.2 не < 192.168.1.1");
    }

    // 12. Тест оператора ==
    {
        IPv4 ip1(192, 168, 1, 1);
        IPv4 ip2(192, 168, 1, 1);
        IPv4 ip3(192, 168, 1, 2);
        
        assert(ip1 == ip2 && "Равные IP должны быть равны");
        assert(!(ip1 == ip3) && "Разные IP не должны быть равны");
    }

    // 13. Тест оператора >
    {
        IPv4 ip1(192, 168, 1, 2);
        IPv4 ip2(192, 168, 1, 1);
        
        assert(ip1 > ip2 && "192.168.1.2 > 192.168.1.1");
        assert(!(ip2 > ip1) && "192.168.1.1 не > 192.168.1.2");
    }

    // 14. Тест оператора <=
    {
        IPv4 ip1(192, 168, 1, 1);
        IPv4 ip2(192, 168, 1, 1);
        IPv4 ip3(192, 168, 1, 2);
        
        assert(ip1 <= ip2 && "Равные IP: <= истинно");
        assert(ip1 <= ip3 && "Меньший IP: <= истинно");
        assert(!(ip3 <= ip1) && "Больший IP: <= ложно");
    }

    // 15. Тест оператора >=
    {
        IPv4 ip1(192, 168, 1, 2);
        IPv4 ip2(192, 168, 1, 1);
        IPv4 ip3(192, 168, 1, 1);
        
        assert(ip1 >= ip2 && "Больший IP: >= истинно");
        assert(ip2 >= ip3 && "Равные IP: >= истинно");
        assert(!(ip2 >= ip1) && "Меньший IP: >= ложно");
    }

    // 16. Тест вывода
    {
        IPv4 ip(192, 168, 1, 1);
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "192.168.1.1" && "Вывод должен быть в формате x.x.x.x");
    }

    // 17. Тест ввода
    {
        std::istringstream iss("10.0.0.1");
        IPv4 ip;
        iss >> ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "10.0.0.1" && "Ввод должен парсить формат x.x.x.x");
    }

    // 18. Тест цепочки инкрементов
    {
        IPv4 ip(255, 255, 255, 253);
        ++ip; ++ip; ++ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "0.0.0.0" && "Три инкремента от 255.255.255.253");
    }

    // 19. Тест цепочки декрементов
    {
        IPv4 ip(0, 0, 0, 3);
        --ip; --ip; --ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "0.0.0.0" && "Три декремента от 0.0.0.3");
    }

    // 20. Тест граничных значений ввода
    {
        std::istringstream iss("255.255.255.255");
        IPv4 ip;
        iss >> ip;
        std::ostringstream oss;
        oss << ip;
        assert(oss.str() == "255.255.255.255" && "Ввод максимального IP");
    }
}