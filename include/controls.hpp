/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef CONTROLS_H
#define CONTROLS_H

#include <string>
#include <vector>
#include "game.hpp"
#include "GameObjectStruct.hpp"
#include <iostream>

/// Abstract class with brief description.
///
/// More detailed text.
class controls
{
    // friend class player;
GameObjectStruct self;
int score = 0;

public:
    controls(int start_x, int start_y, Type type, Direction start_dir):
    self({start_x, start_y, type, start_dir}) {};

    
    int get_score() {return score;};
    GameObjectStruct get_object() {return self;};

    int add_score(int input) {return score += input;}; // also return because why not
    void change_dir(Direction input) {self.dir = input;};

    void move(std::vector<std::vector<int>>);
    void portal();

    virtual GameObjectStruct update(Game game) {return self;}; // update also returns the object

    virtual int get_lives() {return 0;};
};

#endif /* CONTROLS_H */
