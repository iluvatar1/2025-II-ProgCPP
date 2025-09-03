#include <iostream>
#include <cstdio>
#include <print>

int main() {
    int x = 42;

    // std::cout (type-safe, streams)
    std::cout << "Value: " << x << "\n";

    // std::printf (C-style, format strings)
    std::printf("Value: %d\n", x);

    // std::print (C++23, type-safe + format strings)
    std::print("Value: {}\n", x);
}