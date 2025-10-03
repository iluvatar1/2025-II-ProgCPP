// Implementar trapecio y simpson y comparar errores
// Se usara la funcion error para comparar

#include <functional>
#include <cmath>
#include <print>
#include <fstream>
#include <vector>

using fptr = std::function<double(double)>; // f(x)
using algptr = std::function<double(double, double, int, fptr)>; // representa a forward_diff o central_diff

double f(double x);
double trapecio(double a, double b, int nintervals, fptr fun);
double simpson(double a, double b, int nintervals, fptr fun);
double richardson_int(double a, double b, int nsteps, 
                      int order, algptr alg, fptr fun);
double gauss2(double a, double b, fptr fun);
double gauss5(double a, double b, fptr fun);

int main(void)
{
    double exact = std::pow(std::sin(0.5), 2);
    double a = 0.0;
    double b = 1.0;

    std::ofstream fout("data.txt");

    int n = 5;
    double et = std::fabs(1.0 - trapecio(a, b, n, f)/exact );
    double es = std::fabs(1.0 - simpson(a, b, n, f)/exact );
    double etr = std::fabs(1.0 - richardson_int(a, b, n, 2, trapecio, f)/exact );
    double ets = std::fabs(1.0 - richardson_int(a, b, n, 4, simpson, f)/exact );
    double etg2 = std::fabs(1.0 - gauss2(a, b, f)/exact );
    double etg5 = std::fabs(1.0 - gauss5(a, b, f)/exact );
    std::println(fout, "{:10} {:25.16e} {:25.16e} {:25.16e} {:25.16e} {:25.16e} {:25.16e}", 
                n, et, es, etr, ets, etg2, etg5);
    fout.close();

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

double gauss2(double a, double b, fptr fun)
{
    // puntos de gauss
    double x0 = -1.0/std::sqrt(3);
    double x1 = +1.0/std::sqrt(3);
    // pesos 
    double w0 = 1.0;
    double w1 = 1.0;

    // aux
    double aux1 = (b-a)/2;
    double aux2 = (b+a)/2;

    // suma
    double suma = w0*fun(aux1*x0 + aux2) + w1*fun(aux1*x1 + aux2);

    return aux1*suma;
}

double gauss5(double a, double b, fptr fun)
{
    // puntos de gauss
    std::vector<double> x = {0.0000000000000000, -0.5384693101056831, 
                            0.5384693101056831, -0.9061798459386640, 
                            0.9061798459386640};
    // pesos 
    std::vector<double> w = {0.5688888888888889, 0.4786286704993665,
                             0.4786286704993665, 0.2369268850561891,
                             0.2369268850561891};

    // aux
    double aux1 = (b-a)/2;
    double aux2 = (b+a)/2;

    // suma
    double suma = 0.0;
    for (int ii = 0; ii < 5; ii++) {
        suma = suma + w[ii]*fun(aux1*x[ii] + aux2);
    }

    return aux1*suma;
}