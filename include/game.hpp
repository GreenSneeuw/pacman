/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"
#include "maze.hpp"

/// Abstract class with brief description.
///
/// More detailed text.
class Game
{
private:
Maze maze;
bool finished;
std::vector<GameObjectStruct> sprites;

public:
    Game(std::vector<std::vector<int>> map):
    maze(Maze(map)) {};

    std::vector<std::vector<int>> get_map() {return maze.get_map();};
    std::vector<GameObjectStruct> get_objects() {return sprites;};

    void add_object(GameObjectStruct object) {return sprites.push_back(object);};
};

#endif /* GAME_H */
