#include <iostream>
#include <valarray>
#include <vector>
#include <map>
#include <string>

// one bouncing particle 

struct Particle {
    std::valarray<double> R{0.0, 0.0, 0.0}, V{0.0, 0.0, 0.0}, F{0.0, 0.0, 0.0};
    double mass{0}, rad{0};
    void print(void);
};

void initial_conditions(std::vector<Particle> & bodies);
void compute_forces(std::vector<Particle> & bodies, std::map<std::string, double>& par);
void time_step(std::vector<Particle> & bodies, std::map<std::string, double>& par);
void start_integration(std::vector<Particle> & bodies, std::map<std::string, double>& par);


int main(void)
{
    int N = 1;
    std::vector<Particle> particles(N);

    // params
    std::map<std::string, double> params;
    params["T0"] = 0.0;
    params["TF"] = 30.0;
    params["DT"] = 0.1;
    params["G"] = 9.81;
    params["K"] = 201.9876;
    params["B"] = 0.0;//2.76554;
    params["LX"] = 3.78;

    // initial conditions
    initial_conditions(particles);
    start_integration(particles, params);


    // loop over time
    for (double t = params["T0"]; t <= params["TF"]; t = t + params["DT"]) {
        //   compute forces
        compute_forces(particles, params);
        //   time step integration        
        time_step(particles, params);
        //   constrains
        //   print info
        std::cout << t << " ";
        particles[0].print();
        std::cout << "\n";
    }

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
    bodies[0].V[0] = 1.5345;
    bodies[0].rad  = 0.2345;
    bodies[0].mass = 1.7345;
}

void compute_forces(std::vector<Particle> & bodies, std::map<std::string, double>& par)
{
    // reset all forces
    for(auto & p: bodies) {
        p.F = 0;
    }

    // add gravity
    for(auto & p: bodies) {
        p.F[1] += -par["G"]*p.mass;
    }

    // bounce on the floor
    for(auto & p: bodies) {
        double delta = p.rad - p.R[1]; // floor is on y = 0
        if (delta > 0) {
            p.F[1] += par["K"]*delta - par["B"]*p.mass*p.V[1];
        }
    }

    // left wall
    for(auto & p: bodies) {
        double delta = p.rad - p.R[0]; 
        if (delta > 0) {
            p.F[0] += par["K"]*delta - par["B"]*p.mass*p.V[0];
        }
    }

    // right wall
    for(auto & p: bodies) {
        double delta = p.rad + p.R[0] - par["LX"]; 
        if (delta > 0) {
            p.F[0] += -par["K"]*delta - par["B"]*p.mass*p.V[0];
        }
    }


}

void time_step(std::vector<Particle> & bodies, std::map<std::string, double>& par)
{
    for(auto & p: bodies) {
        // // euler
        // p.R = p.R + p.V*par["DT"];
        // p.V = p.V + p.F*par["DT"]/p.mass;

        // leap-frog
        p.V = p.V + p.F*par["DT"]/p.mass;
        p.R = p.R + p.V*par["DT"];
    }
}

void start_integration(std::vector<Particle> & bodies, std::map<std::string, double>& par)
{
    for(auto & p: bodies) {
        p.V = p.V - 0.5*par["DT"]*p.F/p.mass;
    }
}
