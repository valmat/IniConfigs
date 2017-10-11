/**
 *  IniValue.h
 *
 *  Class IniValue designed for extracting values from ini entries
 *  
 *  @author valmat <ufabiz@gmail.com>
 *  @github https://github.com/valmat/inivalues
 */

#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>

namespace vlm {

    template <typename T>
    class IniValue
    {
    public:
        /**
         *  Constructors
         *  @param      default value
         */
        IniValue(const T &value) : _value(value) {}
        IniValue(T &&value) : _value(std::move(value)) {}

        /**
         *  Cast to an object of type T
         */
        operator T () const
        {
            return _value;
        }
        
    private:

        /**
         *  default value
         */
        T _value;
    };


    template<> 
    class IniValue<std::string>
    {
    public:
        
        /**
         *  Constructors
         *  @param      string value
         */
        IniValue(const std::string &value) : _value(value) {}
        IniValue(std::string &&value) : _value(std::move(value)) {}

        /**
         *  Cast to a string
         */
        operator std::string () const
        {
            return _value;
        }
        std::string toString () const
        {
            return _value;
        }

        /**
         *  Casting to integer types
         */
        operator IniValue<uint64_t> () const;
        operator IniValue<uint32_t> () const;
        operator IniValue<uint16_t> () const;
        operator IniValue<uint8_t>  () const;

        operator IniValue<int64_t> () const;
        operator IniValue<int32_t> () const;
        operator IniValue<int16_t> () const;
        operator IniValue<int8_t>  () const;

        /**
         *  Casting to float types
         */
        operator IniValue<float>       () const;
        operator IniValue<double>      () const;
        operator IniValue<long double> () const;

        /**
         *  Cast to a bool
         */
        operator IniValue<bool> () const;
        
        /**
         *  Cast to a const char *
         */
        operator IniValue<const char *> () const;

    private:
        
        /**
         *  string value
         */
        std::string _value;
    };

    std::ostream &operator<< (std::ostream &, const IniValue<std::string> &);
}
