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
int lives; // store lives per player

public:
    Player(int start_x, int start_y, Direction start_dir, int lives):
    Entity(start_x, start_y, PACMAN, start_dir), lives(lives) {};

    void add_lives(int input) override {lives += input;}; // player unique function override
    int get_lives() override {return lives;};

    void update(std::vector<std::vector<int>> map) override {
        move(map);
    };
};

#endif /* PLAYER_H */
