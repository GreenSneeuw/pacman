#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"

class Maze
{
private:
std::vector<std::vector<int>> maze; // 2d array for the map
public:
    Maze(std::vector<std::vector<int>> map):
    maze(map) {};

    std::vector<std::vector<int>> get_map() {return maze;};
    
};


#endif /* MAZE_H */