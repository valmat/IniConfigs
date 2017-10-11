# IniConfigs

## Usage

```cpp
vlm::IniConfigs cfg("test.ini");

if(!cfg) {
    std::cerr<<"Error with open file "<< "test.ini" << std::endl;
    return 1;
}

// in test.ini
// value1 = 1  ; value1 setted as 1
// ;value1+ = 1 ;value1+ is skipped
int64_t defaultValue1 = 5;
int64_t value1        = cfg.get("value1",  defaultValue1); // 1
int64_t value1_       = cfg.get("value1+", defaultValue1); // 5
// You can specify type, but that is not required:
int64_t value1__      = cfg.get<int64_t>("value1",  defaultValue1); // 1

// in test.ini
// value2 = hello world		;value2 comment
// ;value2+ is skipped
std::cout << cfg.get<const char *>("value2",  "default value") << std::endl;
std::cout << cfg.get<const char *>("value2+", "default value") << std::endl;

// in test.ini
// value4 = 3.14159263358979361680130282241663053355296142399311
std::cout << cfg.get<float>      ("value4",  2.718281828459) << std::endl;
std::cout << cfg.get<double>     ("value4",  2.718281828459) << std::endl;
std::cout << cfg.get<long double>("value4",  2.718281828459) << std::endl;


// in test.ini
// boolval1 = on
// boolval2 = 1
// boolval3 = true
// boolval4 = off
// boolval5 = 0
// boolval6 = false
// boolval7 = any else
auto boolval0 = cfg.get("boolval0", false); // true
auto boolval1 = cfg.get("boolval1", false); // true
auto boolval2 = cfg.get("boolval2", false); // true
auto boolval3 = cfg.get("boolval3", false); // true
auto boolval4 = cfg.get("boolval4", true);  // false
auto boolval5 = cfg.get("boolval5", true);  // false
auto boolval6 = cfg.get("boolval6", true);  // false
auto boolval7 = cfg.get("boolval7", true);  // false
```
You can define your custom custing

```cpp
#include "IniConfigs.h"
using vlm;

// Custom casting
struct A {
    A() = default;
    A(int x) : a(x) {}
    int a = 0;
};

template<>
IniValueString::operator IniValue<A> () const {
  return A(std::stoi(this->toString()));
}

int main( int argc, char *argv[])
{
    vlm::IniConfigs cfg("test.ini");
    // in test.ini
    // value1 = 1
    std::cout << cfg.get("value1",  A()).get().a << std::endl; // 1
    std::cout << cfg.get("value1+", A()).get().a << std::endl; // 0

    return 0;
}
```
See [example](example)
