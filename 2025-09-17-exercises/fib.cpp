#include <cstdio>
#include <string>
#include <cmath>

long sum_fibonacci(long n);

int main(int argc, char **argv)
{
    std::printf("%ld\n", sum_fibonacci(300000));
    //sum_fibonacci(30);
    return 0;
}

long sum_fibonacci(long n)
{
    long suma = 0;
    long a = 0; 
    long b = 1; 
    for(int ii = 2; ; ii++) {
        long c = a + b;
        if (c > n) {
            break;
        }
        if (c%2 == 1){ 
            suma += c;
        }
        std::printf("%d ", c);
        a = b;
        b = c;
    }
    return suma;
}

