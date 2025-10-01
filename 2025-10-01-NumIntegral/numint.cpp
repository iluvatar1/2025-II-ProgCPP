// Implementar trapecio y simpson y comparar errores
// Se usara la funcion error para comparar

#include <functional>
#include <cmath>


using fptr = std::function<double(double)>; // f(x)

double f(double x);
double trapecio(double a, double b, int nintervals, fptr fun);

/* ejercicio:
- Implementar la funcion main para imprimir 
la integral entre 0 y 1, con 10 intervalos
*/

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
