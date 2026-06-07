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
        float starting_velocity;
        Vector2 position;
        Vector2 starting_pos;
        float width;
        float height;
        Color color;


    public:
        Cactus(float starting_velocity, Vector2 startPos, float width, float height, Color color)
            : velocity{starting_velocity},
              starting_velocity{starting_velocity},
              position{startPos},
              starting_pos(startPos),
              width(width),
              height(height),
              color{color}
        {}

        void update(float dt, float accel) {
            velocity += accel * dt;
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

        void reset() {
            velocity = starting_velocity;
            position = starting_pos;
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

void update_game(GameState& game_state, Dino& dino, Cactus& cactus, float dt, float gravity, float accel) {
    switch(game_state) {
        
        case GameState::Menu:
            if (IsKeyPressed(KEY_SPACE)) {
                game_state = GameState::Playing;
            }
            break;
        
        case GameState::Playing:
            dino.update(dt, gravity);
            cactus.update(dt, accel);
            if (CheckCollisionRecs(dino.get_rect(), cactus.get_rect())) {
                game_state = GameState::GameOver;
            }
            break;
        
        case GameState::GameOver:
            if (IsKeyPressed(KEY_SPACE)) {
                cactus.reset();
                game_state = GameState::Playing;
            }
            break;
        }
}
void draw_game(GameState game_state, const Dino& dino, const Cactus& cactus, int title_font_size, int title_text_length, int fun_font_size, int fun_text_length) {
    switch(game_state) {

        case GameState::Menu:
            DrawText("Rex Run", (SCREEN_WIDTH - title_text_length) / 2, 50, title_font_size, BLACK);
            DrawText("Press SPACE to run!", (SCREEN_WIDTH - fun_text_length) / 2, 100, fun_font_size, BLACK);
            dino.draw();
            cactus.draw();
            break;
        case GameState::Playing:
            dino.draw();
            cactus.draw();
            break;
        case GameState::GameOver:
            dino.draw();
            cactus.draw();
            break;
    }
}

float accel = 10.0f;
float gravity = 2000.0f;
Vector2 dino_start_pos = {180.0f, 500.0f};
Vector2 dino_start_velocity = {0.0f, 0.0f};
Vector2 cactus_start_pos = {1280, GROUND_Y - 75};

int main() {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Rex Run");
    SetTargetFPS(60);
    
    Dino dino(dino_start_velocity, dino_start_pos, 50, 100, true, BLACK);
    Cactus cacti(450.0f, cactus_start_pos, 25, 75, GREEN);
    
    GameState game_state = GameState::Menu;

    int title_font_size = 50;
    int title_text_length = MeasureText("Rex Run", 50);
    int fun_font_size = 30;
    int fun_text_length = MeasureText("Press SPACE to run!", 30);

    while(!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        update_game(game_state, dino, cacti, dt, gravity, accel);


        BeginDrawing();
            ClearBackground(GRAY);
            DrawLine(0, GROUND_Y, SCREEN_WIDTH, GROUND_Y, WHITE);
            draw_game(game_state, dino, cacti, title_font_size, title_text_length, fun_font_size, fun_text_length);

        EndDrawing();
    }
    
    CloseWindow();
    

    return 0;
}