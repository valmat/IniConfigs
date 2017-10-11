//#include <iostream>
//#include <fstream>
//#include <string>

//#include "IniValue.h"
#include "IniConfigs.h"

//using namespace std;
const char *print_bool(bool v) {
    return v ? "Yes" : "No";
}

int main( int argc, char *argv[])
{
    
    vlm::IniConfigs cfg("test.ini");

    if(!cfg) {
        std::cerr<<"Error with open file "<< "test.ini" << std::endl;
        return 1;
    }

    const std::string name1("value1");
    const std::string name1_("value1_");
    //int64_t val = cfg.get<int64_t>(name, 5);
    int64_t val1  = cfg.get(name1,  5);
    int64_t val1_ = cfg.get(name1_, 5);

    std::cout << "[" << name1 << " ]: ["<< val1  << ']' << std::endl;
    std::cout << "[" << name1_ << "]: ["<< val1_ << ']' << std::endl;
    
    std::cout << cfg.get<const char *>("value2",  "default value") << std::endl;
    std::cout << cfg.get<const char *>("value2+", "default value") << std::endl;
    //std::cout << cfg.get<const char *>("value2++", nullptr)        << std::endl;

    //std::cout << cfg.get("value3") << std::endl;
    //std::cout << cfg.get("value3+", 2.718281828459)        << std::endl;

    //std::cout << cfg.get<std::string>("value4", "value4")        << std::endl;
    std::cout << '[' << cfg.get<const char *>("value5", "value5") << ']' << std::endl;
    std::cout << '[' << cfg.get<const char *>("value6", "value6") << ']' << std::endl;
    //std::cout << '[' << cfg.get("value7", "value7") << ']' << std::endl;

    std::cout << '[' << cfg.get("value8", 0) << ']' << std::endl;
    std::cout << '[' << cfg.get("value8", size_t(0)) << ']' << std::endl;
    std::cout << '[' << cfg.get<size_t>("value8", 0) << ']' << std::endl;



    //std::cout << std::endl << cfg.get<bool>("keyword3", 5) << std::endl;
    //std::cout << std::endl << cfg.get<size_t>("name3", 4444) << std::endl;

    std::cout << '[' << print_bool(cfg.get("boolval0", false)) << ']' << std::endl;

    std::cout << '[' << print_bool(cfg.get("boolval1", false)) << ']' << std::endl;
    std::cout << '[' << print_bool(cfg.get("boolval2", false)) << ']' << std::endl;
    std::cout << '[' << print_bool(cfg.get("boolval3", false)) << ']' << std::endl;

    std::cout << '[' << print_bool(cfg.get("boolval4", true)) << ']' << std::endl;
    std::cout << '[' << print_bool(cfg.get("boolval5", true)) << ']' << std::endl;
    std::cout << '[' << print_bool(cfg.get("boolval6", true)) << ']' << std::endl;
    std::cout << '[' << print_bool(cfg.get("boolval7", true)) << ']' << std::endl;

    return 0;
}

