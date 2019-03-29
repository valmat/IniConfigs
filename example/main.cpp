//#include <iostream>
//#include <fstream>
//#include <string>

#include "IniConfigs.h"

// When installed:
//#include <vlm/iniconfigs/IniConfigs.h>


using vlm::IniValue;
using vlm::IniValueString;

// Custom type:
struct A {
    A()          = default;
    A(const A &) = default;
    A(A &&)      = default;
    A(int x) : a(x) {}
    int a = 0;
};
// Casting custom type:
template<>
IniValueString::operator IniValue<A> () const {return A(std::stoi(this->toString()));}
// You can use _value instead of this->toString(), but
// using private property is bad way (though it is read only, because marked `const`):
//IniValueString::operator IniValue<A> () const {return A(std::stoi(_value));} 

const char * print_bool(bool v) {
    return v ? "Yes" : "No";
}

int main( int argc, char *argv[])
{
    vlm::IniConfigs cfg("test.ini");

    if(!cfg) {
        std::cerr << "Error with open file " << "test.ini" << std::endl;
        return 1;
    }

    const std::string name1("value1");
    const std::string name1_("value1_");
    int64_t val1  = cfg.get(name1,  5);
    int64_t val1_ = cfg.get(name1_, 5);

    std::cout << "[" << name1 << " ]: ["<< val1  << ']' << std::endl;
    std::cout << "[" << name1_ << "]: ["<< val1_ << ']' << std::endl;
    
    std::cout << cfg.get<std::string>("value2",  "default value") << std::endl;
    std::cout << cfg.get<std::string>("value2+", "default value") << std::endl;
    
    std::cout << cfg.get<std::string>("value3") << std::endl;
    std::cout << cfg.get<std::string>("value3+") << std::endl;

    std::cout.precision(25);
    std::cout << cfg.get("value3",  2.718281828459) << std::endl;
    std::cout << cfg.get("value3+", 2.718281828459) << std::endl;
    //std::cout << cfg.get("value3", nullptr) << std::endl;
    std::cout << cfg.get("value4",  2.718281828459) << std::endl;

    std::cout << "Has `value3`?  " << print_bool(cfg.has("value3")) << std::endl;
    std::cout << "Has `value3+`? " << print_bool(cfg.has("value3+")) << std::endl;

    std::cout << cfg.get<float>      ("value4",  2.718281828459) << std::endl;
    std::cout << cfg.get<double>     ("value4",  2.718281828459) << std::endl;
    std::cout << cfg.get<long double>("value4",  2.718281828459) << std::endl;

    auto value5 =  cfg.get<std::string>("value5", "value5");
    auto value6 =  cfg.get<std::string>("value6", "value6");
    std::cout << '[' << value5 << ']' << std::endl;
    std::cout << '[' << value6 << ']' << std::endl;

    std::cout << '[' << (std::string)cfg.get<std::string>("value7", "value7") << ']' << std::endl;
    std::cout << '[' << cfg.get<std::string>("value7", "value7").toString() << ']' << std::endl;
    std::cout << '[' << cfg.get<std::string>("value7", "value7") << ']' << std::endl;

    std::cout << '[' << cfg.get("value8", 0) << ']' << std::endl;
    std::cout << '[' << cfg.get("value8", size_t(0)) << ']' << std::endl;
    std::cout << '[' << cfg.get<size_t>("value8", 0) << ']' << std::endl;

    std::cout << '[' << print_bool(cfg.get("boolval0", false)) << ']' << std::endl;

    std::cout << '[' << print_bool(cfg.get("boolval1", false)) << ']' << std::endl;
    std::cout << '[' << print_bool(cfg.get("boolval2", false)) << ']' << std::endl;
    std::cout << '[' << print_bool(cfg.get("boolval3", false)) << ']' << std::endl;

    std::cout << '[' << print_bool(cfg.get("boolval4", true)) << ']' << std::endl;
    std::cout << '[' << print_bool(cfg.get("boolval5", true)) << ']' << std::endl;
    std::cout << '[' << print_bool(cfg.get("boolval6", true)) << ']' << std::endl;
    std::cout << '[' << print_bool(cfg.get("boolval7", true)) << ']' << std::endl;

    std::cout << "Is ini configs empty? " << print_bool(cfg.empty()) << std::endl;
    std::cout << "Ini entries number:  " << cfg.size() << std::endl;

    std::cout << '[' << cfg.get("value1",  A()).get().a << ']' << std::endl;
    std::cout << '[' << cfg.get("value1+", A()).get().a << ']' << std::endl;

    A a1 = cfg.get("value1",  A());
    A a2 = cfg.get("value1+", A());
    std::cout << '[' << a1.a << ']' << std::endl;
    std::cout << '[' << a2.a << ']' << std::endl;

    // The same
    A a3 = cfg.get<A>("value1");
    A a4 = cfg.get<A>("value1+");
    std::cout << '[' << a3.a << ']' << std::endl;
    std::cout << '[' << a4.a << ']' << std::endl;

    cfg.addFile("test1.ini");
    cfg.addFile("test2.ini");
    
    std::cout << "test1fv : " << cfg.get<int>("test1fv") << std::endl;
    std::cout << "test2fv : " << cfg.get<int>("test2fv") << std::endl;

    std::cout << '[' << cfg.get<std::string>("strval1") << ']' << std::endl;
    std::cout << '[' << cfg.get<std::string>("strval2") << ']' << std::endl;

    std::cout << '[' << cfg.get<std::string>("content_type1") << ']' << std::endl;
    std::cout << '[' << cfg.get<std::string>("content_type2") << ']' << std::endl;

    return 0;
}