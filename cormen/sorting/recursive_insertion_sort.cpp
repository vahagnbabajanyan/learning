#include <vector>

#include "sorting.hpp"

namespace sorting
{
        void recursive_insertion_sort(std::vector<int>& vec, int n)
        {
                if (1 == n) {
                        return;
                }
                recursive_insertion_sort(vec, n - 1);
                int j = n - 1;
                int key = vec[n];
                while (vec[j] >= key && j >= 0) {
                        vec[j + 1] = vec[j];
                        --j;
                }
                vec[j + 1] = key;
        }
} // end of namespace sorting
