/// \file
/// main.cpp


#include "GameObjectStruct.hpp"
#include "UI.hpp"
#include "Game.hpp"
#include "Entities.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Dot.hpp"
#include "Energizer.hpp"
#include "Ghost.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
// #include <mutex>

/// Callback function to update the game state.
///
/// This function is called by an SDL timer at regular intervals.
/// Note that this callback may happen on a different thread than the main thread.
/// You therefore have to be careful in avoiding data races. For example, you
/// should use mutexes to access shared data.
/// Read the documentation of SDL_AddTimer for more information and for tips
/// regarding multithreading issues.

// std::mutex mutex_lock;
// SDL_mutex *mutex;
struct CallbackParams {
    Game *game;
    Player *player;
};

SDL_mutex *mutex = SDL_CreateMutex();

Uint32 gameUpdate(Uint32 interval, void *param)
{
    // Do game loop update here
    SDL_LockMutex(mutex);
    CallbackParams *params = static_cast<CallbackParams*>(param); 
    Game *game = params->game;
    Player *player = params->player;
    
    // player->update(game->get_map());
    // game->collide_check(player);
    game->update_all();
    SDL_UnlockMutex(mutex);
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
            if (y == 1 && x == 1) {
                game.add_entity(new Energizer(x,y));
            } else if (y == 1 && x == 1) {
                game.add_entity(new Energizer(x,y));
            } else if (y == 1 && x == map.size()-1) {
                game.add_entity(new Energizer(x,y));
            } else if (y == map.size()-2 && x == 1) {
                game.add_entity(new Energizer(x,y));
            } else if (y == map.size()-2 && x == map.size()-1) {
                game.add_entity(new Energizer(x,y));
            } else if (map[y][x] == 0){
                game.add_entity(new Dot(x,y));
            }
        }
    }
    // Create a new ui object
    UI ui(game.get_map()); // <-- use map from your game objects.

   
    // create player
    Player player(14,15,LEFT,3);
    game.add_entity(&player);

    // create ghosts
    game.add_entity(new Ghost(12, 13, BLINKY, UP));
    game.add_entity(new Ghost(13, 13, PINKY, UP));
    game.add_entity(new Ghost(14, 13, INKY, UP));
    game.add_entity(new Ghost(15, 13, CLYDE, UP));
    //set the callback params
    CallbackParams* params = new CallbackParams;
    params->game = &game;
    params->player = &player;

    // Start timer for game update, call this function every 100 ms.
    SDL_TimerID timer_id =
        SDL_AddTimer(100, gameUpdate, params);
    bool quit = false;
    while (!quit) {
        // set timeout to limit frame rate
        // SDL_LockMutex(mutex);
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
                case SDLK_LEFT:
                    player.change_dir(LEFT);
                    break;
                case SDLK_RIGHT:
                    player.change_dir(RIGHT);
                    break;
                case SDLK_UP:
                    player.change_dir(UP);
                    break;
                case SDLK_DOWN:
                    player.change_dir(DOWN);
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                }
            }
        }

        // Set the score
        ui.setScore(player.get_score()); // <-- Pass correct value to the setter

        // Set the amount of lives
        ui.setLives(player.get_lives()); // <-- Pass correct value to the setter

        // Render the scene
        std::vector<GameObjectStruct> objects = {game.get_objects()};
        // ^-- Your code should provide this vector somehow (e.g.
        // game->getStructs())
        
        // SDL_UnlockMutex(mutex);

        ui.update(objects);
        
        while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
            // ... do work until timeout has elapsed
        }
    }

    SDL_RemoveTimer(timer_id);

    return 0;
}
