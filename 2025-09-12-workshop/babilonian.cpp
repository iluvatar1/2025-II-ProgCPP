#include <cstdio>
#include <string>

double babilonian_root(double s, int iter);

int main(int argc, char **argv)
{
    int niter = std::stoi(argv[1]);
    double root = babilonian_root(2.0, niter);
    std::printf("%d %25.16le\n", niter, root);

    return 0;
}

double babilonian_root(double s, int iter)
{
    double x = 1.0;
    for(int ii = 0; ii < iter; ii++){
        x = (x + s/x)/2.0;
    }
    return x;
}