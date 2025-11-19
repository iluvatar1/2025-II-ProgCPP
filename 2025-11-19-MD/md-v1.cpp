#include <iostream>
#include <valarray>
#include <vector>

// one bouncing particle 

struct Particle {
    std::valarray<double> R{0.0, 0.0, 0.0}, V{0.0, 0.0, 0.0}, F{0.0, 0.0, 0.0};
    double mass{0}, rad{0};
    void print(void);
};

void initial_conditions(std::vector<Particle> & bodies);

int main(void)
{
    int N = 1;
    std::vector<Particle> particles(N);

    // params

    // initial conditions
    initial_conditions(particles);
    particles[0].print();

    // loop over time
    //   compute forces
    //   time step integration
    //   constrains
    //   print info

    return 0;
}

// particle.cpp
void Particle::print(void) {
    std::cout << mass << "\t" << rad << "\t"
              << R[0] << "\t" << R[1] << "\t" << R[2] << "\t"
              << V[0] << "\t" << V[1] << "\t" << V[2] << "\t"
              << F[0] << "\t" << F[1] << "\t" << F[2] << "\t";
}

void initial_conditions(std::vector<Particle> & bodies)
{
    bodies[0].R[0] = 1.2345;
    bodies[0].R[1] = 2.9345;
    bodies[0].rad  = 0.2345;
    bodies[0].mass = 1.7345;
}
