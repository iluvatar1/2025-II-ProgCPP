#include <cstdio>
#include <string>
#include <cmath>

long largest_prime(long num);
bool isprime(long n);

int main(int argc, char **argv)
{
    long number = std::stol(argv[1]);
    std::printf("%ld\n", largest_prime(number));


    return 0;
}

long largest_prime(long num)
{
    // comienzo a mirar todos los numeros desde num hasta 2
    // si uno de ellos es primo, inmediatamente paro y lo rtorno
    for(int ii = num; ii > 1; ii--) {
        if (isprime(ii)) {
            return ii;
        }
    }
}

bool isprime(long n)
{
    // para todos los numeros menores a n
    // vrificar si ese numero es divisor de n
    // si es divisor: n no es primo
    if (n == 2) { 
        return true;
    }
    bool flag = true;
    //for(long ii = 2; ii < n ; ++ii) {
    for(long ii = 2; ii <= std::sqrt(n)+1 ; ++ii) {
        if (n%ii == 0) { // encontre un divisor
            flag = false;
            break;
        }
    }
    return flag;
}