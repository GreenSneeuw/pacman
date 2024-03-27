/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef GHOST_H
#define GHOST_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"
#include "Entity.hpp"

class Ghost : public Entity
{
private:
    Type self_type;
public:
    Ghost(int start_x, int start_y, Type type, Direction start_dir):
    Entity(start_x, start_y, type, start_dir) {self_type = type;};

    void movement() override;

    void update(std::vector<std::vector<int>> map) override {
        movement();
        move(map);
        // collision();
    };
};

#endif /* GHOST_H */
