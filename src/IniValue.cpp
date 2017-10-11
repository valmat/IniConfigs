/**
 *  IniValue.cpp
 *
 *  Class IniValue designed for extracting values from ini entries
 *  
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/inivalues
 */

#include "IniValue.h"
#include <algorithm>

namespace vlm {

    /**
     *  Casting to integer types
     */
    IniValue<std::string>::operator IniValue<uint64_t> () const {return std::strtoull(_value.c_str(), nullptr, 10);}
    IniValue<std::string>::operator IniValue<uint32_t> () const {return std::strtoul(_value.c_str(), nullptr, 10);}
    IniValue<std::string>::operator IniValue<uint16_t> () const {return std::strtoul(_value.c_str(), nullptr, 10);}
    IniValue<std::string>::operator IniValue<uint8_t>  () const {return std::strtoul(_value.c_str(), nullptr, 10);}

    IniValue<std::string>::operator IniValue<int64_t> () const {return std::stoll(_value);}
    IniValue<std::string>::operator IniValue<int32_t> () const {return std::stol(_value);}
    IniValue<std::string>::operator IniValue<int16_t> () const {return std::stoi(_value);}
    IniValue<std::string>::operator IniValue<int8_t>  () const {return std::stoi(_value);}

    /**
     *  Casting to float types
     */
    IniValue<std::string>::operator IniValue<float>       () const {return std::stof(_value);}
    IniValue<std::string>::operator IniValue<double>      () const {return std::stod(_value);}
    IniValue<std::string>::operator IniValue<long double> () const {return std::stold(_value);}

    /**
     *  Cast to a bool
     */
    IniValue<std::string>::operator IniValue<bool> () const
    {
        std::string v = _value;
        std::transform(v.begin(), v.end(), v.begin(), (int (*)(int))std::tolower);
        return ("true" == v || "1" == v || "on" == v);
    }
    
    /**
     *  Cast to a const char *
     */
    IniValue<std::string>::operator IniValue<const char *> () const
    {
        return _value.c_str();
    }

    std::ostream &operator<< (std::ostream &stream, const IniValue<std::string> &value)
    {
        return stream << value.toString();
    }
}
