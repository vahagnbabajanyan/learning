#ifndef _APP_SETTINGS_HPP_
#define _APP_SETTINGS_HPP_

#include <string>

namespace settings {

struct appSettings
{
        appSettings()
                : _url()
        {}
        std::string _url;
};

} // end of namespace settings

#endif
