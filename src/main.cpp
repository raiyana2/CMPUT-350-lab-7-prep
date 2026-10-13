
#include "pack.h"
#include <iostream>
#include <type_traits>

int main() {
    using MyPack = Pack<int, double, char, int>;

    // Test pack size
    static_assert(MyPack::size == 4);

    // Test index to type
    static_assert(std::is_same_v<MyPack::type<0>, int>);
    static_assert(std::is_same_v<MyPack::type<1>, double>);
    static_assert(std::is_same_v<MyPack::type<2>, char>);

    // Test type to index
    static_assert(MyPack::index<int> == 0);
    static_assert(MyPack::index<double> == 1);
    static_assert(MyPack::index<char> == 2);
    static_assert(MyPack::index<float> == -1);

    // Test empty pack
    static_assert(Pack<>::size == 0);
    static_assert(Pack<>::index<int> == -1);

    std::cout << "All tests passed!\n";

    return 0;
}
