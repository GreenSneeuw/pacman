/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"
#include "Maze.hpp"
#include "Entities.hpp"
#include "Entity.hpp"
#include "Fruit.hpp"

class Game
{
private:
Maze maze;
Entities entities;
bool finished = false;
bool reset = false;
int ghosts_eaten = 0;
std::pair<int,int> add_fruit = {-1,-1};

public:
    Game(std::vector<std::vector<int>> map):
    maze(Maze(map)) {};

    std::vector<std::vector<int>> get_map() {return maze.get_map();};
    std::vector<GameObjectStruct> get_objects() {return entities.get_objects();};
    Entities get_entities() {return entities;} 

    void update_all();
    void collide_check(Entity *input, std::vector<Entity*>* entities_vector);

    void add_entity(Entity *entity) {entities.add_Entity(entity);};
};

#endif /* GAME_H */
