#include <type_traits>

template < typename T > struct Is_const : std::false_type {};

template <typename T> struct Is_const <T const> : std::true_type {};

template <typename T> constexpr bool is_const = Is_const<T>::value;



template <typename T> struct Is_class {
private:
    template < typename U > constexpr static std::true_type test(int U::*);

    template < typename U > constexpr static std::false_type test(...);
public:
    using type = decltype(test<T>(0));
};

template <typename T> constexpr bool is_class = Is_class<T>::type::value;



template <typename T> struct Add_const {
    using type = T const;
};

template <typename T> using add_const = Add_const<T>::type;



template <typename T> struct Remove_const {
    using type = T;
};

template <typename T> struct Remove_const <T const> {
    using type = T;
};

template <typename T> using remove_const = Remove_const<T>::type;



template <bool B, typename T, typename F> struct Conditional {
    using type = T;
};

template <typename T, typename F> struct Conditional <false, T, F> {
    using type = F;
};

template <bool B, typename T, typename F> using conditional = Conditional<B, T, F>::type;



int main()
{
    // Tests for is_const
    static_assert(is_const < int > == false);
    static_assert(is_const < int const > == true);
    static_assert(is_const < double > == false);
    static_assert(is_const < double const > == true);
    static_assert(is_const < int & > == false);
    
    // Compare with standard
    static_assert(std::is_const_v < int > == is_const < int > );
    static_assert(std::is_const_v < int const > == is_const < int const > );
    

    // Tests for is_class
    static_assert(is_class < int > == false);
    static_assert(is_class < double > == false);
    static_assert(is_class < void > == false);
    static_assert(is_class < int * > == false);
    static_assert(is_class < int [] > == false);
    static_assert(is_class < int (int) > == false);
    
    struct TestClass {};
    
    static_assert(is_class < TestClass > == true);
    static_assert(is_class < TestClass const > == true);
    // Compare with standard
    static_assert(std::is_class_v < int > == is_class < int > );
    static_assert(std::is_class_v < TestClass > == is_class < TestClass > );
    

    // Tests for add_const
    static_assert(std::is_same_v < add_const < int > , int const > );
    static_assert(std::is_same_v < add_const < double > , double const > );
    static_assert(std::is_same_v < add_const < TestClass > , TestClass const > );
    
    static_assert(std::is_same_v < std::add_const_t < int > , add_const < int > > );
    

    // Tests for remove_const
    static_assert(std::is_same_v < remove_const < int const > , int > );
    static_assert(std::is_same_v < remove_const < int > , int > );  // non-const unchanged
    static_assert(std::is_same_v < remove_const < TestClass const > , TestClass > );
    
    static_assert(std::is_same_v < std::remove_const_t < int const > , remove_const < int const > > );

    // Tests for conditional
    static_assert(std::is_same_v < conditional < true, int, double > , int > );
    static_assert(std::is_same_v < conditional < false, int, double > , double > );
    static_assert(std::is_same_v < conditional < true, TestClass, int > , TestClass > );
    
    static_assert(std::is_same_v < std::conditional_t < true, int, double > , conditional < true, int, double > > );
    static_assert(std::is_same_v < std::conditional_t < false, int, double > , conditional < false, int, double > > );
}