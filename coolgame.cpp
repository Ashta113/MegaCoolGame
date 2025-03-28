#include "coolgame.hpp"
#include <SDL2/SDL.h>

CoolGame::CoolGame():
    isRunning { true },
    gameOver { false },
    fallSpeed { 1 },
    lastUpdate { 0 }
{ 
}

CoolGame::~CoolGame()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void CoolGame::init() 
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Mega Cool Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    isRunning = true;
    gameOver = false;
    field.CreateField(field);
    tetramino.CreateTetramino(field, tetramino);
}

void CoolGame::checkEvents() 
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            isRunning = false;
        }
        else if (e.type == SDL_KEYDOWN && !gameOver) {
            switch (e.key.keysym.sym) 
            {
                case SDLK_LEFT:
                    if (tetramino.CheckToLeft(field, tetramino)) {
                        tetramino.MoveLeft(tetramino);
                    }
                    break;
                case SDLK_RIGHT:
                    if (tetramino.CheckToRight(field, tetramino)) {
                        tetramino.MoveRight(tetramino);
                    }
                    break;
                case SDLK_DOWN:
                    if (tetramino.CheckToDown(field, tetramino)) {
                        tetramino.MoveDown(tetramino);
                    } else {
                        tetramino.SplitToField(field, tetramino);
                        field.ClearFullLines(field);
                        tetramino.CreateTetramino(field, tetramino);
                        gameOver = tetramino.CheckGameOver(field, tetramino);
                    }
                    break;
                case SDLK_UP:
                    if (tetramino.CheckRotate(field, tetramino)) {
                        tetramino.Rotate(tetramino);
                    }
                    break;
            }
        }
    }
}

void CoolGame::update()
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastUpdate > (1000 / fallSpeed)) {
        if (tetramino.CheckToDown(field, tetramino)) {
            tetramino.MoveDown(tetramino);
        } else {
            tetramino.SplitToField(field, tetramino);
            field.ClearFullLines(field);
            tetramino.CreateTetramino(field, tetramino);
            gameOver = tetramino.CheckGameOver(field, tetramino);
        }
        lastUpdate = currentTime;
    }
}

void CoolGame::draw()
{
    if (gameOver) {
        field.GameOver(renderer);
        field.DrawBorderField(renderer, field);
    } else {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(renderer);
        tetramino.DrawTetramino(renderer, field, tetramino);
        field.DrawBorderField(renderer, field);
        field.DrawField(renderer, field);
        SDL_RenderPresent(renderer);
    }
}

void CoolGame::run()
{
    while (isRunning) {
        checkEvents();
        if (!gameOver) update();
        draw();
        SDL_Delay(16);
    }
}