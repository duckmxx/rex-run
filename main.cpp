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
        
        Rectangle get_rect() const {
            return Rectangle{
                position.x,
                position.y,
                width,
                height,
                
            };
        }

        void draw() const {
            DrawRectangle(position.x, position.y, width, height, color);
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

        Rectangle get_rect() const {
            return Rectangle{
                position.x,
                position.y,
                width,
                height,
                
            };
        }

        void draw() const {
            DrawRectangle(position.x, position.y, width, height, color);
        }

};

enum class GameState {
    Menu,
    Playing,
    GameOver
};

void update_game(GameState& game_state, Dino& dino, Cactus& cactus, float dt, float gravity) {
    switch(game_state) {
        
        case GameState::Menu:
            if (IsKeyPressed(KEY_SPACE)) {
                game_state = GameState::Playing;
            }
            break;
        
        case GameState::Playing:
            dino.update(dt, gravity);
            cactus.update(dt);
            if (CheckCollisionRecs(dino.get_rect(), cactus.get_rect())) {
                game_state = GameState::GameOver;
            }
            if (IsKeyPressed(KEY_R)) {
                game_state = GameState::Playing;
            }
            break;
        
        case GameState::GameOver:
            if (IsKeyPressed(KEY_R)) {
                game_state = GameState::Playing;
            }
            break;
        }
}
void draw_game(GameState game_state, const Dino& dino, const Cactus& cactus) {
    switch(game_state) {

        case GameState::Menu:
            break;
        case GameState::Playing:
            dino.draw();
            cactus.draw();
            break;
        case GameState::GameOver:
            break;
    }
}


float gravity = 1500.0f;
Vector2 dino_start_pos = {180.0f, 500.0f};
Vector2 dino_start_velocity = {0.0f, 0.0f};

int main() {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rex Run");
    SetTargetFPS(60);
    
    Dino dino(dino_start_velocity, dino_start_pos, 50, 100, true, BLACK);
    Cactus cacti(450, {1280, GROUND_Y - 75}, 25, 75, GREEN);
    
    GameState game_state = GameState::Menu;


    while(!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        update_game(game_state, dino, cacti, dt, gravity);


        BeginDrawing();
            ClearBackground(GRAY);
            DrawLine(0, GROUND_Y, SCREEN_WIDTH, GROUND_Y, WHITE);
            draw_game(game_state, dino, cacti);

        EndDrawing();
    }
    
    CloseWindow();
    

    return 0;
}