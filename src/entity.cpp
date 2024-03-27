#include "Entity.hpp"

void Entity::move(std::vector<std::vector<int>> map) {

    switch (self.dir){
        case UP:
            if (map[self.y - 1][self.x] == 0) self.y -= 1;
            break;
        case DOWN:
            if (map[self.y + 1][self.x] == 0) self.y += 1;
            break;
        case RIGHT:
            if (map[self.y][self.x + 1] == 0) self.x += 1;
            break;
        case LEFT:
            if (map[self.y][self.x - 1] == 0) self.x -= 1;
            break;
    }
    // portal
    if (self.x < 0) self.x = map[self.y].size();
    else if (self.x > map[self.y].size()) self.x = 0;
    else if (self.y < 0) self.y = map.size();
    else if (self.y > map.size()) self.y = 0;
    
};
