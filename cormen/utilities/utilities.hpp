/*
 * randomly initialize array, save in file, read from file. print full, print from to.
 */

#ifndef _RAND_VEC_HPP_
#define _RAND_VEC_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>

namespace utilities
{
        class my_exception : public std::exception
        {
        public:
                my_exception(const std::string msg)
                        : m_msg(msg)
                {}

                ~my_exception() throw()
                {}

                const char* what() const throw()
                {
                        return m_msg.c_str();
                }
        private:
                std::string m_msg;
        };

        template <typename T>
        void rand_init_vec(std::vector<T>& vec, const int size = 10, const int range = 100)
        {
                static int i = 0;
                if ( i == 0 ) {
                        srand(time(NULL));
                        ++i;
                }
                for (int i = 0; i < size; ++i) {
                        vec.push_back(rand() % range);
                }
        }

        template <typename T>
        void print_vec(const std::vector<T>& vec, int beg, int end)
        {
                std::copy(vec.begin() + beg, vec.begin() + end,
                          std::ostream_iterator<T>(std::cout, " "));
                std::cout << std::endl;
        }

        template <typename T>
        void print_full_vec(const std::vector<T>& vec)
        {
                std::copy(vec.begin(), vec.end(),
                          std::ostream_iterator<T>(std::cout, " "));
                std::cout << std::endl;
        }

        template <typename T>
        void save_vec_in_file(const std::vector<T>& vec, const std::string filename = "input")
        {
                std::ofstream fout;
                fout.open(filename.c_str());
                if (!fout.good()) {
                        throw(my_exception(std::string("can't open file with name : ") + filename ));
                }
                std::copy(vec.begin(), vec.end(),
                          std::ostream_iterator<T>(fout, "\n"));
                std::cout << std::endl;
        }

        template <typename T>
        void read_vec_from_file(std::vector<T>& vec, const std::string& filename = "input")
        {
                std::ifstream fin;
                fin.open(filename.c_str());
                if (!fin.good()) {
                        throw(my_exception(std::string("can't open file with name :") + filename));
                }
                while (fin.good()) {
                        std::string tmp;
                        std::getline(fin, tmp);
                        if (!tmp.empty()) {
                                T i = atoi(tmp.c_str());
                                vec.push_back(i);
                        }
                }
        }

        void num_to_binary(const int num, std::vector<bool>&);

        int binary_to_num(const std::vector<bool>& bin);

        void align_binaries(std::vector<bool>& v1, std::vector<bool>& v2);

        void merge_count_inversions(std::vector<int>&, int, int, int, int&);

        void merge_sort_count_inversions(std::vector<int>&, int, int, int&);

        int count_inversions(const std::vector<int>& vec);

} // end of namespace utilities

#endif
