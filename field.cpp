#include "field.hpp"
#include <SDL2/SDL.h>

void Field::CreateField(Field& field_) {
    for (int y = 0; y < 15; ++y) {
        for (int x = 0; x < 10; ++x) {
            field_.field[y][x] = 0;
        }
    }
}
void Field::DrawBorderField(SDL_Renderer* renderer_, Field& field_) {
    SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff);
    SDL_Rect border =
    {
        FIELD_X - 2,
        FIELD_Y - 2,
        FIELD_WIDTH * BLOCK_SIZE + 4,
        FIELD_HEIGHT * BLOCK_SIZE + 4
    };
    SDL_RenderDrawRect(renderer_, &border);
}
void Field::DrawField(SDL_Renderer* renderer_, Field& field_) {
    for (int y = 0; y < 15; ++y) {
        for (int x = 0; x < 10; ++x) {
            if (field[y][x]) {
                SDL_Rect cell = {
                    FIELD_X + BLOCK_SIZE * x,
                    FIELD_Y + BLOCK_SIZE * y,
                    BLOCK_SIZE,
                    BLOCK_SIZE
                };
                SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderFillRect(renderer_, &cell);
            } else {
                SDL_SetRenderDrawColor(renderer_, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderDrawPoint(renderer_, FIELD_X + BLOCK_SIZE * x + BLOCK_SIZE / 2, FIELD_Y + BLOCK_SIZE * y + BLOCK_SIZE / 2);
            }
        }
    }
}

void Field::ClearFullLines(Field& field_) {
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
    while (0 <= now_y) {
        for (int x = 0; x < 10; ++x) {
            field[now_y][x] = 0;
        }
        now_y -= 1;
    }
}

void Field::GameOver(SDL_Renderer* renderer_) {
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
            SDL_Rect cell = {
                FIELD_X + BLOCK_SIZE * x,
                FIELD_Y + BLOCK_SIZE * y,
                BLOCK_SIZE,
                BLOCK_SIZE
            };
            switch (game_over[y][x]) {
                case 0:
                    SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0x00, 0xff);
                    SDL_RenderFillRect(renderer_, &cell);
                    break;
                case 1:
                    SDL_SetRenderDrawColor(renderer_, 0xff, 0x00, 0x00, 0xff);
                    SDL_RenderFillRect(renderer_, &cell);
                    break;
                case 2:
                    SDL_SetRenderDrawColor(renderer_, 0x00, 0xff, 0x00, 0xff);
                    SDL_RenderFillRect(renderer_, &cell);
                    break;
                case 3:
                    SDL_SetRenderDrawColor(renderer_, 0x00, 0x00, 0xff, 0xff);
                    SDL_RenderFillRect(renderer_, &cell);
                    break;
                case 4:
                    SDL_SetRenderDrawColor(renderer_, 0xff, 0x00, 0xff, 0xff);
                    SDL_RenderFillRect(renderer_, &cell);
                    break;
            }
        }
    }
    SDL_RenderPresent(renderer_);
}