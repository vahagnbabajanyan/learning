/*
 * my_algorithms.hpp
 */

#ifndef _MY_ALGORITHMS_HPP_
#define _MY_ALGORITHMS_HPP_

#include "utilities.hpp"

#include <vector>

namespace my_algorithms
{
        std::vector<bool> add_two_binaries(std::vector<bool> v1, std::vector<bool> v2)
        {
                utilities::align_binaries(v1, v2);

                utilities::print_full_vec(v1);
                utilities::print_full_vec(v2);

                std::vector<bool> res(v1.size() + 1, 0);
                int size = v1.size();
                for (int i = size - 1; i >= 0; --i) {
                        res[i] = (res[i + 1] & v1[i]) | (res[i + 1] & v2[i]) | (v1[i] & v2[i]);
                        res[i + 1] = res[i + 1] ^ (v1[i] ^ v2[i]);
                }
                return res;
        }
}

#endif
