/**
 *  IniConfigs.cpp
 *
 *  Ini config parser
 *
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/IniConfigs
 */

#include "IniConfigs.h"
#include <algorithm>

namespace vlm {

    namespace {
        /**
         *  Trim spaces
         *  @param  string to trim
         */
        inline void trim(std::string &str)
        {
            // trim from start
            str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
            // trim from end
            str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
        }
    }

    // add ini-file
    bool IniConfigs::addFile(const std::string &file_name)
    {
        std::ifstream file(file_name, std::ios::in | std::ios::binary);
        if(!file) {
            return false;
        }

        auto &npos = std::string::npos;
        
        std::string str;
        for(unsigned line = 1; std::getline(file, str); line++) {
            // trim
            trim(str);
            size_t pos = str.find('=');
            if( str.empty() ||  npos == pos ) {
                continue;
            }

            std::string key   = str.substr( 0, pos );
            std::string value = str.substr( pos+1);

            // remove comment
            {
                size_t lqpos = value.find_first_of ('"');
                size_t rqpos = value.find_last_of  ('"');
                pos          = value.find_last_of(';');

                if( npos > pos && (npos == lqpos || (lqpos < rqpos && rqpos < pos)) ) {
                    value = value.substr( 0, pos );
                }
            }

            trim(key);
            trim(value);

            // Expand quotes
            if(value.size() > 1 && '"' == value[0] && '"' == value[value.size()-1]) {
                value = value.substr(1, value.size()-2);
            }
            
            // _map.emplace(key, value);
            _map[key] = value;
        }
        return true;
    }

}
