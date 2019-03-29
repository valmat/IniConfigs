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


                // std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
                // std::cerr << "\n\n\n" << value << std::endl;


                // std::cerr << "rqpos = " << rqpos << std::endl;
                // std::cerr << "pos   = " << pos << std::endl;

                // std::cerr << "(npos > pos)    " << ( (npos > pos)    ? 'Y':'N' ) << std::endl;
                // std::cerr << "(npos == lqpos) " << ( (npos == lqpos) ? 'Y':'N' ) << std::endl;
                // std::cerr << "(lqpos < rqpos) " << ( (lqpos < rqpos) ? 'Y':'N' ) << std::endl;
                // std::cerr << "(rqpos < pos)   " << ( (rqpos < pos)   ? 'Y':'N' ) << std::endl;


                if( npos > pos &&
                    (npos == lqpos || (lqpos < rqpos && rqpos < pos))
                ) {
                    value = value.substr( 0, pos );
                }

                // std::cerr << "\n[" << value<< "]" << std::endl;
                // std::cerr << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
            }

            // pos = value.rfind('"');
            // // pos = value.rfind(';', (npos == pos) ? npos : pos+1);
            // pos = value.rfind(';');
            // size_type ( const basic_string& str, size_type pos = npos ) const;
            // if( npos > pos ) {
            //     value = value.substr( 0, pos );
            // }

            trim(key);
            trim(value);


            // Expand quotes
            if(value.size() > 1 && '"' == value[0] && '"' == value[value.size()-1]) {
                value = value.substr(1, value.size()-2);
            }
            
            // _map.emplace(key, value);
            _map[key] = value;




/*

            // remove comment
            size_t pos = str.find(';');
            if( npos > pos ) {
                str = str.substr( 0, pos );
            }
            
            // trim
            trim(str);
            
            if( str.empty() ) {
                continue;
            }
            
            // parse key and value
            pos = str.find('=');
            if( npos > pos ) {
                std::string key   = str.substr(  0, pos );
                std::string value = str.substr( pos+1, str.size() );

                trim(key);
                trim(value);

                if(value.size() > 1 && '"' == value[0] && '"' == value[value.size()-1]) {
                    value = value.substr(1, value.size()-2);
                }
                
                _map[key] = value;
            } else {
                std::cerr << "IniConfigs: syntax error in line: " << line << " [file: " << file_name << "]" << std::endl;
                _isValid = false;
            }
*/

        }
        return true;
    }

}
