/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef ENERGIZER_H
#define ENERGIZER_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"
#include "Entity.hpp"

class Energizer : public Entity
{
public:
    Energizer(int x, int y):
    Entity(x, y, ENERGIZER, UP) {};
};

#endif /* DOT_H */
