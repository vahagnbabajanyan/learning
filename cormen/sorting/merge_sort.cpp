#include <vector>
#include <cassert>
#include <algorithm>
#include <limits>

#include "sorting.hpp"
#include "utilities.hpp"

namespace sorting
{
        void merge(std::vector<int>& vec, int p, int q, int r)
        {
                int size = vec.size();
                assert( p <= q && q < r );
                assert( r < size );
                int n1 = q - p + 1;
                int n2 = r - q;
                std::vector<int> left(n1 + 1);
                std::vector<int> right(n2 + 1);
                std::copy(vec.begin() + p, vec.begin() + q + 1, left.begin());
                std::copy(vec.begin() + q + 1, vec.begin() + r + 1, right.begin());
                left[n1] = std::numeric_limits<int>::max();
                right[n2] = std::numeric_limits<int>::max();

                int i_left = 0;
                int i_right = 0;
                for(int k = p; k <= r; ++k)
                {
                        if (left[i_left] < right[i_right]) {
                                vec[k] = left[i_left];
                                ++i_left;
                        } else {
                                vec[k] = right[i_right];
                                ++i_right;
                        }
                }
        }

        void merge_sort(std::vector<int>& vec, int p, int r)
        {
                if (p < r) {
                        int q = (p + r) / 2;
                        merge_sort(vec, p, q);
                        merge_sort(vec, q + 1, r);
                        merge(vec, p, q, r);
                }
        }



        void merge_no_sentinel(std::vector<int>& vec, int p, int q, int r)
        {
                int size = vec.size();
                assert( p <= q && q < r );
                assert( r < size );
                int n1 = q - p + 1;
                int n2 = r - q;
                std::vector<int> left(n1);
                std::vector<int> right(n2);
                std::copy(vec.begin() + p, vec.begin() + q + 1, left.begin());
                std::copy(vec.begin() + q + 1, vec.begin() + r + 1, right.begin());
                int li = 0;
                int ri = 0;
                int k = p;
                while (li < n1 && ri < n2) {
                        if (left[li] <= right[ri]) {
                                vec[k] = left[li];
                                ++li;
                        } else {
                                vec[k] = right[ri];
                                ++ri;
                        }
                        ++k;
                }
                if (li >= n1) {
                        while (ri < n2) {
                                vec[k] = right[ri];
                                ++ri;
                                ++k;
                        }
                        return;
                }
                while(li < n1) {
                        vec[k] = left[li];
                        ++li;
                        ++k;
                }
                /*bool to_check = true;
                std::vector<int>::iterator it;
                for (int k = p; k <= r; ++k) {
                        if (to_check) {
                                if (left[li] <= right[ri]) {
                                        it = left.begin() + li;
                                        ++li;
                                        if (li >= n1) {
                                                to_check = false;
                                        }
                                } else {
                                        it = right.begin() + ri;
                                        ++ri;
                                        if (ri >= n2) {
                                                to_check = false;
                                        }
                                }
                        } else {
                                ++it;
                        }
                        vec[k] = *it;
                }*/
        }

        void merge_sort_no_sentinel(std::vector<int>& vec, int p, int r)
        {
                if (p < r) {
                        int q = (p + r) / 2;
                        merge_sort_no_sentinel(vec, p, q);
                        merge_sort_no_sentinel(vec, q + 1, r);
                        merge_no_sentinel(vec, p, q, r);
                }
        }
} // end of namespace sorting
