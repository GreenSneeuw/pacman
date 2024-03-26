/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"
#include "maze.hpp"
#include "sprites.hpp"

/// Abstract class with brief description.
///
/// More detailed text.
class Game
{
private:
Maze maze;
bool finished;
Sprites sprites;

public:
    Game(std::vector<std::vector<int>> map):
    maze(Maze(map)) {};

    std::vector<std::vector<int>> get_map() {return maze.get_map();};
    std::vector<GameObjectStruct> get_objects() {return sprites.get_sprites();};

    void add_object(GameObjectStruct object) {sprites.add_sprite(object);};
};

#endif /* GAME_H */
