// g++ md-v9-raylib-3.cpp -o md-raylib.x -I ./raylib-5.5_linux_amd64/include -L ./raylib-5.5_linux_amd64/lib -l raylib
// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./raylib-5.5_linux_amd64/lib 

#include <iostream>
#include <valarray>
#include <vector>
#include <map>
#include <string>
#include <cmath> // Needed for sin/cos

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
    InitWindow(screenWidth, screenHeight, "3D Simulation - Custom Left Click Control");
    
    // 3. Setup Camera Data
    Camera3D camera = { 0 };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Camera Orbit Variables
    // We look at the center of the room
    Vector3 target = { (float)params["LX"]/2.0f, 2.0f, 0.0f };
    
    // Spherical coordinates for the camera
    float camRadius = 14.0f; // Distance from target
    float camAngle = 0.0f;   // Horizontal angle (rotation around Y)
    float camPitch = 0.4f;   // Vertical angle (height)

    SetTargetFPS(120); 

    // Time Management
    double accumulator = 0.0;
    double physDT = params["DT"];

    // Visual Dimensions
    float roomWidth = (float)params["LX"];
    float wallHeight = 5.0f;
    float depth = 4.0f; 
    float thickness = 0.1f;

    // --- MAIN LOOP ---
    while (!WindowShouldClose())
    {
        // --- A. CUSTOM CAMERA INPUT ---
        // 1. Zoom with Mouse Wheel
        camRadius -= GetMouseWheelMove() * 0.5f;
        if (camRadius < 2.0f) camRadius = 2.0f; // Prevent going through target

        // 2. Rotate with LEFT CLICK
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 delta = GetMouseDelta();
            camAngle -= delta.x * 0.01f; // Sensitivity X
            camPitch -= delta.y * 0.01f; // Sensitivity Y
        }

        // Clamp Pitch to avoid flipping the camera upside down
        if (camPitch > 1.5f) camPitch = 1.5f;
        if (camPitch < 0.1f) camPitch = 0.1f; // Don't go below floor

        // 3. Update Camera Position based on spherical coords
        // x = r * cos(pitch) * sin(angle)
        // y = r * sin(pitch)
        // z = r * cos(pitch) * cos(angle)
        camera.position.x = target.x + camRadius * cosf(camPitch) * sinf(camAngle);
        camera.position.y = target.y + camRadius * sinf(camPitch);
        camera.position.z = target.z + camRadius * cosf(camPitch) * cosf(camAngle);
        
        camera.target = target;

        // --- B. PHYSICS UPDATE ---
        double frameTime = GetFrameTime();
        if (frameTime > 0.25) frameTime = 0.25;
        accumulator += frameTime;

        while (accumulator >= physDT) {
            compute_forces(particles, params);
            time_step(particles, params);
            accumulator -= physDT;
        }

        // --- C. RENDER ---
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
                DrawSphere(pos, (float)particles[0].rad, BLUE);
                DrawSphereWires(pos, (float)particles[0].rad, 8, 8, DARKBLUE);
                
                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawFPS(10, 10);
            DrawText("Controls: Hold LEFT CLICK to Rotate. Wheel to Zoom.", 10, 30, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// --- PHYSICS IMPLEMENTATION ---

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