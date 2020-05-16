#include <iostream>
#include <vector>

//For C++11 we have to use trailing return type syntax
template<typename Container, typename Index>
auto authAndAccess1(Container& c, Index i) -> decltype(c[i]) {
    return c[i];
}

//allowed in C++14 to not use trailing return type
template<typename Container, typename Index>
auto authAndAccess2(Container& c, Index i) {
    return c[i];
}

//authAndAccess2() return a new object of Container item, auto deduction ignores the reference-ness of the expression
//authAndAccess3() returns exactly whatever c[i] returns (reference to the object if container is std::vector or std::deque)
template<typename Container, typename Index>
decltype(auto) authAndAccess3(Container& c, Index i) {
    return c[i];
}

//If we need to pass rvalue reference to the function
template<typename Container, typename Index>
decltype(auto) authAndAccess4(Container&& c, Index i) {
    std::cout << "c lvalue: " << std::is_lvalue_reference<decltype(c)>::value
    << ", c rvalue: " << std::is_rvalue_reference<decltype(c)>::value << std::endl;
    return std::forward<Container>(c)[i];
}

//equivalent to authAndAccess4 on C++11
template<typename Container, typename Index>
auto authAndAccess5(Container&& c, Index i) -> decltype(std::forward<Container>(c)[i]) {
    return std::forward<Container>(c)[i];
}

void testcase1() {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::cout << "testcase1: =====================" << std::endl;

    std::cout << "authAndAccess1 lvalue: " << std::is_lvalue_reference<decltype(authAndAccess1(v, 2))>::value
    << ", authAndAccess1 rvalue: " << std::is_rvalue_reference<decltype(authAndAccess1(v, 2))>::value << std::endl;

    std::cout << "authAndAccess2 lvalue: " << std::is_lvalue_reference<decltype(authAndAccess2(v, 2))>::value
    << ", authAndAccess2 rvalue: " << std::is_rvalue_reference<decltype(authAndAccess2(v, 2))>::value << std::endl;

    std::cout << "authAndAccess3 lvalue: " << std::is_lvalue_reference<decltype(authAndAccess3(v, 2))>::value
    << ", authAndAccess3 rvalue: " << std::is_rvalue_reference<decltype(authAndAccess3(v, 2))>::value << std::endl;

    std::cout << "================================" << std::endl;
}

void testcase2() {
    int x = 27;
    const int& cx = x;
    auto ax = cx;               //ax's type is int
    decltype(auto) adx = cx;    //adx's type is const int&

    std::cout << "testcase2: =====================" << std::endl;

    std::cout << "ax lvalue: " << std::is_lvalue_reference<decltype(ax)>::value
    << ", ax rvalue: " << std::is_rvalue_reference<decltype(ax)>::value << std::endl;

    std::cout << "adx lvalue: " << std::is_lvalue_reference<decltype(adx)>::value
    << ", adx rvalue: " << std::is_rvalue_reference<decltype(adx)>::value << std::endl;

    std::cout << "================================" << std::endl;
}

void testcase3() {
    std::vector<int> v1{1, 2, 3, 4, 5};
    std::vector<int> v2{1, 2, 3, 4, 5};
    std::vector<int> v3{1, 2, 3, 4, 5};
    std::cout << "testcase3: =====================" << std::endl;
    std::cout << "authAndAccess4 lvalue: " << std::is_lvalue_reference<decltype(authAndAccess4(std::move(v1), 2))>::value
    << ", authAndAccess4 rvalue: " << std::is_rvalue_reference<decltype(authAndAccess4(std::move(v2), 2))>::value << std::endl;
    std::cout << "================================" << std::endl;
}
//decltype((x)) return int&
void testcase4() {
    int x = 0;
    std::cout << "testcase4: =====================" << std::endl;
    std::cout << "decltype(x) lvalue: " << std::is_lvalue_reference<decltype(x)>::value
    << ", decltype(x) rvalue: " << std::is_rvalue_reference<decltype(x)>::value << std::endl;
    std::cout << "decltype((x)) lvalue: " << std::is_lvalue_reference<decltype((x))>::value
    << ", decltype((x)) rvalue: " << std::is_rvalue_reference<decltype((x))>::value << std::endl;
    std::cout << "================================" << std::endl;
}

//return type is int
decltype(auto) f1() {
    int x = 0;
    return x;
}

//return type is int& -> dangle, return reference to local variable
// decltype(auto) f2() {
//     int x = 0;
//     return (x);
// }

int main() {
    testcase1();
    testcase2();
    testcase3();
    testcase4();
    return 0;
}

