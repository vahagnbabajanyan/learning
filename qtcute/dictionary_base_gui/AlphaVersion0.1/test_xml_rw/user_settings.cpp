#include "user_settings.hpp"

#include <string>

namespace settings
{

userSettings::userSettings(const std::string& userName)
        : _user(userName),
          _password(),
          _level(invalid),
          _stats()
{}

std::string userSettings::levelString(Level l)
{
        switch(l)
        {
                case beginer:
                        return "beginer";
                        break;
                case intermediate:
                        return "intermediate";
                        break;
                case pro:
                        return "pro";
                        break;
                case expert:
                        return "expert";
                        break;
                case invalid:
                        return "";
        }
        return "";
}

userSettings::Level userSettings::levelFromString(const std::string& l)
{
        if ("beginer" == l ) {
                return beginer;
        } else if ("intermediate" == l ) {
                return intermediate;
        } else if ("pro" == l ) {
                return pro;
        } else if ("expert" == l) {
                return expert;
        }
        return invalid;
}

} // end of namespace settings
