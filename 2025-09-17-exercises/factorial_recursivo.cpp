#include <cstdio>
#include <string>
#include <cmath>

long factorial(long n);
long fibonacci(long n);

int main(int argc, char **argv)
{
    std::printf("%ld\n", fibonacci(50));
    return 0;
}

long factorial(long n) 
{
    //n! = n*(n-1)*(n-2)*...*2*1
    //n! = n*(n-1)!
    if (n == 1) return 1;
    return n*factorial(n-1);
}

long fibonacci(long n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

