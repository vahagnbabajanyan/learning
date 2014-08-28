/*
 * sorting.hpp declarations of implementations of sorting algorithm functions
 */

#ifndef _SORTING_HPP_
#define _SORTING_HPP_

#include <vector>

namespace sorting
{
        // insertion_sort. Cormen: Chapter 2.1
        void insertion_sort(std::vector<int>&);

        // insertion_sort. Cormen: Chapter 2.1: Exercise: 2.1-2
        // With required parameter order_inc
        void insertion_sort(std::vector<int>&, bool order_inc);

        // insertion sort. Cormen: Exercise 2.3-4
        // recursive insertion sort
        void recursive_insertion_sort(std::vector<int>&, int);

        // selection_sort Cormen: Exercise: 2.2-2
        void selection_sort(std::vector<int>& vec);

        // merge_sort. divide_and_conquer approach. Cormen: Chapter 2.3.1
        void merge_sort(std::vector<int>& vec, int p, int r);

        // auxiliary operation for merge_sort
        void merge(std::vector<int>&, int p, int q, int r);

} // end of namespace sorting

#endif
