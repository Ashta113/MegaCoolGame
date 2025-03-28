#pragma once

#include "field.hpp"
#include <SDL2/SDL.h>

inline int figures[7][4][4][4]
{    
    0, 0, 1, 0, // I 0 deg
    0, 0, 1, 0, 
    0, 0, 1, 0, 
    0, 0, 1, 0, 

    0, 0, 0, 0, // I 90 deg
    1, 1, 1, 1, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    0, 0, 1, 0, // I 180 deg
    0, 0, 1, 0, 
    0, 0, 1, 0, 
    0, 0, 1, 0, 

    0, 0, 0, 0, // I 270 deg
    1, 1, 1, 1, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    // ******************** //

    0, 0, 1, 1, // S 0 deg
    0, 1, 1, 0, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    0, 1, 0, 0, // S 90 deg
    0, 1, 1, 0, 
    0, 0, 1, 0, 
    0, 0, 0, 0, 

    0, 0, 1, 1, // S 180 deg
    0, 1, 1, 0, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    0, 1, 0, 0, // S 270 deg
    0, 1, 1, 0, 
    0, 0, 1, 0, 
    0, 0, 0, 0, 

    // ******************** //

    0, 1, 1, 0, // Z 0 deg
    0, 0, 1, 1, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    0, 0, 1, 0, // Z 90 deg
    0, 1, 1, 0, 
    0, 1, 0, 0, 
    0, 0, 0, 0, 

    0, 1, 1, 0, // Z 180 deg
    0, 0, 1, 1, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    0, 0, 1, 0, // Z 270 deg
    0, 1, 1, 0, 
    0, 1, 0, 0, 
    0, 0, 0, 0, 

    // ******************** //

    0, 0, 0, 0, // T 0 deg
    0, 1, 1, 1, 
    0, 0, 1, 0, 
    0, 0, 0, 0, 

    0, 0, 1, 0, // T 90 deg
    0, 0, 1, 1, 
    0, 0, 1, 0, 
    0, 0, 0, 0, 

    0, 0, 1, 0, // T 180 deg
    0, 1, 1, 1, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    0, 0, 1, 0, // T 270 deg
    0, 1, 1, 0, 
    0, 0, 1, 0, 
    0, 0, 0, 0, 

    // ******************** //

    0, 0, 1, 0, // L 0 deg
    0, 0, 1, 0, 
    0, 0, 1, 1, 
    0, 0, 0, 0, 

    0, 0, 0, 1, // L 90 deg
    0, 1, 1, 1, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    0, 1, 1, 0, // L 180 deg
    0, 0, 1, 0, 
    0, 0, 1, 0, 
    0, 0, 0, 0, 

    0, 0, 0, 0, // L 270 deg
    0, 1, 1, 1, 
    0, 1, 0, 0, 
    0, 0, 0, 0, 

    // ******************** //

    0, 0, 1, 0, // J 0 deg
    0, 0, 1, 0, 
    0, 1, 1, 0, 
    0, 0, 0, 0, 

    0, 0, 0, 0, // J 90 deg
    0, 1, 1, 1, 
    0, 0, 0, 1, 
    0, 0, 0, 0, 

    0, 0, 1, 1, // J 180 deg
    0, 0, 1, 0, 
    0, 0, 1, 0, 
    0, 0, 0, 0, 

    0, 1, 0, 0, // J 270 deg
    0, 1, 1, 1, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    // ******************** //

    0, 1, 1, 0, // O 0 deg
    0, 1, 1, 0, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    0, 1, 1, 0, // O 90 deg
    0, 1, 1, 0, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    0, 1, 1, 0, // O 180 deg
    0, 1, 1, 0, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 

    0, 1, 1, 0, // O 270 deg
    0, 1, 1, 0, 
    0, 0, 0, 0, 
    0, 0, 0, 0,
};

class Tetramino
{
public:
    int color { };
    int type { };
    int blockPos[2] { };

    struct Coordinates
    {
        int x;
        int y;
    } position;

    void SplitToField(Field& field_, Tetramino& tetramino_);
    void CreateTetramino(Field& field_, Tetramino& tetramino_);
    void DrawTetramino(SDL_Renderer* renderer_, Field& field_, Tetramino& tetramino_);
    bool CheckGameOver(Field& field_, Tetramino& tetramino_);
    bool CheckToDown(Field& field_, Tetramino& tetramino_);
    bool CheckToLeft(Field& field_, Tetramino& tetramino_);
    bool CheckToRight(Field& field_, Tetramino& tetramino_);
    bool CheckRotate(Field& field_, Tetramino& tetramino_);
    void MoveDown(Tetramino& tetramino_);
    void MoveLeft(Tetramino& tetramino_);
    void MoveRight(Tetramino& tetramino_);
    void Rotate(Tetramino& tetramino_);
private:

};