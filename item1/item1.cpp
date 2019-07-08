#include <iostream>

// return size of an array as a compile-time constant. (The
// array parameter has no name, because we care only about
// the number of elements it contains.)
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept { //declaring this function constexpr makes its result available during compilation
	return N;
}

int main() 
{
    int keyVals[] = { 1, 3, 7, 9, 11, 22, 35 };
    std::cout << arraySize(keyVals) << std::endl;
    return 0;
}