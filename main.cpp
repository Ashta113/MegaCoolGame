#include "field.hpp"
#include "tetromino.hpp"
#include "coolgame.hpp"
#include <time.h>

int main(int argc, char* argv[]) {
    srand(time(0));
    CoolGame coolgame;
    coolgame.init();
    coolgame.createNewGame();
    coolgame.run();
    return 0;
}