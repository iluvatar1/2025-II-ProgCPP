// Implementar trapecio y simpson y comparar errores
// Se usara la funcion error para comparar

#include <functional>
#include <cmath>
#include <print>

using fptr = std::function<double(double)>; // f(x)
using algptr = std::function<double(double, double, int, fptr)>; // representa a forward_diff o central_diff

double f(double x);
double trapecio(double a, double b, int nintervals, fptr fun);
double simpson(double a, double b, int nintervals, fptr fun);
double richardson_int(double a, double b, int nsteps, 
                      int order, algptr alg, fptr fun);


int main(void)
{
    std::println("{:25.16e}", trapecio(0.0, 1.0, 10, f) );
    std::println("{:25.16e}", simpson(0.0, 1.0, 10, f) );
    std::println("{:25.16e}", richardson_int(0.0, 1.0, 10, 2, trapecio, f) );
    std::println("{:25.16e}", richardson_int(0.0, 1.0, 10, 4, simpson, f) );
    std::println("{:25.16e}", std::pow(std::sin(0.5), 2) );


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
    if (nintervals % 2 != 0) {
        nintervals += 1;
    }

    double deltax = (b-a)/nintervals;

    double suma1 = 0.0;
    for(int k = 1; k <= nintervals/2; k++) {
        double xk = a + (2*k-1)*deltax;
        suma1 = suma1 + fun(xk);
    }

    double suma2 = 0.0;
    for(int k = 1; k <= nintervals/2-1; k++) {
        double xk = a + (2*k)*deltax;
        suma2 = suma2 + fun(xk);
    }

    double suma = fun(a) + 4*suma1 + 2*suma2 + fun(b);

    return deltax*suma/3;
}

double richardson_int(double a, double b, int nsteps, 
                      int order, algptr alg, fptr fun)
{
    double aux1 = alg(a, b, 2*nsteps, fun);
    double aux2 = alg(a, b, nsteps, fun);
    double aux3 = std::pow(2.0, order);
    return (aux3*aux1 - aux2)/(aux3-1);
}
