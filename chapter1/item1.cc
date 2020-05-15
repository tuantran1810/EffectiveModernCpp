#include <iostream>

/*
Consider a function template looks like this:
template <typename T>
void f(ParamType param);
*/

//case 1: ParamType is a reference or pointer, but not a universial reference:
template <typename T>
void flvalue(T& param) {
    std::cout << "called to flvalue() of case 1 with lvalue reference, lvalue: " << std::is_lvalue_reference<decltype(param)>::value
    << ", rvalue: " << std::is_rvalue_reference<decltype(param)>::value << std::endl;
}

void testcase1() {
    int x = 27;
    const int cx = x;
    const int& rx = x;
    int&& rvx = std::move(x);
    flvalue(x);     //T is deduced to int and ParamType is deduced to int&
    flvalue(cx);    //T is deduced to const int and ParamType is deduced to const int&
    flvalue(rx);    //T is deduced to const int and ParamType is deduced to const int&
    flvalue(rvx);   //T is deduced to int and ParamType is deduced to int&
    //passing const object to template function taking T& parameter is safe, it remains the constaness of the parameter!
}

template<typename T>
void fpointer(T* param) {
    std::cout << "called to fpointer() of case 1 with pointer" << std::endl;
}

void testcase2() {
    int x = 27;
    const int* px = &x;
    fpointer(&x);   //T is deduced to int and ParamType is deduced to int*
    fpointer(px);   //T is deduced to const int and ParamType is deduced to const int*
}

//case 2: ParamType is a universal reference
template <typename T>
void fUniversalRef(T&& param) {
    std::cout << "called to fUniversalRef() of case 2 with universal reference, lvalue: " << std::is_lvalue_reference<decltype(param)>::value
    << ", rvalue: " << std::is_rvalue_reference<decltype(param)>::value << std::endl;
}

void testcase3() {
    int x = 27;
    const int cx = x;
    const int& rx = x;
    fUniversalRef(x);     //T is deduced to int& and ParamType is deduced to int&
    fUniversalRef(cx);    //T is deduced to const int& and ParamType is deduced to const int&
    fUniversalRef(rx);    //T is deduced to const int& and ParamType is deduced to const int&
    fUniversalRef(27);    //T is deduced to int and ParamType is deduced to int&&
}

//case 3: ParamType is neighter pointer or reference, ignore the const-ness, reference-ness and volatile
template <typename T>
void f_rest(T param) {
    std::cout << "called to f_rest() of case 3, lvalue: " << std::is_lvalue_reference<decltype(param)>::value
    << ", rvalue: " << std::is_rvalue_reference<decltype(param)>::value << std::endl;
}

void testcase4() {
    int x = 27;
    const int cx = x;
    const int& rx = x;

    //First const means this pointer points to a constant string
    //Second pointer means this pointer is a constant pointer and cannot be assigned to another value
    const char* const ptr = "Fun with pointer";
    f_rest(x);          //both T and ParamType are deduced to int
    f_rest(cx);         //both T and ParamType are deduced to int
    f_rest(rx);         //both T and ParamType are deduced to int
    f_rest(ptr);        //both T and ParamType are deduced to const char*
}

/*
Array types are difference from pointer types, although sometimes they seem interchangeable
In many contexts, an array decays into a pointer to its first element
*/

void myfunc1(int param[]) {
    return;
}

void myfunc2(int* param) {
    return;
}

//These two of myfunc() are the same

void testcase5() {
    const char name[] = "J. P. Briggs"; //type const char[13]
    const char* ptrToName = name; //name array decays to pointer, type const char*
    //ptrToName and name, these type are difference, but because of the array-to-pointer decay rule, the code compiles
    //The type of an array that's passes to a template function by value is deduced to be a pointer type
    f_rest(name);       //both T and ParamType are deduced to const char*
    //Although function cannot declare parameters that are truly array, it can declare parameters which are reference to arrays
    flvalue(name);      //Type deduced for T is actual type of array comes with size: const char [13], and the ParamType is const char (&)[13]
}

// Functions can be deduced to pointers also
void someFunc(int a, double b) { //type void(int, double)
    return;
}

void testcase6() {
    f_rest(someFunc);       //param is deduced as ptr-to-func, type void (*)(int, double)
    flvalue(someFunc);      //param is deduced as reference-to-func, type is void (&)(int, double)
}

// return size of an array as a compile-time constant. (The
// array parameter has no name, because we care only about
// the number of elements it contains.)
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept { //declaring this function constexpr makes its result available during compilation
    return N;
}

int main()
{
    testcase1();
    testcase2();
    testcase3();
    testcase4();
    testcase5();
    testcase6();
    int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };
    std::cout << arraySize(keyVals) << std::endl;
    return 0;
}