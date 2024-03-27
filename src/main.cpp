/// \file
/// main.cpp


#include "GameObjectStruct.hpp"
#include "UI.hpp"
#include "game.hpp"
#include "player.hpp"
#include "Entities.hpp"
#include "Entity.hpp"
#include "dot.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

/// Callback function to update the game state.
///
/// This function is called by an SDL timer at regular intervals.
/// Note that this callback may happen on a different thread than the main thread.
/// You therefore have to be careful in avoiding data races. For example, you
/// should use mutexes to access shared data.
/// Read the documentation of SDL_AddTimer for more information and for tips
/// regarding multithreading issues.
Uint32 gameUpdate(Uint32 interval, void * /*param*/)
{
    // Do game loop update here
    return interval;
}

/// Program entry point.
int main(int /*argc*/, char ** /*argv*/)
{
    std::vector<std::vector<int>> map = {{
        #include "board.def"
    }};
    Game game(map);

    for(int y = 0; y < map.size(); y++){
        for (int x = 0; x < map[y].size(); x++){
            if (map[y][x] == 0){
                game.add_entity(new Dot(x,y));
            }
        }
    }
    // Create a new ui object
    UI ui(game.get_map()); // <-- use map from your game objects.

    // Start timer for game update, call this function every 100 ms.
    SDL_TimerID timer_id =
        SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));

    // Example object, this can be removed later
    Player player(1,1,DOWN,3);
    
    // Call game init code here
    game.add_entity(&player);

    bool quit = false;
    while (!quit) {
        // set timeout to limit frame rate
        Uint32 timeout = SDL_GetTicks() + 20;

        // Handle the input
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            // Quit button.
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // All keydown events
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT: // YOUR CODE HERE
                    player.change_dir(LEFT);
                    break;
                case SDLK_RIGHT: // YOUR CODE HERE
                    player.change_dir(RIGHT);
                    break;
                case SDLK_UP: // YOUR CODE HERE
                    player.change_dir(UP);
                    break;
                case SDLK_DOWN: // YOUR CODE HERE
                    player.change_dir(DOWN);
                    break;
                case SDLK_SPACE:
                    player.add_score(100);
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
            }
        }
        player.update(game.get_map());
        // Set the score
        ui.setScore(player.get_score()); // <-- Pass correct value to the setter

        // Set the amount of lives
        ui.setLives(player.get_lives()); // <-- Pass correct value to the setter

        // Render the scene
        // std::vector<GameObjectStruct> objects = {player.get_object()};
        std::vector<GameObjectStruct> objects = {game.get_objects()};
        // ^-- Your code should provide this vector somehow (e.g.
        // game->getStructs())
        ui.update(objects);

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
            // ... do work until timeout has elapsed
        }
    }

    SDL_RemoveTimer(timer_id);

    return 0;
}
