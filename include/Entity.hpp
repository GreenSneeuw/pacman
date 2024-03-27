/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"

class Entity
{
GameObjectStruct self;
int score = 0;

public:
    Entity(int start_x, int start_y, Type type, Direction start_dir):
    self({start_x, start_y, type, start_dir}) {};

    
    int get_score() {return score;};
    

    int add_score(int input) {return score += input;}; // also return because why not
    void change_dir(Direction input) {self.dir = input;};

    void move(std::vector<std::vector<int>>);
    GameObjectStruct get_object() {return self;};

    virtual GameObjectStruct update(std::vector<std::vector<int>> map) {return self;}; // update also returns the object

    virtual int get_lives() {return 0;};
};

#endif /* ENTITY_H */
