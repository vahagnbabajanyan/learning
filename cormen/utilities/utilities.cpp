#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <limits>

#include "utilities.hpp"

namespace utilities
{
        void num_to_binary(const int num, std::vector<bool>& result)
        {
                int reminder;
                if (num <= 1) {
                        result.push_back(num);
                        return;
                }
                reminder = num % 2;
                num_to_binary(num >> 1, result);
                result.push_back(reminder);
        }

        int binary_to_num(const std::vector<bool>& bin)
        {
                int num = 0;
                int size = bin.size();
                for (int i = 1; i <= size; ++i) {
                        num = num + bin[i] * (1 << (size - i));
                }
                return num;
        }

        void align_binaries(std::vector<bool>& v1, std::vector<bool>& v2)
        {
                if (v1.size() == v2.size()) {
                        return;
                }
                if (v1.size() > v2.size()) {
                        std::vector<bool> tmp(v1.size(), 0);
                        tmp.insert(tmp.begin() + (v1.size() - v2.size()), v2.begin(), v2.end());
                        tmp.erase(tmp.begin() + v1.size(), tmp.end());
                        v2.clear();
                        std::copy(tmp.begin(), tmp.end(), std::back_inserter(v2));
                        return;
                }
                std::vector<bool> tmp(v2.size(), 0);
                tmp.insert(tmp.begin() + (v2.size() - v1.size()), v1.begin(), v1.end());
                tmp.erase(tmp.begin() + v2.size(), tmp.end());
                v1.clear();
                std::copy(tmp.begin(), tmp.end(), std::back_inserter(v1));
        }

        void merge_count_inversions(std::vector<int>& vec, int p, int q, int r, int& inv_count)
        {
                int n1 = q - p + 1;
                std::vector<int> left(vec.begin() + p, vec.begin() + q + 1);
                std::vector<int> right(vec.begin() + q + 1, vec.begin() + r + 1);
                left.push_back(std::numeric_limits<int>::max());
                right.push_back(std::numeric_limits<int>::max());
                int lindx = 0;
                int rindx = 0;
                for (int k = p; k <= r; ++k) {
                        if (left[lindx] <= right[rindx]) {
                                vec[k] = left[lindx];
                                ++lindx;
                        } else {
                                vec[k] = right[rindx];
                                if (std::numeric_limits<int>::max() != left[lindx]) {
                                        inv_count += n1 - lindx;
                                }
                                ++rindx;
                        }
                }
        }

        void merge_sort_count_inversions(std::vector<int>& vec, int p, int r, int& inv_count)
        {
                if ( p < r) {
                        int q = (p + r) / 2;
                        merge_sort_count_inversions(vec, p, q, inv_count);
                        merge_sort_count_inversions(vec, q + 1, r, inv_count);
                        merge_count_inversions(vec, p, q, r, inv_count);
                }
        }

        int count_inversions(const std::vector<int>& vec)
        {
                std::vector<int> tmp(vec.begin(), vec.end());
                int inv_count;
                merge_sort_count_inversions(tmp, 0, vec.size() - 1, inv_count);
                return inv_count;
        }

} // end of namespace utilities
