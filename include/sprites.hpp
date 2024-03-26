/*
 * Copyright license (in comments that doxygen does not parse)
 */

#ifndef SPRITES_H
#define SPRITES_H

#include <string>
#include <vector>
#include "GameObjectStruct.hpp"

/// Abstract class with brief description.
///
/// More detailed text.
class Sprites
{
private:
std::vector<GameObjectStruct> sprites;

public:
    std::vector<GameObjectStruct> get_sprites() {return sprites;};
    void add_sprite(GameObjectStruct object) {sprites.push_back(object);};
};

#endif /* SPRITES_H */
