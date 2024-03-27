/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"
#include "Entity.hpp"

class Player : public Entity
{
private:
int lives;

public:
    Player(int start_x, int start_y, Direction start_dir, int lives):
    Entity(start_x, start_y, PACMAN, start_dir), lives(lives) {};

    int get_lives() override {return lives;};

    GameObjectStruct update(std::vector<std::vector<int>> map) override {
        move(map);
        // collision();
        return get_object();
    };
};

#endif /* PLAYER_H */
