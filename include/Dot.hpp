/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef DOT_H
#define DOT_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"
#include "Entity.hpp"

class Dot : public Entity
{
public:
    Dot(int x, int y):
    Entity(x, y, DOT, UP) {};
};

#endif /* DOT_H */
