#pragma once

#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 850;
const int SCREEN_HEIGHT = 880;
const int BLOCK_SIZE = 52;
const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 15;
const int FIELD_X = 270;
const int FIELD_Y = 50;

class Field
{
public:
    int field[15][10];

    void CreateField(Field& field_);
    void DrawBorderField(SDL_Renderer* renderer_, Field& field_);
    void DrawField(SDL_Renderer* renderer_, Field& field_);
    void ClearFullLines(Field& field_);
    void GameOver(SDL_Renderer* renderer_);
private:
};