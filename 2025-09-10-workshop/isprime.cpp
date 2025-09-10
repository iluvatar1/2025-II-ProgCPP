#include <cstdio>
#include <cmath>

bool isprime(long n);

int main()
{
    std::printf("%d\n", isprime(20000000089));
    std::printf("%d\n", isprime(2));
    std::printf("%d\n", isprime(11));
    std::printf("%d\n", isprime(5));
    std::printf("%d\n", isprime(8));
    std::printf("%d\n", isprime(999));

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
