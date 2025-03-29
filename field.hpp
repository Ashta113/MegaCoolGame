#pragma once

#include "tetromino.hpp"

const int SCREEN_WIDTH = 850;
const int SCREEN_HEIGHT = 880;
const int BLOCK_SIZE = 52;
const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 15;
const int FIELD_X = 270;
const int FIELD_Y = 50;
const int TEXT_X = 50;
const int TEXT_Y = 250;

class Field
{
public:
    int field[15][10];
    Tetramino tetramino;

    void SplitToField();
    void CreateTetramino();
    bool CheckGameOver();
    bool CheckToDown();
    bool CheckToLeft();
    bool CheckToRight();
    bool CheckRotate();
    void CreateField();
    int ClearFullLines();
private:
};