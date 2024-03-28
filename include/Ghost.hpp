/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef GHOST_H
#define GHOST_H

#include <string>
#include <vector>
#include <time.h>
#include "GameObjectStruct.hpp"
#include "Entity.hpp"

class Ghost : public Entity
{
private:
    Type self_type;
    bool toBeScared = false;
public:
    Ghost(int start_x, int start_y, Type type, Direction start_dir):
    Entity(start_x, start_y, type, start_dir) {self_type = type;};

    Type get_realType() override {return self_type;};
    
    void movement() override;
    void update(std::vector<std::vector<int>> map) override {
        movement();
        move(map);
    };
};

#endif /* GHOST_H */