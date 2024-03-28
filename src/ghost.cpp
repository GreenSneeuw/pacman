#include "Ghost.hpp"
#include <cstdlib>
#include <ctime>

void Ghost::movement() {
    switch (self_type) { // very random movement yes
        case BLINKY:
            change_dir(static_cast<Direction>(rand() % 4));
            break;
        case PINKY:
            change_dir(static_cast<Direction>(rand() % 4));
            break;
        case INKY:
            change_dir(static_cast<Direction>(rand() % 4));
            break;
        case CLYDE:
            change_dir(static_cast<Direction>(rand() % 4));
            break;
        default:
            break;
    }
}