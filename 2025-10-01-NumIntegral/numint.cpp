// Implementar trapecio y simpson y comparar errores
// Se usara la funcion error para comparar

#include <functional>
#include <cmath>
#include <print>

using fptr = std::function<double(double)>; // f(x)

double f(double x);
double trapecio(double a, double b, int nintervals, fptr fun);
double simpson(double a, double b, int nintervals, fptr fun);

/* ejercicio:
implementar simpson
*/

int main(void)
{
    std::println("{:25.16e}", trapecio(0.0, 1.0, 10, f) );
    std::println("{:25.16e}", simpson(0.0, 1.0, 10, f) );

    return 0;
}


double f(double x)
{
    return x*std::sin(x*x);
}


double trapecio(double a, double b, int nintervals, fptr fun)
{
    double deltax = (b-a)/nintervals;
    double suma = 0.0;
    for(int k = 1; k <= nintervals - 1; k++) {
        double xk = a + k*deltax;
        suma = suma + fun(xk);
    }
    suma = suma + fun(a)/2 + fun(b)/2;

    return deltax*suma;
}

double simpson(double a, double b, int nintervals, fptr fun)
{
    
}