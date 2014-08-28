/*
 * searching.hpp
 */

#ifndef _SEARCHING_HPP
#define _SEARCHING_HPP

namespace searching
{
        // linear search
        template <typename KeyType>
        int linear_search(const std::vector<KeyType>& vec, const KeyType key)
        {
                int i = 0;
                while (i < vec.size()) {
                        if (key == vec[i]) {
                                return i;
                        }
                        ++i;
                }
                return -1;
        }

        int recursive_binary_search(const std::vector<int>& vec, int begin, int end, const int key)
        {
                if (begin < end) {
                        int mid = (begin + end) / 2;
                        if (key == vec[mid]) {
                                return mid;
                        } else if (key < vec[mid]) {
                                return recursive_binary_search(vec, begin, mid - 1, key);
                        }
                        return recursive_binary_search(vec, mid + 1, end, key);
                }
                if (begin == end && key == vec[begin]) {
                        return begin;
                }
                return -1;
        }

        int binary_search(const std::vector<int>& vec, const int key)
        {
                int begin = 0;
                int end = vec.size() - 1;
                while (begin < end) {
                        int mid = (begin + end) / 2;
                        if (key == vec[mid]) {
                                return mid;
                        } else if (key < vec[mid]) {
                                end = mid - 1;
                        } else {
                                begin = mid + 1;
                        }
                }
                return -1;
        }
} // end of namespace searching

#endif
