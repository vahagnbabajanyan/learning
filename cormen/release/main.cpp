#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "utilities.hpp"
#include "sorting.hpp"
#include "searching.hpp"
#include "my_algorithms.hpp"

int main()
{
/*        std::vector<int> vec;
        utilities::rand_init_vec(vec);
        utilities::print_full_vec(vec);

        //sorting::merge_sort(vec, 0, vec.size() - 1);
        //sorting::selection_sort(vec);
        sorting::recursive_insertion_sort(vec, vec.size() - 1);
        utilities::print_full_vec(vec);
        int key;
        char c = 'y';
        while('y' == c) {
                std::cout << "input please key: ";
                std::cin >> key;
                int index;
                if (-1 == (index = searching::recursive_binary_search(vec, 0, vec.size() - 1, key))) {
                        std::cout << "Theare is no such element in array" << std::endl;
                } else {
                        std::cout << "The element : " << key << " is found in array with index : " << index << std::endl;
                }
                std::cout << "do you want to contonue y/n : ";
                std::cin >> c;
        }*/
        std::vector<int> vec;
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(9);
        vec.push_back(10);
        vec.push_back(4);
        vec.push_back(5);
        vec.push_back(6);
        vec.push_back(7);
        vec.push_back(8);
        utilities::print_full_vec(vec);

        std::cout << "the number of inversions: " << utilities::count_inversions(vec) << std::endl;

}
