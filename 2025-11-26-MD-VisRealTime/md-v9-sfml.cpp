// g++ md-v9-sfml.cpp -o md.x -lsfml-graphics -lsfml-window -lsfml-system

#include <iostream>
#include <valarray>
#include <vector>
#include <map>
#include <string>

// SFML headers
#include <SFML/Graphics.hpp>

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

    std::map<std::string, double> params;
    params["T0"] = 0.0;
    params["TF"] = 100.0; // Run longer
    // IMPORTANT: Keep physics DT constant and small for stability
    params["DT"] = 0.01;  
    params["G"] = 9.81;
    params["K"] = 201.9876;
    params["B"] = 0.2; // Damping
    params["LX"] = 3.78;

    initial_conditions(particles);
    start_integration(particles, params);

    // --- SFML SETUP ---
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fixed Time Step Simulation");
    window.setFramerateLimit(120); 

    // Setup View (Coordinate System)
    sf::View view;
    float worldWidth = params["LX"] + 2.0; 
    float aspectRatio = (float)window.getSize().x / window.getSize().y;
    view.setSize(worldWidth, -worldWidth / aspectRatio); // Negative height flips Y-axis
    view.setCenter(params["LX"] / 2.0, 2.0); 
    window.setView(view);

    // Shapes
    sf::CircleShape pShape(particles[0].rad);
    pShape.setOrigin(particles[0].rad, particles[0].rad);
    pShape.setFillColor(sf::Color::Cyan);

    float wallThick = 0.1f;
    sf::RectangleShape floorShape(sf::Vector2f(params["LX"] + wallThick*4, wallThick));
    floorShape.setOrigin(wallThick*2, wallThick);
    floorShape.setPosition(-wallThick*2, 0);
    floorShape.setFillColor(sf::Color(100, 100, 100));

    sf::RectangleShape leftWall(sf::Vector2f(wallThick, 5.0f));
    leftWall.setOrigin(wallThick, 0);
    leftWall.setPosition(0, -1.0);
    leftWall.setFillColor(sf::Color(150, 50, 50));

    sf::RectangleShape rightWall(sf::Vector2f(wallThick, 5.0f));
    rightWall.setPosition(params["LX"], -1.0);
    rightWall.setFillColor(sf::Color(150, 50, 50));

    // --- TIME MANAGEMENT VARIABLES ---
    sf::Clock clock;
    double accumulator = 0.0;
    const double dt = params["DT"]; // The fixed physics time step

    while (window.isOpen()) {
        // 1. Measure how much time passed since last frame
        sf::Time elapsed = clock.restart();
        double frameTime = elapsed.asSeconds();

        // Safety: If the window is dragged or lags, don't try to simulate huge jumps
        if (frameTime > 0.25) frameTime = 0.25;

        // 2. Add to accumulator
        accumulator += frameTime;

        // Process Events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        // 3. Consume accumulated time in fixed discrete steps
        while (accumulator >= dt) {
            compute_forces(particles, params);
            time_step(particles, params);
            
            accumulator -= dt;
        }

        // 4. Render
        window.clear(sf::Color::Black);
        
        pShape.setPosition(particles[0].R[0], particles[0].R[1]);
        
        window.draw(floorShape);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(pShape);
        
        window.display();
    }

    return 0;
}

// --- PHYSICS IMPLEMENTATION ---

void Particle::print(void) {
    // Keep existing print logic
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
    for(auto & p: bodies) p.F = 0;

    // Gravity
    for(auto & p: bodies) p.F[1] += -par["G"]*p.mass;

    // Floor
    for(auto & p: bodies) {
        double delta = p.rad - p.R[1]; 
        if (delta > 0) p.F[1] += par["K"]*delta - par["B"]*p.mass*p.V[1];
    }

    // Left wall
    for(auto & p: bodies) {
        double delta = p.rad - p.R[0]; 
        if (delta > 0) p.F[0] += par["K"]*delta - par["B"]*p.mass*p.V[0];
    }

    // Right wall
    for(auto & p: bodies) {
        double delta = p.rad + p.R[0] - par["LX"]; 
        if (delta > 0) p.F[0] += -par["K"]*delta - par["B"]*p.mass*p.V[0];
    }
}

void time_step(std::vector<Particle> & bodies, std::map<std::string, double>& par)
{
    for(auto & p: bodies) {
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