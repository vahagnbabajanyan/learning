#ifndef _USER_CONF_HPP_
#define _USER_CONF_HPP_

#include <list>
#include <string>

namespace settings
{

class statistics
{
public:
        statistics(){}
};

struct userSettings
{
        enum Level
        {
                beginer = 0,
                intermediate = 1,
                pro = 2,
                expert = 3,
                invalid = 4
        };

        static std::string levelString(Level l);
        static Level levelFromString(const std::string&);

        userSettings(const std::string& userName);
        std::list<std::string> _dictionaries;
        std::list<std::string> _tests;
        std::string _user;
        std::string _password;
        Level _level;
        std::string _stats;
};

} // end of namespace settings

#endif
