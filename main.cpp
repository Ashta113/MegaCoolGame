#include "field.hpp"
#include "tetromino.hpp"
#include "coolgame.hpp"
#include <SDL2/SDL.h>
#include <time.h>

int main(int argc, char* argv[]) {
    srand(time(0));
    CoolGame coolgame;
    coolgame.init();
    coolgame.run();
    return 0;
}