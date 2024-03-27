/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef ENTITIES_H
#define ENTITIES_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"
#include "Entity.hpp"

class Entities
{
private:
std::vector<Entity*> entities;

public:
    std::vector<GameObjectStruct> get_objects();
    std::vector<Entity*>* get_entities() {return &entities;};

    void add_Entity(Entity *entity) {entities.emplace_back(entity);};
};

#endif /* ENTITIES_H */
