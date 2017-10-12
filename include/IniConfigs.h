/**
 *  IniConfigs.h
 *
 *  This is a simplest ini config parser
 *
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/IniConfigs
 */

#pragma once

#include "IniValue.h"
#include <map>


namespace vlm {

    class IniConfigs
    {
    public:
        /**
         *  Constructor
         *  @param      configuration file name
         */
        IniConfigs(const char* file_name);

        /**
         *  Get ini entry
         *  @param      config name
         *  @param      config default value
         *  @param      config value string must be not empty
         */
        template <typename T>
        IniValue<T> get(const std::string &name, const T &value, bool noEmpty = true) const
        {
            auto cfg = _map.find(name);
            // if key not exist
            if(cfg == _map.cend()) {
                return IniValue<T>(value);
            }

            // check if config value string is empty
            if(noEmpty && cfg->second.empty()) {
                return IniValue<T>(value);
            }
            
            return IniValue<std::string>(cfg->second);
        }

        /**
         *  Get ini entry
         *  @param      config name
         */
        template <typename T>
        IniValue<T> get(const std::string &name) const
        {
            auto cfg = _map.find(name);
            // if key not exist or config value string is empty return default
            if(cfg == _map.cend() || cfg->second.empty()) {
                return IniValue<T>(T());
            }
            
            return IniValue<std::string>(cfg->second);
        }
        
        ~IniConfigs() = default;
        
        /**
         *  Check file successfully opened
         */
        operator bool () const
        {
            return _isValid;
        }

    private:
        
        bool _isValid = true;
        std::map<std::string, std::string> _map;
    };

}
