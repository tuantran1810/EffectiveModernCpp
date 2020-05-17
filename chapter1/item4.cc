#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

template<typename T>
class TypeDisplayer;

void testcase1() {
    const int answer = 42;
    auto x = answer;    //x is an int
    auto y = &answer;   //y us a const int*

    //The following 2 lines cannot be compiled but will show us the type of x and y
    // TypeDisplayer<decltype(x)> xType;
    // TypeDisplayer<decltype(y)> yType;

    //In runtime, we can use the following way to show type name
    std::cout << "testcase1: =====================" << std::endl;
    std::cout << "x type: " << typeid(x).name() << std::endl;
    std::cout << "y type: " << typeid(y).name() << std::endl;
    std::cout << "================================" << std::endl;
}

struct Widget
{
    int tmp;
    Widget(int i): tmp(i) {}
};

template<typename T>
void f(const T& param) {
    std::cout << "T =       " << typeid(T).name() << std::endl;
    std::cout << "param =   " << typeid(param).name() << std::endl;
    return;
}

template<typename T>
void f_boost(const T& param) {
    using std::cout;
    using boost::typeindex::type_id_with_cvr;

    cout << "T =        " << type_id_with_cvr<T>().pretty_name() << std::endl;
    cout << "param =    " << type_id_with_cvr<decltype(param)>().pretty_name() << std::endl;
}

std::vector<Widget> createVec() {
    return std::vector<Widget>{Widget(1)};
}

void testcase2() {
    std::cout << "testcase1: =====================" << std::endl;
    const auto vw = createVec();
    if (!vw.empty()) {
        //the type results printed from this function is not proper
        //the type should be returned is const Widget* const &
        f(&vw[0]);
        f_boost(&vw[0]);
    }
    std::cout << "================================" << std::endl;
}

int main() {
    testcase1();
    testcase2();
    return 0;
}
