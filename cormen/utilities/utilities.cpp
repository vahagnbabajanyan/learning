#include <iostream>
#include <vector>
#include <algorithm>

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
} // end of namespace utilities
