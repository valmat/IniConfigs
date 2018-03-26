/**
 *  IniConfigs.cpp
 *
 *  This is a simplest ini config parser
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
        
        std::string str;
        for(unsigned line = 1; std::getline(file, str); line++) {
            
            // remove comment
            size_t pos = str.find(';');
            if( std::string::npos > pos ) {
                str = str.substr( 0, pos );
            }
            
            // trim
            trim(str);
            
            if( str.empty() ) {
                continue;
            }
            
            // parse key and value
            pos = str.find('=');
            if( std::string::npos > pos ) {
                std::string key   = str.substr(  0, pos );
                std::string value = str.substr( pos+1, str.size() );
                trim(key);
                trim(value);
                
                _map[key] = value;
            } else {
                std::cerr << "IniConfigs: syntax error in line: " << line << " [file: " << file_name << "]" << std::endl;
                _isValid = false;
            }
        }
        return true;
    }

}
