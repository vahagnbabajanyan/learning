#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>

#include "sorting.hpp"

namespace sorting
{
        void selection_sort(std::vector<int>& vec)
        {
                for (unsigned i = 0; i < vec.size() - 1; ++i) {
                        int min_index = i;
                        for (unsigned j = i + 1; j < vec.size(); ++j) {
                                if (vec[min_index] > vec[j]) {
                                        min_index = j;
                                }
                        }
                        int tmp = vec[i];
                        vec[i] = vec[min_index];
                        vec[min_index] = tmp;
                        std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
                        std::cout << std::endl;
                }
        }

} // end of namespace sorting
