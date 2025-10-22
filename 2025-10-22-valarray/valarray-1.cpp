#include <print>
#include <valarray>
#include <cmath>

int main()
{
    std::valarray<int> v = {1,2,3,4,5,6,7,8,9,10};

    // apptainer exec /tmp/gcc15.sif g++ -std=c++23 -fsanitize=address valarray-1.cpp 
    // std::println("{}", v);

    double suma = v.sum();

    std::println("{}", suma);

    return 0;
}