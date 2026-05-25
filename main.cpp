#include <iostream>
#include "raylib.h"

static constexpr int SCREEN_WIDTH = 1270;
static constexpr int SCREEN_HEIGHT = 720;

class Dino {
    private:
        Vector2 velocity;
        Vector2 position;
    
    public:
        Dino(Vector2 velocity, Vector2 position) : velocity{velocity}, position{position} {}

        void updatePosition(Vector2 new_position) {
            position = new_position;
        }
        void updateVelocity(Vector2 new_velocity) {
            velocity = new_velocity;
        }
        Vector2 getPosition() {
            return position;
        }
        Vector2 getVelocity() {
            return velocity;
        }
};


float gravity = 100.0f;
Vector2 dino_start_pos = {180.0f, 0.0f};
Vector2 dino_start_velocity = {0.0f, 0.0f};

int main() {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rex Run");
    SetTargetFPS(60);
    Dino dino(dino_start_velocity, dino_start_pos);
    
    
    while(!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        std::cout << "Position: " << dino.getPosition().x << " " << dino.getPosition().y << " Velocity: " << dino.getVelocity().x << " " << dino.getVelocity().y << "\n";

        dino.updateVelocity({dino_start_velocity.x, dino.getVelocity().y + (gravity * dt)});
      //  dino.updateVelocity({0.0f, 50.0f});
        dino.updatePosition({dino_start_pos.x, dino.getPosition().y + (dino.getVelocity().y * dt)});


        BeginDrawing();
            ClearBackground(GRAY);
            DrawLine(0, 600, 1280, 600, WHITE);
            DrawRectangle(dino.getPosition().x, dino.getPosition().y, 50, 100, BLACK);


        EndDrawing();
    }
    
    CloseWindow();
    



    return 0;
}