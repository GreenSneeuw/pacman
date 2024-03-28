#include "Entity.hpp"

void Entity::move(std::vector<std::vector<int>> map) {
    // portal
    if (self.x < 0) self.x = map[self.y].size() - 1;
    else if (self.x > map[self.y].size()-1) self.x = 0; 
    else if (self.y < 0) self.y = map.size() - 1;
    else if (self.y > map.size()-1) self.y = 0;
    
    else{ // if not portal, do normal movement
        if (buffered_dir != self.dir){ // input buffering
            switch (buffered_dir){
                case UP: // for direction, check if it is valid to change direction
                    if (map[self.y - 1][self.x] == 0) self.dir = buffered_dir;
                    break;
                case DOWN:
                    if (map[self.y + 1][self.x] == 0) self.dir = buffered_dir;
                    break;
                case RIGHT:
                    if (map[self.y][self.x + 1] == 0) self.dir = buffered_dir;
                    break;
                case LEFT:
                    if (map[self.y][self.x - 1] == 0) self.dir = buffered_dir;
                    break;
            }
        }
    
        switch (self.dir){ // normal movement
            case UP: // for direction, check if it is valid to move that way
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
    }
};
