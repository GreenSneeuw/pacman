#include "Game.hpp"
#include <ctime>
#include <cmath>

u_int32_t start_time = 0;

void Game::update_all(){
    std::vector<Entity*>* entities_vector = entities.get_entities();
    if(finished){
        // do nothing, just pause game
    }
    else if(reset){ // reset when pacman dies
        for(std::vector<Entity*>::iterator it = entities_vector->begin(); it != entities_vector->end();it++){
            if ((*it)->get_object().type == PACMAN){
                (*it)->reset(14,15);
            }
            if ((*it)->get_object().type > 0 && (*it)->get_object().type < 5){ // ghosts
                (*it)->reset(14,13);
            }
        }
        reset = false;
    }
    else{ // default update
        for(std::vector<Entity*>::iterator it = entities_vector->begin(); it != entities_vector->end();it++){
            if ((*it)->get_object().type == PACMAN){ // only players do collision checks
                collide_check(*it, entities_vector);
            }
            if ((*it)->get_object().type < 7){ // below 7 are pacman, ghosts
                (*it)->update(get_map());
            }
            if ((*it)->get_object().type == PACMAN){ // only players do collision checks
                collide_check(*it, entities_vector);
            }
        }
        // another loop for other stuff
        for(std::vector<Entity*>::iterator it = entities_vector->begin(); it != entities_vector->end();){
            if ((*it)->get_object().type == PACMAN){ // fruits
                if ((*it)->get_score() > (*it)->get_threshold()){
            int x, y;
            std::vector<std::vector<int>> map = maze.get_map();
            while (1){
                x = rand() % map[0].size(); // get a random position
                y = rand() % map.size();
                if (map[y][x] == 0){break;} // check if the position is valid
            }
            add_fruit = {x, y}; // set the values to be added later
            (*it)->add_threshold(1000);
        }
            }
            if((*it)->getScare()){ // 8 seconds
                u_int32_t scared_time = time(NULL) - start_time;
                if (scared_time > 7){
                    (*it)->change_type((*it)->get_realType());  // reset scared to original type
                    (*it)->scare();
                    ghosts_eaten = 0; // reset the counter for increased score
                }
                else if (scared_time > 4){ // make ghost flicker after 5 seconds
                    switch ((*it)->get_object().type){
                        case SCARED:
                            (*it)->change_type(SCAREDINV);
                            break;
                        case SCAREDINV:
                            (*it)->change_type(SCARED);
                            break;
                        default:
                            break;
                    }
                }
                else{
                    (*it)->change_type(SCARED); // make scared
                }
            }
            if((*it)->getMark()){ // erase marked from list
                *entities_vector->erase(it);
            } 
            else {
                it++;
            }
        }
        if (add_fruit.first != -1){ // add fruit
            add_entity(new Fruit (add_fruit.first, add_fruit.second));
            add_fruit = {-1,-1};
        }
    }
}

void Game::collide_check(Entity *input, std::vector<Entity*>* entities_vector){

    if (input->get_object().type == PACMAN){ // check if the input really is pacman
        for(std::vector<Entity*>::iterator it = entities_vector->begin(); it != entities_vector->end();it++){
            if ((*it)->get_object().type != PACMAN){ // skip the cycle when the iterator is pacman
                if ((*it)->get_object().x == input->get_object().x && (*it)->get_object().y == input->get_object().y){ // a collision when x and y are equal for the object and input
                    Type type = (*it)->get_object().type; // get the object type
                    switch (type){
                        case DOT:
                            (*it)->markToRemove();
                            input->add_score(10); // 10 points for a dot
                            break;

                        case ENERGIZER:
                            (*it)->markToRemove();
                            input->add_score(50); // 50 points for an energizer
                            start_time = time(NULL);
                            for(std::vector<Entity*>::iterator it2 = entities_vector->begin(); it2 != entities_vector->end();it2++){ // iterate again to find all live ghosts
                                Type type2 = (*it2)->get_object().type;
                                if (type2 > 0 && type2 < 5){ // live ghotss
                                    (*it2)->scare();
                                }
                            }
                            break;

                        case SCARED:
                        case SCAREDINV:
                            input->add_score(200*std::pow(2,ghosts_eaten)); // 200 multiplied by 2^(n) with n ghosts eaten
                            ghosts_eaten++;
                            (*it)->reset(14,13); // reset the ghost
                            (*it)->scare(); // remove scared status
                            (*it)->change_type((*it)->get_realType());  // reset scared to original type
                            break;

                        default:
                            if (type > 0 && type < 5){ // live ghosts
                                input->add_lives(-1);
                                if (input->get_lives() < 1){
                                    finished = true;
                                }
                                else{
                                    reset = true;
                                }
                            } else if (type > 6 && type < 13){ // fruits
                                (*it)->markToRemove();
                                input->add_score(100 * (type-5)); // points for a fruit
                            }
                            break;
                    }
                }
            }
        }
    }
}