#include "tetromino.hpp"
#include <SDL2/SDL.h>

void Tetramino::SplitToField(Field& field_, Tetramino& tetramino_)
{
    for (int y = tetramino_.position.y; y < tetramino_.position.y + 4; ++y) {
        for (int x = tetramino_.position.x; x < tetramino_.position.x + 4; ++x) {
            if (figures[tetramino_.blockPos[0]][tetramino_.blockPos[1]][y - tetramino_.position.y][x - tetramino_.position.x]) {
                field_.field[y][x] = 1;
            }
        }
    }
}
void Tetramino::CreateTetramino(Field& field_, Tetramino& tetramino_)
{
    int NumberNewTetramino = rand() % 7;
    tetramino_.blockPos[0] = NumberNewTetramino;
    tetramino_.blockPos[1] = 0;
    tetramino_.position.x = 3;
    tetramino_.position.y = 0;
}
void Tetramino::DrawTetramino(SDL_Renderer* renderer_, Field& field_, Tetramino& tetramino_)
{
    for (int y = tetramino_.position.y; y < tetramino_.position.y + 4; ++y) {
        for (int x = tetramino_.position.x; x < tetramino_.position.x + 4; ++x) {
            if (figures[tetramino_.blockPos[0]][tetramino_.blockPos[1]][y - tetramino_.position.y][x - tetramino_.position.x]) {
                SDL_Rect cell = {
                    FIELD_X + BLOCK_SIZE * x,
                    FIELD_Y + BLOCK_SIZE * y,
                    BLOCK_SIZE,
                    BLOCK_SIZE
                };
                SDL_SetRenderDrawColor(renderer_, 0xff, 0x00, 0xff, 0xff);
                SDL_RenderFillRect(renderer_, &cell);
            }
        }
    }
}
bool Tetramino::CheckGameOver(Field& field_, Tetramino& tetramino_)
{
    for (int y = tetramino_.position.y; y < tetramino_.position.y + 4; ++y) {
        for (int x = tetramino_.position.x; x < tetramino_.position.x + 4; ++x) {
            if (figures[tetramino_.blockPos[0]][tetramino_.blockPos[1]][y - tetramino_.position.y][x - tetramino_.position.x] && field_.field[y][x]) {
                return true;
            }
        }
    }
    return false;
}
bool Tetramino::CheckToDown(Field& field_, Tetramino& tetramino_)
{
    Tetramino future = tetramino_;
    Tetramino::MoveDown(future);
    for (int y = future.position.y; y < future.position.y + 4; ++y) {
        for (int x = future.position.x; x < future.position.x + 4; ++x) {
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && field_.field[y][x]) {
                return false;
            }
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && y == 15) {
                return false;
            }
        }
    }
    return true;
}
bool Tetramino::CheckToLeft(Field& field_, Tetramino& tetramino_)
{
    Tetramino future = tetramino_;
    Tetramino::MoveLeft(future);
    for (int y = future.position.y; y < future.position.y + 4; ++y) {
        for (int x = future.position.x; x < future.position.x + 4; ++x) {
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && field_.field[y][x]) {
                return false;
            }
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && x == -1) {
                return false;
            }
        }
    }
    return true;
}
bool Tetramino::CheckToRight(Field& field_, Tetramino& tetramino_)
{
    Tetramino future = tetramino_;
    Tetramino::MoveRight(future);
    for (int y = future.position.y; y < future.position.y + 4; ++y) {
        for (int x = future.position.x; x < future.position.x + 4; ++x) {
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && field_.field[y][x]) {
                return false;
            }
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && x == 10) {
                return false;
            }
        }
    }
    return true;
}
bool Tetramino::CheckRotate(Field& field_, Tetramino& tetramino_)
{
    Tetramino future = tetramino_;
    Tetramino::Rotate(future);
    for (int y = future.position.y; y < future.position.y + 4; ++y) {
        for (int x = future.position.x; x < future.position.x + 4; ++x) {
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && field_.field[y][x]) {
                return false;
            }
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && (y == 15 || x == -1 || x == 10)) {
                return false;
            }
        }
    }
    return true;
}
void Tetramino::MoveDown(Tetramino& tetramino_)
{
    tetramino_.position.y += 1;
}
void Tetramino::MoveLeft(Tetramino& tetramino_)
{
    tetramino_.position.x -= 1;
}
void Tetramino::MoveRight(Tetramino& tetramino_)
{
    tetramino_.position.x += 1;
}
void Tetramino::Rotate(Tetramino& tetramino_)
{
    tetramino_.blockPos[1] += 1;
    tetramino_.blockPos[1] %= 4;
}