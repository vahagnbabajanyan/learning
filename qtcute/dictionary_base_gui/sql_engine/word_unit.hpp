#ifndef _WORD_UNIT_HPP_
#define _WORD_UNIT_HPP_

#include <string>

struct wordUnit
{
        wordUnit(const std::string& key,
                 const std::string& transl,
                 const std::string& phr,
                 const std::string& sent)
                : _key(key),
                  _translations(transl),
                  _phrases(phr),
                  _sentence(sent)
        {}

        std::string _key;
        std::string _translations;
        std::string _phrases;
        std::string _sentence;
};

#endif
