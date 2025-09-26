#include <cmath>
#include <print>

double fun(double x);
double forward_diff(double x, double h);
double central_diff(double x, double h);

int main()
{
    double x = 1.2345;
    double exacto = std::cos(x);

    for (double h = 1.0e-16; h <= 1.0e-1; h = h*10.0) {
        double xf = std::fabs(1 - forward_diff(x, h)/exacto);
        double xc = std::fabs(1 - central_diff(x, h)/exacto);
        std::println("{:25.16e} {:25.16e} {:25.16e}", h, xf, xc);
    }

    return 0;
}

double fun(double x)
{
    return std::sin(x);
}

double forward_diff(double x, double h)
{
    return (fun(x+h) - fun(x))/h;
}

double central_diff(double x, double h)
{
    return (fun(x+h) - fun(x-h))/(2*h);
}
