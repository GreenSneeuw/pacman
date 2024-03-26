/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"
#include "controls.hpp"

class player : public controls
{
private:
int lives;

public:
    player(int start_x, int start_y, Type type, Direction start_dir, int lives):
    controls(start_x, start_y, type, start_dir), lives(lives) {};

    // GameObjectStruct get_object() {return self;}
    // void move(Direction input) override {
    //     self.dir = input;
    // };

    int get_lives() override {return lives;};

    GameObjectStruct update(Game game) override {
        move(game.get_map());
        return get_object();
    };
};

#endif /* PLAYER_H */
