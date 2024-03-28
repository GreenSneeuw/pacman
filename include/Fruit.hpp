/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef FRUIT_H
#define FRUIT_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"
#include "Entity.hpp"

class Fruit : public Entity
{
public:
    Fruit(int x, int y):
    Entity(x, y, static_cast<Type>(7 + (rand() % 6)), UP) {};

    Type change_fruit() override {return static_cast<Type>(7 + (rand() % 6));};
};

#endif /* FRUIT_H */
