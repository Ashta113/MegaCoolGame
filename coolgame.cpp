#include "coolgame.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

CoolGame::CoolGame():
    isRunning { true },
    gameOver { false },
    fallSpeed { 1 },
    lastUpdate { 0 },
    score { 0 }
{ 
}

CoolGame::~CoolGame()
{
    SDL_DestroyTexture(textTexture);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void CoolGame::init() 
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow("Mega Cool Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   font = TTF_OpenFont("NotoSans.ttf", 26);
}

void CoolGame::createNewGame() {
    score = 0;
    field.CreateField();
    field.CreateTetramino();
    gameOver = false;
    lastUpdate = SDL_GetTicks();
}

void CoolGame::checkEvents() 
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
            isRunning = false;
        }
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {
            createNewGame();
        }
        else if (e.type == SDL_KEYDOWN && !gameOver) {
            switch (e.key.keysym.sym) 
            {
                case SDLK_SPACE:
                    field.DropDown();
                    field.SplitToField();
                    score += field.ClearFullLines();
                    field.CreateTetramino();
                    gameOver = field.CheckGameOver();
                    lastUpdate = SDL_GetTicks();
                case SDLK_LEFT:
                    if (field.CheckToLeft()) {
                        field.tetramino.MoveLeft();
                    }
                    break;
                case SDLK_RIGHT:
                    if (field.CheckToRight()) {
                        field.tetramino.MoveRight();
                    }
                    break;
                case SDLK_DOWN:
                    if (field.CheckToDown()) {
                        field.tetramino.MoveDown();
                        lastUpdate = SDL_GetTicks();
                    } else {
                        field.SplitToField();
                        score += field.ClearFullLines();
                        field.CreateTetramino();
                        gameOver = field.CheckGameOver();
                    }
                    break;
                case SDLK_UP:
                    if (field.CheckRotate()) {
                        field.tetramino.Rotate();
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
        if (field.CheckToDown()) {
            field.tetramino.MoveDown();
            lastUpdate = SDL_GetTicks();
        } else {
            field.SplitToField();
            score += field.ClearFullLines();
            field.CreateTetramino();
            gameOver = field.CheckGameOver();
            lastUpdate = SDL_GetTicks();
        }
    }
}

void CoolGame::DrawTetramino()
{
    for (int y = field.tetramino.position.y; y < field.tetramino.position.y + 4; ++y) {
        for (int x = field.tetramino.position.x; x < field.tetramino.position.x + 4; ++x) {
            if (figures[field.tetramino.blockPos[0]][field.tetramino.blockPos[1]][y - field.tetramino.position.y][x - field.tetramino.position.x]) {
                SDL_Rect cell = {
                    FIELD_X + BLOCK_SIZE * x,
                    FIELD_Y + BLOCK_SIZE * y,
                    BLOCK_SIZE,
                    BLOCK_SIZE
                };
                SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }
}

void CoolGame::DrawBorderField() {
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_Rect border =
    {
        FIELD_X - 2,
        FIELD_Y - 2,
        FIELD_WIDTH * BLOCK_SIZE + 4,
        FIELD_HEIGHT * BLOCK_SIZE + 4
    };
    SDL_RenderDrawRect(renderer, &border);
}

void CoolGame::DrawField() {
    for (int y = 0; y < 15; ++y) {
        for (int x = 0; x < 10; ++x) {
            if (field.field[y][x]) {
                SDL_Rect cell = {
                    FIELD_X + BLOCK_SIZE * x,
                    FIELD_Y + BLOCK_SIZE * y,
                    BLOCK_SIZE,
                    BLOCK_SIZE
                };
                SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderFillRect(renderer, &cell);
            } else {
                SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderDrawPoint(renderer, FIELD_X + BLOCK_SIZE * x + BLOCK_SIZE / 2, FIELD_Y + BLOCK_SIZE * y + BLOCK_SIZE / 2);
            }
        }
    }
}

void CoolGame::DrawMirror() 
{
    Tetramino clone = field.tetramino;
    field.DropDown();
    for (int y = field.tetramino.position.y; y < field.tetramino.position.y + 4; ++y) {
        for (int x = field.tetramino.position.x; x < field.tetramino.position.x + 4; ++x) {
            if (figures[field.tetramino.blockPos[0]][field.tetramino.blockPos[1]][y - field.tetramino.position.y][x - field.tetramino.position.x]) {
                SDL_Rect cell = {
                    FIELD_X + BLOCK_SIZE * x,
                    FIELD_Y + BLOCK_SIZE * y,
                    BLOCK_SIZE,
                    BLOCK_SIZE
                };
                SDL_SetRenderDrawColor(renderer, 0xbb, 0x00, 0xbb, 0xff);
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }
    field.tetramino = clone;
}

void CoolGame::DrawText() 
{
    SDL_Color textColor = {0xff, 0xff, 0xff, 0xff};
    std::string text = "Score: ";
    text += std::to_string(score);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_Rect textRect =
    {
        TEXT_X,
        TEXT_Y,
        0,
        0
    };
    SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}

void CoolGame::draw()
{
    if (gameOver) {
        GameOver();
        DrawBorderField();
        DrawText();
    } else {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
        SDL_RenderClear(renderer);
        DrawMirror();
        DrawTetramino();
        DrawBorderField();
        DrawField();
        DrawText();
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

void CoolGame::GameOver() {
    const int game_over[15][10] =
    {
        1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 
        1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 
        1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 
        1, 1, 1, 2, 0, 0, 1, 2, 0, 2, 
        0, 0, 2, 0, 2, 0, 0, 2, 0, 2, 
        0, 0, 2, 2, 2, 3, 3, 2, 0, 2, 
        0, 0, 2, 0, 2, 3, 0, 0, 2, 0, 
        3, 0, 3, 0, 0, 3, 3, 3, 0, 0, 
        3, 3, 3, 0, 0, 3, 0, 0, 0, 0, 
        3, 0, 3, 0, 0, 3, 3, 3, 0, 0, 
        3, 0, 4, 4, 4, 0, 0, 4, 4, 0, 
        0, 0, 4, 0, 0, 0, 0, 4, 0, 4, 
        0, 0, 4, 4, 4, 0, 0, 4, 4, 0, 
        0, 0, 4, 0, 0, 0, 0, 4, 0, 4, 
        0, 0, 4, 4, 4, 0, 0, 4, 0, 4        
    };
    for (int y = 0; y < 15; ++y) {
        for (int x = 0; x < 10; ++x) {
            SDL_Rect cell = 
            {
                FIELD_X + BLOCK_SIZE * x,
                FIELD_Y + BLOCK_SIZE * y,
                BLOCK_SIZE,
                BLOCK_SIZE
            };
            switch (game_over[y][x]) 
            {
                case 0:
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
                    SDL_RenderFillRect(renderer, &cell);
                    break;
                case 1:
                    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xff);
                    SDL_RenderFillRect(renderer, &cell);
                    break;
                case 2:
                    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
                    SDL_RenderFillRect(renderer, &cell);
                    break;
                case 3:
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xff, 0xff);
                    SDL_RenderFillRect(renderer, &cell);
                    break;
                case 4:
                    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0xff);
                    SDL_RenderFillRect(renderer, &cell);
                    break;
            }
        }
    }
    SDL_RenderPresent(renderer);
}