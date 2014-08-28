#include <vector>

#include "sorting.hpp"
#include "utilities.hpp"

namespace {
        bool greater(int x, int y, bool ord)
        {
                return ord ? x > y : x < y;
        }
}

namespace sorting
{
        void insertion_sort(std::vector<int>& vec)
        {
                int size = vec.size();
                for (int i = 1; i < size; ++i) {
                        int key = vec[i];
                        int j = i - 1;
                        while (j >= 0 && key < vec[j]) {
                                vec[j + 1] = vec[j];
                                --j;
                        }
                        vec[j + 1] = key;
                }
        }


        void insertion_sort(std::vector<int>& vec, bool non_inc)
        {
                int size = vec.size();
                for (int i = 1; i < size; ++i) {
                        int key = vec[i];
                        int j = i - 1;
                        while (j >= 0 && greater(key, vec[j], non_inc)) {
                                vec[j + 1] = vec[j];
                                --j;
                        }
                        vec[j + 1] = key;
                }        }
} // end of namespace sorting
