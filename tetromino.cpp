#include "tetromino.hpp"
#include <SDL2/SDL.h>

void Tetramino::MoveDown()
{
    position.y += 1;
}
void Tetramino::MoveLeft()
{
    position.x -= 1;
}
void Tetramino::MoveRight()
{
    position.x += 1;
}
void Tetramino::Rotate()
{
    blockPos[1] += 1;
    blockPos[1] %= 4;
}