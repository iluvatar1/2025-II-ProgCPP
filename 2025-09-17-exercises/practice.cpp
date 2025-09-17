#include <cstdio>
#include <string>
#include <cmath>

long largest_prime(long num);

void nth_twin_primes(long n);

void nthpairs(void);

int main(int argc, char **argv)
{
    // nth_twin_primes(1);
    // nth_twin_primes(2);
    // nth_twin_primes(10);
    // nth_twin_primes(5098);

    nthpairs();

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

void nth_twin_primes(long n)
{
    int count = 0;
    for(int ii = 2; ; ii++) {
        if (isprime(ii) and isprime(ii+2)) {
            count++;
            if (count == n) {
                std::printf("(%d, %d)\n", ii, ii+2);
                break;
            }
        }
    }
}

void nthpairs(void)
{
    // debe imprimir la norma de las primeras 100 parejas de numeros primos gemelos
    int count = 0;
    for(int ii = 2; ; ii++) {
        if (isprime(ii) and isprime(ii+2)) {
            count++;
            std::printf("%d %25.16le\n", count, std::hypot(ii, ii+2));
            if (count == 100) {
                break;
            }
        }
    }
}
