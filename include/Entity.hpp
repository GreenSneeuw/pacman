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
private:
    GameObjectStruct self;
    Direction buffered_dir;
    int score = 0;
    int threshold = 1000;
    bool toBeRemoved = false;
    bool toBeScared = false;
    bool toBeMoved = false;

public:
    Entity(int start_x, int start_y, Type type, Direction start_dir):
    self({start_x, start_y, type, start_dir}) {};

    
    int get_score() {return score;}; // score retrieval and adding
    int add_score(int input) {return score += input;};

    int get_threshold() {return threshold;}; // score retrieval and adding
    int add_threshold(int input) {return threshold += input;};

    void markToRemove() {toBeRemoved = true;}; // marking to be erased
    bool getMark() {return toBeRemoved;};

    void scare() {toBeScared = !toBeScared;};  // marking to be set to scared
    bool getScare() {return toBeScared;};

    virtual Type get_realType() {return DOT;}; // return a default value

    void change_dir(Direction input) {buffered_dir = input;}; // movement
    void move(std::vector<std::vector<int>>);
    
    void reset(int x, int y) {self.x = x, self.y = y;}; // resetting
    
    GameObjectStruct get_object() {return self;}; // struct retrieval

    void change_type(Type type) {self.type = type;}; // change type

    // virtual functions
    virtual void movement() {};
    virtual void update(std::vector<std::vector<int>> map) {}; 
    virtual void add_lives(int input) {};
    virtual int get_lives() {return 0;};
};

#endif /* ENTITY_H */
