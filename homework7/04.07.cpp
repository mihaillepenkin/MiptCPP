//////////////////////////////////////////////////////////////////////////////////////////

// chapter : Generic Programming

//////////////////////////////////////////////////////////////////////////////////////////

// content : Hybrid Metaprogramming
//
// content : Compile-Time Rational Arithmetic
//
// content : Dependent Names Problem
//
// content : Dependent Types
//
// content : Disambiguation Specifier typename
//
// content : Operator +

//////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <numeric>

//////////////////////////////////////////////////////////////////////////////////////////

template < int N = 0, int D = 1 > struct Ratio
{
    constexpr static auto num = N;

    static_assert(D != 0);

    constexpr static auto den = D;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > struct Sum
{
    constexpr static auto num = R1::num * R2::den + R2::num * R1::den;

    constexpr static auto den = R1::den * R2::den;

    constexpr static auto gcd = std::gcd(num, den);

//  ------------------------------------------------------------------

    using type = Ratio < num / gcd, den / gcd> ;
};

template <typename R1, typename R2> struct Mul {
    constexpr static auto num = R1::num *  R2::num;
    constexpr static auto den = R1::den *  R2::den;

    constexpr static auto gcd = std::gcd(num, den);

    using type = Ratio < num / gcd, den / gcd>;
};

template < typename R1, typename R2 > using sum = typename Sum < R1, R2 > ::type;

template < typename R1, typename R2 > using mul = typename Mul < R1, R2 > ::type;


template < typename R1, typename R2> struct Sub {
    using type = sum <R1, mul<Ratio <-1>, R2>>;
};

template < typename R1, typename R2 > using sub = typename Sub < R1, R2 > ::type;

template < typename R> struct Revert {
    using type = Ratio <R::den, R::num>;
};

template < typename R> using revert = typename Revert < R > ::type;

template < typename R1, typename R2> struct Div {
    using type = mul <R1, revert<R2>>;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > using div = typename Div < R1, R2 > ::type;

//////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename R = Ratio < 1 > > struct Duration
{
    T x = T();
};

//////////////////////////////////////////////////////////////////////////////////////////

template
<
    typename T1, typename R1,

    typename T2, typename R2
>
constexpr auto operator+(Duration < T1, R1 > const & lhs, Duration < T2, R2 > const & rhs)
{
    using ratio_t = Ratio < 1, sum < R1, R2 > ::den > ;

    auto x =
    (
        lhs.x * ratio_t::den / R1::den * R1::num +

        rhs.x * ratio_t::den / R2::den * R2::num
    );

    return Duration < decltype(x), ratio_t > (x);
}

template
<
    typename T1, typename R1,

    typename T2, typename R2
>
constexpr auto operator-(Duration < T1, R1 > const & lhs, Duration < T2, R2 > const & rhs)
{
    using ratio_t = Ratio < 1, sum < R1, R2 > ::den > ;

    auto x =
    (
        lhs.x * ratio_t::den / R1::den * R1::num -

        rhs.x * ratio_t::den / R2::den * R2::num
    );

    return Duration < decltype(x), ratio_t > (x);
}

//////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    using R1 = Ratio<1, 2>;
    using R2 = Ratio<1, 3>;
    using R3 = Ratio<5, 6>;

    static_assert(R1::num == 1);
    static_assert(R1::den == 2);
    static_assert(R2::num == 1);
    static_assert(R2::den == 3);

    using Sum12 = sum<R1, R2>;
    static_assert(Sum12::num == 5);
    static_assert(Sum12::den == 6);

    using Mul12 = mul<R1, R2>;
    static_assert(Mul12::num == 1);
    static_assert(Mul12::den == 6);

    using Sub12 = sub<R1, R2>;
    static_assert(Sub12::num == 1);
    static_assert(Sub12::den == 6);

    using Div12 = div<R1, R2>;
    static_assert(Div12::num == 3);
    static_assert(Div12::den == 2);

    using RevertR1 = revert<R1>;
    static_assert(RevertR1::num == 2);
    static_assert(RevertR1::den == 1);

    constexpr Duration<int, Ratio<1, 1000>> d1{100};
    constexpr Duration<int, Ratio<1, 1000>> d2{50};

    constexpr auto d3 = d1 + d2;
    static_assert(d3.x == 75);

    constexpr auto d4 = d1 - d2;
    static_assert(d4.x == 25);

    return 0;
}