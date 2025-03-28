#include "tetromino.hpp"
#include "field.hpp"

class CoolGame 
{
public:
    CoolGame();
    ~CoolGame();

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Field field;

    void init();
    void checkEvents();
    void update();
    void draw();
    void run();
    void DrawTetramino();
    void DrawBorderField();
    void DrawField();
    void GameOver();
private:
    bool isRunning;
    bool gameOver;
    int fallSpeed;
    int lastUpdate;
};