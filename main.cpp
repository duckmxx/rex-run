#include "raylib.h"

static constexpr int SCREEN_WIDTH = 1270;
static constexpr int SCREEN_HEIGHT = 720;

static constexpr int GROUND_Y = 600;


class Dino {
    private:
        Vector2 velocity;
        Vector2 position;
        float width;
        float height;
        bool onGround;
        Color color;

    public:
        Dino(Vector2 velocity, Vector2 position, float width, float height, bool onGround, Color color)
            : velocity{velocity},
              position{position}, 
              width{width},
              height{height}, 
              onGround{onGround},
              color{color} {}

        void update(float dt, float gravity) {
            velocity.y += gravity * dt;
            
            if (IsKeyPressed(KEY_SPACE) && onGround) {
                velocity.y -= 700.0f;
                onGround = false;
            }
            position.y += velocity.y * dt;
            
            if ((position.y + height) >= GROUND_Y) {
                velocity.y = 0;
                position.y = GROUND_Y - height;
                onGround = true;
            }

        }
        
        void draw() {
            DrawRectangle(position.x, position.y, 50, 100, color);
        }
};

class Cactus {
    private:
        float velocity;
        Vector2 position;
        Vector2 starting_pos;
        float width;
        float height;

        Color color;


    public:
        Cactus(float velocity, Vector2 startPos, float width, float height, Color color)
            : velocity{velocity},
              position{startPos},
              starting_pos(startPos),
              width(width),
              height(height),
              color{color}
        {}

        void update(float dt) {
            position.x -= velocity * dt;
            if ((position.x + width) <= 0) {
                position.x = starting_pos.x;
            }
        }

        void draw() {
            DrawRectangle(position.x, position.y, width, height, color);
        }

};


float gravity = 1500.0f;
Vector2 dino_start_pos = {180.0f, 500.0f};
Vector2 dino_start_velocity = {0.0f, 0.0f};

int main() {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rex Run");
    SetTargetFPS(60);
    Dino dino(dino_start_velocity, dino_start_pos, 50, 100, true, BLACK);
    Cactus cacti(450, {1280, GROUND_Y - 75}, 25, 75, GREEN);
    
    while(!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        dino.update(dt, gravity);
        cacti.update(dt);


        BeginDrawing();
            ClearBackground(GRAY);
            DrawLine(0, 600, 1280, 600, WHITE);
            dino.draw();
            cacti.draw();

        EndDrawing();
    }
    
    CloseWindow();
    



    return 0;
}