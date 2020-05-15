#include <iostream>
#include <vector>

//case1: the type specifier is a pointer or reference, but not a universal reference
void testcase1() {
    auto x = 27;
    const auto& rx = x;
    const auto* px = &x;
    std::cout << "testcase1: =====================" << std::endl;
    std::cout << "rx lvalue: " << std::is_lvalue_reference<decltype(rx)>::value
    << ", rvalue: " << std::is_rvalue_reference<decltype(rx)>::value << std::endl;
    std::cout << "================================" << std::endl;
}

//case2: the type specifier is a universal reference
void testcase2() {
    auto x = 27;
    const auto cx = x;
    const auto& rx = x;
    auto&& uref1 = x;       //x is int and is a lvalue -> uref1's type is int&
    auto&& uref2 = cx;      //cx is const int and is a lvalue -> uref2's type is const int&
    auto&& uref3 = rx;      //rx is const int& and is a lvalue -> uref3's type is const int&
    auto&& uref4 = 27;      //27 is rvalue -> uref4's type is int&&

    std::cout << "testcase2: =====================" << std::endl;

    std::cout << "uref1 lvalue: " << std::is_lvalue_reference<decltype(uref1)>::value
    << ", rvalue: " << std::is_rvalue_reference<decltype(uref1)>::value << std::endl;
    std::cout << "uref2 lvalue: " << std::is_lvalue_reference<decltype(uref2)>::value
    << ", rvalue: " << std::is_rvalue_reference<decltype(uref2)>::value << std::endl;
    std::cout << "uref3 lvalue: " << std::is_lvalue_reference<decltype(uref3)>::value
    << ", rvalue: " << std::is_rvalue_reference<decltype(uref3)>::value << std::endl;
    std::cout << "uref4 lvalue: " << std::is_lvalue_reference<decltype(uref4)>::value
    << ", rvalue: " << std::is_rvalue_reference<decltype(uref4)>::value << std::endl;

    std::cout << "================================" << std::endl;
}

//case 3: the type specifier is neither a reference or pointer
void testcase3() {
    auto x = 27;            //x's type is int
    const auto cx = x;      //cx's type is const int
}

//how auto type deduction works on array
void testcase4() {
    const char name[] = "J. P. Briggs";
    auto arr1 = name;       //arr1's type is const char*
    auto& arr2 = name;      //arr2's type is const char (&)[13]
}

//how auto type deduction works on function
void someFunc(int, double) {
    return;
}

void testcase5() {
    auto func1 = someFunc;  //func1's type is void (*)(int, double)
    auto& func2 = someFunc; //func2's type is void (&)(int, double)
}

//braced initializers is the only way in which auto type deduction and template type deduction differ
template<typename T>
void f(T param) {
    return;
}

template<typename T>
void fsingle(std::initializer_list<T> param) {
    return;
}

void testcase6() {
    auto x = {11, 23, 9};   //x's type is std::initializer_list<int>
    // f({11, 23, 9});      //error since it's double in type deduction (one for T - initializer list and one for int value)
    fsingle({11, 23, 9});   //this thing works because it'single layer type deduction (T = int)
    //so the only difference is that auto assume braced initializer is std::initializer_list<T> and template doesn't
}

//this thing wont compile!!!!
// auto createInitList() {
//     return {11, 23, 9};
// }

void testcase7() {
    std::vector<int> v;
    auto resetV = [&v](const auto& newValue) {v = newValue;};
    auto resetV2 = [&v](const std::initializer_list<int>& newValue) {v = newValue;};
    // resetV({1, 2, 3});      //this thing wont compile!
    resetV2({1, 2, 3});      //this thing wont compile!
}

int main() {
    testcase1();
    testcase2();
    testcase3();
    testcase4();
    testcase5();
    testcase6();
    testcase7();
    return 0;
}

