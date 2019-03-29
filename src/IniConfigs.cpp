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
#include <functional>

namespace vlm {

    namespace {
        /**
         *  Trim spaces
         *  @param  string to trim
         */
        inline void trim(std::string &str)
        {
            // trim from start
            str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not_fn(std::ptr_fun<int, int>(std::isspace))));
            // trim from end
            str.erase(std::find_if(str.rbegin(), str.rend(), std::not_fn(std::ptr_fun<int, int>(std::isspace))).base(), str.end());
        }

        template<class InputIt, class UnaryPredicate>
        size_t _count_while(InputIt first, InputIt last, UnaryPredicate p)
        {
            size_t ret = 0;
            for (; first != last && p(*first); ++first) {
                ++ret;
            }
            return ret;
        }

        inline void trim(std::string_view &str)
        {
            size_t count;
            count = _count_while(str.begin(), str.end(), [](auto c) {return std::isspace(c);} );
            str.remove_prefix(std::min(count, str.size()));
            count = _count_while(str.rbegin(), str.rend(), [](auto c) {return std::isspace(c);} );
            str.remove_suffix(std::min(count, str.size()));
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
        while(std::getline(file, str)) {
            // trim
            trim(str);
            size_t pos = str.find('=');
            if( str.empty() ||  npos == pos ) {
                continue;
            }

            std::string_view key   (str.data(), pos);
            std::string_view value (str.data() + pos + 1, str.size() - pos - 1);

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

            _map[std::string(key)] = std::string(value);
        }

        return true;
    }

}
