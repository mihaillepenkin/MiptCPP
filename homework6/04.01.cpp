////////////////////////////////////////////////////////////////////////////////////

// chapter : Language Core Basics

////////////////////////////////////////////////////////////////////////////////////

// content : Insertion Sort Algorithm
//
// content : Time Complexity O(N^2)
//
// content : Merge Sort Algorithm
//
// content : Time Complexity O(N*log(N))
//
// content : Hybrid Sort Algorithm
//
// content : Spatial and Temporal Locality
//
// content : Function std::midpoint
//
// content : Function std::inplace_merge

////////////////////////////////////////////////////////////////////////////////////

// support : https://www.cs.usfca.edu/~galles/visualization/ComparisonSort.html

////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>
#include <span>
#include <random>


////////////////////////////////////////////////////////////////////////////////////

template <typename T> void order(std::vector < T > & vector, std::size_t left, std::size_t right)
{
    for (auto i = left + 1; i < right; ++i)
    {
        for (auto j = i; j > left; --j)
        {
            if (vector[j - 1] > vector[j])
            {
                std::swap(vector[j], vector[j - 1]);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////

template <typename T> T get_pivot(std::vector < T > & vector, std::size_t l, std::size_t r) {
    T first  = vector[l];
    T middle = vector[std::midpoint(l, r)];
    T last   = vector[r];
    if ((first <= middle) == (middle <= last))
        return middle;
    if ((first <= last) == (last <= middle))
        return last;
    return first;
}

template <typename T> std::size_t partition(std::vector < T > & vector, T pivot, std::size_t l, std::size_t r) {
    while (true) {
        while (vector[l] < pivot) {
            ++l;
        }
        while (vector[r] > pivot) {  
            --r;
        }
        if (l >= r) {
            return r;
        }
        std::swap(vector[l], vector[r]);
        ++l;
        if (r == 0)  {
            break;
        }
        --r;
    }
    return r;
}

template <typename T> void quick_sort(std::vector < T > & vector, std::size_t l, std::size_t r) {

    if (r - l > 16)
    {
        T pivot = get_pivot(vector, l, r);
        T pivot_ind = partition(vector, pivot, l, r);

        quick_sort< T >(vector, l, pivot_ind);
        quick_sort< T >(vector, pivot_ind + 1, r);
    }
    else
    {
        order< T >(vector, l,   r + 1);
    }
}

template <typename T> void sort(std::vector < T > & vector)
{
    if (!vector.empty())  {
        quick_sort(vector, 0, std::size(vector) - 1);
    }
}


////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void run_sort_tests() {
    const std::size_t size = 50;

    {
        std::vector<T> vec(size);
        std::iota(vec.begin(), vec.end(), T(0));
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(vec.begin(), vec.end(), gen);

        sort(vec);
        assert(std::ranges::is_sorted(vec));
    }

    {
        std::vector<T> vec(size);
        std::iota(vec.begin(), vec.end(), T(0)); 
        std::reverse(vec.begin(), vec.end());

        sort(vec);
        assert(std::ranges::is_sorted(vec));
    }
}


int main()
{
    run_sort_tests<int>();
    run_sort_tests<long>();
    run_sort_tests<double>();
}

////////////////////////////////////////////////////////////////////////////////////