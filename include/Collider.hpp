/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef COLLIDER_H
#define COLLIDER_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"
#include "Entities.hpp"
#include "Entity.hpp"

class Collider
{
public:
    void collision(Entity);
};

#endif /* COLLIDER_H */
