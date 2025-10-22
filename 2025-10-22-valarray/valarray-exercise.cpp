#include <print>
#include <valarray>
#include <cmath>
#include <algorithm>
#include <numeric>

int main(void)
{
    const int N = 1000;

    std::valarray<double> x(N);

    // fill it
    const double XMIN = 0.0;
    const double XMAX = 2*M_PI;
    const double DX = (XMAX-XMIN)/N;
    // x_i = xmin + i*dx 
    std::iota(std::begin(x), std::end(x), 0.0);
    x *= DX;
    x += XMIN;

    // compute sin
    std::valarray<double> y = std::sin(x);

    // filter
    auto mask = -0.5 < y and y < 0.5;
    std::valarray<double> xnew = x[mask];
    std::valarray<double> ynew = y[mask];

    // print
    for(auto val : ynew) {
        std::print("{} ", val);
    }

    return 0;
}