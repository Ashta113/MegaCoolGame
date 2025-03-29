#include "tetromino.hpp"
#include "field.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class CoolGame 
{
public:
    CoolGame();
    ~CoolGame();
    TTF_Font* font;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* textTexture;
    Field field;

    void init();
    void createNewGame();
    void checkEvents();
    void update();
    void DrawTetramino();
    void DrawBorderField();
    void DrawField();
    void DrawMirror();
    void DrawText();
    void draw();
    void run();
    void GameOver();
private:
    bool isRunning;
    bool gameOver;
    int fallSpeed;
    int lastUpdate;
    int score;
};