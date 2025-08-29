// mi primer programa, ya soy un hacker
#include <iostream>

int main()
{
    std::cout << "Hola Mundo\n" << 12345 << "\n";
    
    int a {2147483647};
    std::cout << a << "\n";

    bool flag = 4;
    std::cout << flag << "\n";

    double x = -9.87e307;
    std::cout << x << "\n"; 

    std::string str = "Hola mundo";
    std::cout << str << "\n"; // imprimir toda la cadena
    std::cout << str[0] << "\n"; // imprimir el primer caracter
    std::cout << str[1] << "\n"; 


    return 0;
}