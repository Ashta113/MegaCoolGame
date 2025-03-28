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
    Tetramino tetramino;

    void init();
    void checkEvents();
    void update();
    void draw();
    void run();
private:
    bool isRunning;
    bool gameOver;
    int fallSpeed;
    int lastUpdate;
};