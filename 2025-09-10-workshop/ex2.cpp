// compute the sum of the digits of a number
#include <cstdio>
#include <string>

int sumdigits(long num);

int main(int argc, char **argv)
{
    long mynum = std::stol(argv[1]);
    std::printf("%d\n", sumdigits(mynum)); 

    return 0;
}

int sumdigits(long num)
{
    // convertir en cadena
    // por cada elemento dentro de la cadena, acumular la suma
    // retornar la suma
    std::string num_str = std::to_string(num);
    int suma = 0;
    for(char c: num_str) {
        suma = suma + (c - '0');
    }

    // // second version: using integers
    // // Use modulo and division to extract and sum digits.
    // // This is generally more efficient than string conversion.
    // while (num > 0) {
    //     suma += num % 10; // Get the last digit and add it to the sum
    //     num /= 10;        // Remove the last digit from the number
    // }    
    
    // num = 123 
    // 123%10 -> 3
    // num = 123/10 = 12
    // 12%10 -> 2
    // num = 12/10 -> 1
    // 1%10 -> 1
    // num = 1/10 -> 0

    return suma;
}
