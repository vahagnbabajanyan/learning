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
        userSettings(const std::string& userName);

        std::list<std::string> _dictionaries;
        std::list<std::string> _tests;
        std::string _user;
        std::string _password;
        std::string _level;
        std::string _stats;
};

} // end of namespace settings

#endif
