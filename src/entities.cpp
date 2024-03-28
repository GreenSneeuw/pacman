#include "Entities.hpp"
#include <iostream>

std::vector<GameObjectStruct> Entities::get_objects() {
    std::vector<GameObjectStruct> temp;
    for(Entity* it : entities){ // loop over entities
        temp.emplace_back(it->get_object()); // make list of GameObjectStruct
    };
    return temp;
};