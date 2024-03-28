#include "Game.hpp"
#include "time.h"
#include <cmath>

u_int32_t start_time = 0;
void Game::update_all(){
    std::vector<Entity*>* entities_vector = entities.get_entities();
    if(finished){

    }
    else if(reset){ // reset when pacman dies
        for(std::vector<Entity*>::iterator it = entities_vector->begin(); it != entities_vector->end();it++){
            if ((*it)->get_object().type == PACMAN){
                (*it)->reset(14,15);
            }
            if ((*it)->get_object().type > 0 && (*it)->get_object().type < 5){ // ghosts
                (*it)->reset(14,13);
            }
            // it++;
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
        // remove marked entities
        for(std::vector<Entity*>::iterator it = entities_vector->begin(); it != entities_vector->end();){
            if((*it)->getScare() && time(NULL) - start_time == 8){
                (*it)->change_type((*it)->get_realType());  // reset scared to original type
                (*it)->scare();
                ghosts_eaten = 0;
            } else if((*it)->getScare()){
                (*it)->change_type(SCARED);
            }
            if((*it)->getMark()){
                *entities_vector->erase(it);
            }
            else {
                it++;
            }
        }
    }
}

void Game::collide_check(Entity *input, std::vector<Entity*>* entities_vector){
    // for(Entity* it : *entities_vector){
    if (input->get_object().type == PACMAN){
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
                            input->add_score(200*std::pow(2,ghosts_eaten)); // 200 multiplied by 2^(n) with n ghosts eaten
                            ghosts_eaten++;
                            (*it)->reset(14,13);
                            (*it)->scare();
                            (*it)->change_type((*it)->get_realType());  // reset scared to original type
                            input->add_score(500);
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
                            }
                            break;
                    }
                }
            }
        }
    }
}