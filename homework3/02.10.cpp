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

////////////////////////////////////////////////////////////////////////////////////

void order(std::vector < int > & vector, std::size_t left, std::size_t right)
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

void merge(std::vector < int > & vector_1, std::size_t left, std::size_t right)
{
    auto middle = std::midpoint(left, right), size = right - left;

    std::vector < int > vector_2(size, 0);

    for (auto i = left, j = middle, k = 0uz; k < size; ++k)
    {
        if (i < middle && ((j < right && vector_1[i] <= vector_1[j]) || j == right))
        {
            vector_2[k] = vector_1[i++];
        }
        else
        {
            vector_2[k] = vector_1[j++];
        }
    }

    for (auto i = 0uz, j = 0uz; j < size; ++j)
    {
        vector_1[left + i++] = vector_2[j];
    }
}

////////////////////////////////////////////////////////////////////////////////////

void split(std::vector < int > & vector, std::size_t left, std::size_t right)
{
    if (right - left > 16)
    {
        auto middle = std::midpoint(left, right);

        split(vector, left,   middle);

        split(vector, middle, right );

        merge(vector, left,   right );
    }
    else
    {
        order(vector, left,   right );
    }
}

////////////////////////////////////////////////////////////////////////////////////

int get_pivot(std::vector < int > & vector, std::size_t l, std::size_t r) {
    int first = vector[l];
    int middle = vector[std::midpoint(l, r)];
    int last = vector[r];
    return first + last + middle - std::max({first, last, middle}) - std::min({first, last, middle});
}

std::size_t partition(std::vector < int > & vector, int pivot, std::size_t l, std::size_t r) {
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

void quick_sort(std::vector < int > & vector, std::size_t l, std::size_t r) {
    if (l >= r) {
        return;
    }
    int pivot = get_pivot(vector, l, r);
    int pivot_ind = partition(vector, pivot, l, r);

    quick_sort(vector, l, pivot_ind - 1);
    quick_sort(vector, pivot_ind + 1, r);
}

void sort(std::vector < int > & vector)
{
    if (!vector.empty())  {
        quick_sort(vector, 0, std::size(vector) - 1);
    }
}


////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto size = 1uz << 10;

//  ---------------------------------------

    std::vector < int > vector(size, 0);

//  ---------------------------------------

    for (auto i = 0uz; i < size; ++i)
    {
        vector[i] = size - i;
    }

//  ---------------------------------------

    sort(vector);


//  ---------------------------------------

    assert(std::ranges::is_sorted(vector));
}

////////////////////////////////////////////////////////////////////////////////////