#include <cmath>
#include <print>
#include <fstream> // para imprimir a archivo
#include <functional>

using funptr = std::function<double(double)>;
using algptr = std::function<double(double, double, funptr)>; // representa a forward_diff o central_diff

double f(double x);
double forward_diff(double x, double h, funptr fun);
double central_diff(double x, double h, funptr fun);
double richardson_diff(double x, double h, int n, algptr alg, funptr fun);



int main()
{
    double x = 1.2345;
    double exacto = std::cos(x);

    // crear un file stream
    std::ofstream fout("data.txt");

    for (double h = 1.0e-16; h <= 1.0e-1; h = h*10.0) {
        double xf = std::fabs(1 - forward_diff(x, h, f)/exacto);
        double xc = std::fabs(1 - central_diff(x, h, f)/exacto);
        double xrf = std::fabs(1 - richardson_diff(x, h, 1, forward_diff, f)/exacto);
        double xrc = std::fabs(1 - richardson_diff(x, h, 2, central_diff, f)/exacto);
        std::println(fout, "{:25.16e} {:25.16e} {:25.16e} {:25.16e} {:25.16e}", h, xf, xc, xrf, xrc);
    }

    fout.close(); // cerrar el stream

    return 0;
}

double f(double x)
{
    return std::sin(x);
}

double forward_diff(double x, double h, funptr fun)
{
    return (fun(x+h) - fun(x))/h;
}

double central_diff(double x, double h, funptr fun)
{
    return (fun(x+h) - fun(x-h))/(2*h);
}

double richardson_diff(double x, double h, int n, algptr alg, funptr fun)
{
    double aux1 = alg(x, h/2, fun);
    double aux2 = alg(x, h, fun);
    double aux3 = std::pow(2.0, n);
    return (aux3*aux1 - aux2)/(aux3-1);
}
