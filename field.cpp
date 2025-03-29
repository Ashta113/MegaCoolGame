#include "field.hpp"
#include <SDL2/SDL.h>

void Field::SplitToField()
{
    for (int y = tetramino.position.y; y < tetramino.position.y + 4; ++y) {
        for (int x = tetramino.position.x; x < tetramino.position.x + 4; ++x) {
            if (figures[tetramino.blockPos[0]][tetramino.blockPos[1]][y - tetramino.position.y][x - tetramino.position.x]) {
                field[y][x] = 1;
            }
        }
    }
}

void Field::CreateTetramino()
{
    int NumberNewTetramino = rand() % 7;
    tetramino.blockPos[0] = NumberNewTetramino;
    tetramino.blockPos[1] = 0;
    tetramino.position.x = 3;
    tetramino.position.y = 0;
}

bool Field::CheckGameOver()
{
    for (int y = tetramino.position.y; y < tetramino.position.y + 4; ++y) {
        for (int x = tetramino.position.x; x < tetramino.position.x + 4; ++x) {
            if (figures[tetramino.blockPos[0]][tetramino.blockPos[1]][y - tetramino.position.y][x - tetramino.position.x] && field[y][x]) {
                return true;
            }
        }
    }
    return false;
}

bool Field::CheckToDown()
{
    Tetramino future = tetramino;
    future.MoveDown();
    for (int y = future.position.y; y < future.position.y + 4; ++y) {
        for (int x = future.position.x; x < future.position.x + 4; ++x) {
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && field[y][x]) {
                return false;
            }
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && y == 15) {
                return false;
            }
        }
    }
    return true;
}

bool Field::CheckToLeft()
{
    Tetramino future = tetramino;
    future.MoveLeft();
    for (int y = future.position.y; y < future.position.y + 4; ++y) {
        for (int x = future.position.x; x < future.position.x + 4; ++x) {
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && field[y][x]) {
                return false;
            }
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && x == -1) {
                return false;
            }
        }
    }
    return true;
}

bool Field::CheckToRight()
{
    Tetramino future = tetramino;
    future.MoveRight();
    for (int y = future.position.y; y < future.position.y + 4; ++y) {
        for (int x = future.position.x; x < future.position.x + 4; ++x) {
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && field[y][x]) {
                return false;
            }
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && x == 10) {
                return false;
            }
        }
    }
    return true;
}

bool Field::CheckRotate()
{
    Tetramino future = tetramino;
    future.Rotate();
    for (int y = future.position.y; y < future.position.y + 4; ++y) {
        for (int x = future.position.x; x < future.position.x + 4; ++x) {
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && field[y][x]) {
                return false;
            }
            if (figures[future.blockPos[0]][future.blockPos[1]][y - future.position.y][x - future.position.x] && (y == 15 || x == -1 || x == 10)) {
                return false;
            }
        }
    }
    return true;
}

void Field::CreateField() {
    for (int y = 0; y < 15; ++y) {
        for (int x = 0; x < 10; ++x) {
            field[y][x] = 0;
        }
    }
}

int Field::ClearFullLines() {
    int now_y = 14;
    bool fill = true;
    for (int y = 14; 0 <= y; --y) {
        fill = true;
        for (int x = 0; x < 10; ++x) {
            if (!field[y][x]) {
                fill = false;
                break;
            }
        }
        if (!fill) {
            for (int x = 0; x < 10; ++x) {
                field[now_y][x] = field[y][x];
            }
            now_y -= 1;
        }
    }
    for (int i = 0; i <= now_y; ++i) {
        for (int x = 0; x < 10; ++x) {
            field[now_y][x] = 0;
        }
    }
    now_y += 1;
    if (now_y == 4) return now_y * 100 + 100;
    else return now_y * 100;
}
