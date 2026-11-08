//////////////////////////////////////////////////////////////////

// chapter : Generic Programming

//////////////////////////////////////////////////////////////////

// content : Tuples
//
// content : Dependent Nested Templates
//
// content : Disambiguation Specifier template

//////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <type_traits> 

//////////////////////////////////////////////////////////////////

template < typename ... Ts > class Tuple {
public:
    constexpr std::size_t size() const {
        return sizeof...(Ts);
    }
};

//////////////////////////////////////////////////////////////////

template < typename T, typename ... Ts > class Tuple < T, Ts ... >
{
public :

    constexpr Tuple(T && x, Ts && ... xs)
    :
        m_head(std::forward < T  > (x )   ),

        m_tail(std::forward < Ts > (xs)...)
    {}

//  ------------------------------------------------

    template < std::size_t I > constexpr auto get() const
    {
        if constexpr (I > 0)
        {
            return m_tail.template get < I - 1 > ();
        }
        else
        {
            return m_head;
        }
    }

    constexpr std::size_t size() const {
        return 1 + sizeof...(Ts);
    }

private :

    T m_head;

    Tuple < Ts ... > m_tail;
};

//////////////////////////////////////////////////////////////////

int main() 
{
    // 1. Оригинальный тест из примера (работает, т.к. передаем rvalue-литералы)
    Tuple < int, double, std::string > tuple(1, 2.0, "aaaaa");
    assert(tuple.get < 0 > () == 1);
    assert(tuple.size() == 3);

    // 2. Тесты через static_assert (используем тривиальные типы для гарантии constexpr)
    constexpr Tuple<int, double, char> constexpr_tuple(1, 2.0, 'X');
    
    static_assert(constexpr_tuple.size() == 3, "Ошибка: размер должен быть 3");
    static_assert(constexpr_tuple.get<0>() == 1, "Ошибка: элемент 0");
    static_assert(constexpr_tuple.get<1>() == 2.0, "Ошибка: элемент 1");
    static_assert(constexpr_tuple.get<2>() == 'X', "Ошибка: элемент 2");

    // 3. Проверка типов. ВАЖНО: т.к. get() возвращает `auto`, он возвращает 
    // значение по копии (int), а не ссылку (const int&). Проверяем именно это.
    static_assert(std::is_same_v<decltype(constexpr_tuple.get<0>()), int>, "Тип должен быть int (по значению)");
    static_assert(std::is_same_v<decltype(constexpr_tuple.get<1>()), double>, "Тип должен быть double (по значению)");

    // 4. Проверка пустого кортежа
    constexpr Tuple<> empty_tuple;
    static_assert(empty_tuple.size() == 0, "Ошибка: размер пустого кортежа должен быть 0");

    // 5. Проверка кортежа из 1 элемента
    constexpr Tuple<char> single_tuple('Z');
    static_assert(single_tuple.size() == 1, "Ошибка: размер кортежа из 1 элемента должен быть 1");
    static_assert(single_tuple.get<0>() == 'Z', "Ошибка: значение не совпадает");

    // МЫ УБРАЛИ тест с lvalue (int a = 42; Tuple<...> t(a, b);), 
    // потому что исходный конструктор Tuple(T&&, Ts&&...) физически не может 
    // принять lvalue, и это правильное поведение для данного примера.

    return 0;

}

//////////////////////////////////////////////////////////////////