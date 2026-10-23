////////////////////////////////////////////////////////////////////////////////////

// chapter : Object-Oriented Programming

////////////////////////////////////////////////////////////////////////////////////

// content : Special Member Functions
//
// content : Container std::initializer_list
//
// content : Algorithm std::ranges::copy
//
// content : Deep and Shallow Copying
//
// content : Copy and Move Constructors
//
// content : Function std::exchange
//
// content : Copy and Move Operators =
//
// content : Self-Assignment Problem
//
// content : Pattern Copy-and-Swap
//
// content : Generating Special Member Functions
//
// content : Rules of 0, 3, 4 and 5

////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cstddef>
#include <cassert> 
#include <initializer_list>
#include <iterator>
#include <print>
#include <utility>

////////////////////////////////////////////////////////////////////////////////////

class Vector
{
public :

    Vector() : m_size(0), m_capacity(1)
    {
        std::print("Vector:: Vector (1)\n");
    }

//  --------------------------------------------------------------------------------

    Vector(std::initializer_list < int > list) : m_size(std::size(list)), m_capacity(std::size(list))
    {
        std::print("Vector:: Vector (2)\n");

        m_array = m_size ? new int[m_size]{} : nullptr;

        std::ranges::copy(list, m_array);
    }

//  --------------------------------------------------------------------------------

    Vector(Vector const & other) : m_size(other.m_size), m_capacity(other.m_capacity)
    {
        std::print("Vector:: Vector (3)\n");

        m_array = m_size ? new int[m_size]{} : nullptr;

        std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
    }

//  --------------------------------------------------------------------------------

    Vector(Vector && other)
    :
        m_array(std::exchange(other.m_array, nullptr)),

        m_size (std::exchange(other.m_size,  0      )),

        m_capacity (std::exchange(other.m_capacity,  0      ))
    {
        std::print("Vector:: Vector (4)\n");
    }

//  --------------------------------------------------------------------------------

   ~Vector()
    {
        std::print("Vector::~Vector\n");

        delete[] m_array;
    }

//  --------------------------------------------------------------------------------

//  auto & operator=(Vector const & other) // error
//  {
//      std::print("Vector::operator= (1)\n");
//
//      if (this != &other)
//      {
//          delete[] m_array;
//
//          m_array = (m_size = other.m_size) ? new int[m_size]{} : nullptr;
//
//          std::ranges::copy(other.m_array, other.m_array + other.m_size, m_array);
//      }
//
//      return *this;
//  }

//  --------------------------------------------------------------------------------

//  auto & operator=(Vector const & other) // bad
//  {
//      std::print("Vector::operator= (2)\n");
//
//      if (this != &other)
//      {
//          auto array = other.m_size ? new int[other.m_size]{} : nullptr;
//
//          std::ranges::copy(other.m_array, other.m_array + other.m_size, array);
//
//          delete[] std::exchange(m_array, array);
//
//          m_size = other.m_size;
//      }
//
//      return *this;
//  }

//  --------------------------------------------------------------------------------

//  auto & operator=(Vector && other) // bad
//  {
//      std::print("Vector::operator= (3)\n");
//
//      if (this != &other)
//      {
//          delete[] m_array;
//
//          m_array = std::exchange(other.m_array, nullptr);
//
//          m_size  = std::exchange(other.m_size,  0      );
//      }
//
//      return *this;
//  }

//  --------------------------------------------------------------------------------

    auto & operator=(Vector other)
    {
        std::print("Vector::operator= (4)\n");

        swap(other);

        return *this;
    }

//  --------------------------------------------------------------------------------

    void swap(Vector & other)
    {
        std::swap(m_array, other.m_array);

        std::swap(m_size,  other.m_size );

        std::swap(m_capacity,  other.m_capacity );
    }

    bool empty() const {
        return m_size == 0;
    }

    void clear() {
        for (auto i = 0uz; i < m_size; ++i) {
            m_array[i] = 0;
        }
        m_size = 0;
    }

    void push_back(int new_value) {
        if (m_array == nullptr) {
            m_array = new int[m_capacity];
        }
        if (m_size > m_capacity - 1) {
            m_capacity*=2;
            int * tmp_array = new int[m_capacity];
            for (auto i = 0uz; i < m_size; ++i) {
                tmp_array[i] = m_array[i];
            }
            delete[] std::exchange(m_array, tmp_array);
        }
        m_array[m_size++] = new_value;
    }

    std::size_t size() const {
        return m_size;
    }

    std::size_t capacity() const {
        return m_capacity;
    }

    int operator[](std::size_t index) const {
        return m_array[index];
    }

private :

    int * m_array = nullptr;

    std::size_t m_size = 0;

    std::size_t m_capacity = 1;
};

////////////////////////////////////////////////////////////////////////////////////

void swap(Vector & lhs, Vector & rhs)
{
    lhs.swap(rhs);
}

////////////////////////////////////////////////////////////////////////////////////

int main()
{

    // 1. Тест конструктора по умолчанию
    {
        Vector v;
        assert(v.empty() && "Default vector should be empty");
        assert(v.size() == 0 && "Default vector size should be 0");
        assert(v.capacity() == 1 && "Default vector capacity should be 1");
    }

    // 2. Тест initializer_list
    {
        Vector v = {10, 20, 30};
        assert(v.size() == 3 && "Size should be 3");
        assert(v.capacity() == 3 && "Capacity should be 3");
        assert(v[0] == 10 && v[1] == 20 && v[2] == 30 && "Elements mismatch");
    }

    // 3. Тест push_back и реаллокации (удвоения capacity)
    {
        Vector v;
        assert(v.capacity() == 1);
        v.push_back(1);
        assert(v.size() == 1 && v.capacity() == 1);
        
        v.push_back(2); // Триггер реаллокации (1 -> 2)
        assert(v.size() == 2 && v.capacity() == 2);
        assert(v[0] == 1 && v[1] == 2);
        
        v.push_back(3); // Триггер реаллокации (2 -> 4)
        assert(v.size() == 3 && v.capacity() == 4);
        assert(v[0] == 1 && v[1] == 2 && v[2] == 3);
    }

    // 4. Тест clear() (память НЕ должна освобождаться)
    {
        Vector v = {1, 2, 3, 4, 5};
        v.push_back(6); // size=6, capacity=10
        v.clear();
        assert(v.empty() && "Vector should be empty after clear");
        assert(v.size() == 0 && "Size should be 0 after clear");
        assert(v.capacity() == 10 && "Capacity MUST be preserved after clear");
    }

    // 5. Тест копирующего конструктора (Глубокая копия)
    {
        Vector v1 = {1, 2, 3};
        Vector v2 = v1;
        
        assert(v2.size() == 3 && v2.capacity() == 3);
        assert(v2[0] == 1 && v2[1] == 2 && v2[2] == 3);
        
        // Модифицируем v2, v1 не должен измениться
        v2.push_back(4);
        assert(v1.size() == 3 && "Original vector size changed! (Shallow copy detected)");
        assert(v2.size() == 4 && "Copied vector size should be 4");
    }

    // 6. Тест перемещающего конструктора (Move)
    {
        Vector v1 = {10, 20, 30};
        Vector v2 = std::move(v1);
        
        assert(v2.size() == 3 && v2.capacity() == 3);
        assert(v2[0] == 10 && v2[1] == 20 && v2[2] == 30);
        
        // v1 должен быть в валидном, но пустом состоянии
        assert(v1.empty() && "Moved-from vector should be empty");
        assert(v1.size() == 0 && "Moved-from vector size should be 0");
        assert(v1.capacity() == 0 && "Moved-from vector capacity should be 0");
    }

    // 7. Тест swap (через friend/глобальную функцию и метод)
    {
        Vector v1 = {1, 2};
        Vector v2 = {3, 4, 5, 6};
        
        swap(v1, v2); // Вызывает v1.swap(v2)
        
        assert(v1.size() == 4 && v1.capacity() == 4 && v1[0] == 3);
        assert(v2.size() == 2 && v2.capacity() == 2 && v2[0] == 1);
    }

    // 8. Тест Copy-and-Swap присваивания
    {
        Vector v1 = {1, 2, 3};
        Vector v2;
        
        v2 = v1; // Copy-and-swap
        assert(v2.size() == 3 && v2[2] == 3);
        
        Vector v3 = {9, 9};
        v2 = std::move(v3); // Move через тот же operator=(Vector other)
        assert(v2.size() == 2 && v2[0] == 9);
        assert(v3.empty() && v3.capacity() == 0);
    }

}

////////////////////////////////////////////////////////////////////////////////////