#include <string>
#include <algorithm>
#include <iostream>

void reverseSymbols(std::string& s, size_t first, size_t last)
{
        int size = last - first;
        for (int i = 0; i < size / 2; ++i) {
                char tmp = s[first + i];
                s[first + i] = s[last - i - 1];
                s[last - i - 1] = tmp;
        }
}

void reverse(std::string& s)
{
        reverseSymbols(s, 0, s.size());
        size_t first = 0, last = 0;
        last = s.find_first_of(" ");
        while (std::string::npos != last) {
                reverseSymbols(s, first, last);
                first = last + 1;
                last = s.find_first_of(" ", first);
        }
        if (!s.substr(first).empty()) {
                reverseSymbols(s, first, s.size());
        }
}

int main()
{
        std::string s = "hello world how are you";

        std::cout << s << std::endl;

        reverse(s);
        
        std::cout << s << std::endl;
}
