#include <string>

#include "user_settings.hpp"

namespace settings
{

        userSettings::userSettings(const std::string& userName)
                :_user(userName), _password(), _level(), _stats()
        {}

} //  end of namespace settings
