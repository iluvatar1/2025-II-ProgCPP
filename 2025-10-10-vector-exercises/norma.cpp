// calcula la norma de un vector
#include <print>
#include <cstdlib>
#include <cmath>
#include <vector>

// & : pasa por referencia, no creo nuevas variables, puedo 
// modificar al argumento original dentro de la funcion
// const: evita que lo modique

double compute_norm(const std::vector<double> & data); 
void fill(std::vector<double> & data);

int main (int argc, char *argv[])
{
    std::vector<double> array;
    array.resize(10);
    // fill
    fill(array);

    // compute norm
    double norma = compute_norm(array);
    std::println("{:25.16e}", norma);

    return 0;
}

void fill(std::vector<double> & data)
{
    for(int ii = 0; ii < data.size(); ++ii) {
        data[ii] = 2*ii + 1;
    }
}


double compute_norm(const std::vector<double> & data)
{
    // \sqrt{\sum x_i^2}
    double suma = 0.0;
    for(auto x : data) {
        suma += x*x;
    }
    return std::sqrt(suma);
}
