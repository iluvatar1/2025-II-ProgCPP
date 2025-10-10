// calcula la norma de un vector
#include <print>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <random>

// & : pasa por referencia, no creo nuevas variables, puedo 
// modificar al argumento original dentro de la funcion
// const: evita que lo modique

double compute_norm(const std::vector<double> & data); 
double compute_pnorm(const std::vector<double> & data, int p); 
void fill(std::vector<double> & data);
void fill_random(std::vector<double> & data);
int argmax(const std::vector<double> & data);

int main (int argc, char *argv[])
{
    std::vector<double> array;
    array.resize(10);
    // fill
    fill_random(array);

    // compute norm
    double norma = compute_norm(array);
    std::println("{:25.16e}", norma);
    norma = compute_pnorm(array, 2);
    std::println("{:25.16e}", norma);

    // argmax
    std::println("{}", argmax(array));

    for(auto x : array) {
        std::print("{} ", x);
    }
    std::println();

    return 0;
}

void fill(std::vector<double> & data)
{
    for(int ii = 0; ii < data.size(); ++ii) {
        data[ii] = 2*ii + 1;
    }
}

void fill_random(std::vector<double> & data)
{
    std::mt19937 mt(1);  // genera los bits aleatorios
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    // fills the vector using random numbers 
    for(int ii = 0; ii < data.size(); ++ii) {
        data[ii] = dist(mt);
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

double compute_pnorm(const std::vector<double> & data, int p)
{
    // (\sum x_i^p)^{1/p}
    double suma = 0.0;
    for(auto x : data) {
        suma += std::pow(x, p);
    }
    return std::pow(suma, 1.0/p);
}

int argmax(const std::vector<double> & data)
{
    // asignar un valor inicial al maximo y a su indice
    // recorrer el arreglo
    // si encuentro uno mas grande, entonces 
    // cambio el valor del maximo y de su indice
    // return el indice del maximo
    int iimax = 0;
    double valmax = data[0];
    for(int ii = 0; ii < data.size(); ++ii) {
        if (data[ii] > valmax) {
            valmax = data[ii];
            iimax = ii;
        }
    }
    return iimax;
}
