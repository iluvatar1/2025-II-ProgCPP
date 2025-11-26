#include <iostream>
#include <valarray>
#include <vector>
#include <map>
#include <string>

#include "raylib.h"

// --- PHYSICS ENGINE (Unchanged) ---
struct Particle {
    std::valarray<double> R{0.0, 0.0, 0.0}, V{0.0, 0.0, 0.0}, F{0.0, 0.0, 0.0};
    double mass{0}, rad{0};
    void print(void);
};

void initial_conditions(std::vector<Particle> & bodies);
void compute_forces(std::vector<Particle> & bodies, std::map<std::string, double>& par);
void time_step(std::vector<Particle> & bodies, std::map<std::string, double>& par);
void start_integration(std::vector<Particle> & bodies, std::map<std::string, double>& par);

// --- MAIN ---
int main(void)
{
    // 1. Setup Simulation
    int N = 1;
    std::vector<Particle> particles(N);

    std::map<std::string, double> params;
    params["DT"] = 0.01;   
    params["G"] = 9.81;
    params["K"] = 201.9876;
    params["B"] = 0.2;
    params["LX"] = 3.78;

    initial_conditions(particles);
    start_integration(particles, params);

    // 2. Setup Raylib Window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "3D Physics - Mouse Orbit");
    
    // 3. Setup Camera
    Camera3D camera = { 0 };
    // Start position: Isometric-like view
    camera.position = (Vector3){ (float)params["LX"] + 6.0f, 8.0f, 10.0f }; 
    // Target: Look at the center of the box (LX/2, Height/2, Z=0)
    camera.target = (Vector3){ (float)params["LX"]/2.0f, 2.5f, 0.0f }; 
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Use a slightly higher framerate for smoother interaction
    SetTargetFPS(60); 

    // Time Accumulator
    double accumulator = 0.0;
    double physDT = params["DT"];

    // Wall Dimensions
    float roomWidth = (float)params["LX"];
    float wallHeight = 6.0f;
    float depth = 4.0f; 
    float thickness = 0.2f;

    // --- MAIN LOOP ---
    while (!WindowShouldClose())
    {
        // --- A. INPUT & UPDATE ---
        
        // Update Camera allows Mouse Orbiting
        // Arguments: Camera pointer, Mode
        UpdateCamera(&camera, CAMERA_ORBITAL);

        // Physics Step (Accumulator)
        double frameTime = GetFrameTime();
        if (frameTime > 0.25) frameTime = 0.25;
        accumulator += frameTime;

        while (accumulator >= physDT) {
            compute_forces(particles, params);
            time_step(particles, params);
            accumulator -= physDT;
        }

        // --- B. RENDER ---
        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                // 1. Draw Floor
                DrawCube((Vector3){roomWidth/2, -thickness/2, 0}, 
                         roomWidth + thickness*2, thickness, depth, LIGHTGRAY);
                DrawCubeWires((Vector3){roomWidth/2, -thickness/2, 0}, 
                              roomWidth + thickness*2, thickness, depth, DARKGRAY);

                // 2. Draw Left Wall
                DrawCube((Vector3){-thickness/2, wallHeight/2, 0}, 
                         thickness, wallHeight, depth, MAROON);
                DrawCubeWires((Vector3){-thickness/2, wallHeight/2, 0}, 
                              thickness, wallHeight, depth, DARKGRAY);

                // 3. Draw Right Wall
                DrawCube((Vector3){roomWidth + thickness/2, wallHeight/2, 0}, 
                         thickness, wallHeight, depth, MAROON);
                DrawCubeWires((Vector3){roomWidth + thickness/2, wallHeight/2, 0}, 
                              thickness, wallHeight, depth, DARKGRAY);

                // 4. Draw Particle
                Vector3 pos = { (float)particles[0].R[0], (float)particles[0].R[1], 0.0f };
                
                // Draw Sphere
                DrawSphere(pos, (float)particles[0].rad, BLUE);
                // Draw a small wireframe around it to see rotation better
                DrawSphereWires(pos, (float)particles[0].rad, 8, 8, DARKBLUE);
                
                // Draw simple grid for reference
                DrawGrid(10, 1.0f);

            EndMode3D();

            // Instructions
            DrawFPS(10, 10);
            DrawText("- Left Click: Rotate", 10, 30, 20, DARKGRAY);
            DrawText("- Wheel: Zoom", 10, 50, 20, DARKGRAY);
            DrawText("- Right Click: Pan", 10, 70, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// --- PHYSICS IMPLEMENTATION (Unchanged) ---

void Particle::print(void) {}

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