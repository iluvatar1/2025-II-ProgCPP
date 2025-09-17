#include <cstdio>
#include <string>
#include <cmath>

long largest_prime(long num);

void sexy_primes(long n);

int main(int argc, char **argv)
{
    // nth_twin_primes(1);
    // nth_twin_primes(2);
    // nth_twin_primes(10);
    // nth_twin_primes(5098);
    sexy_primes(20);

    return 0;
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

void sexy_primes(long n)
{
    for(int ii = 2; ii <= n; ii++) {
        if (isprime(ii) and isprime(ii+6)) {
                std::printf("(%d, %d)\n", ii, ii+6);
            }
    }
}
