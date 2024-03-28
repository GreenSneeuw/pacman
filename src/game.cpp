#include "Game.hpp"

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

            if ((*it)->get_object().x == input->get_object().x && (*it)->get_object().y == input->get_object().y){ // a collision
                if ((*it)->get_object().type > 0 && (*it)->get_object().type < 5){
                    input->add_lives(-1);
                    if (input->get_lives() < 1){
                        finished = true;
                    }
                    else{
                        reset = true;
                    }
                }
                if ((*it)->get_object().type == SCARED){
                    // scared collision
                }
                if ((*it)->get_object().type == DOT){
                    // *entities_vector->erase(it);
                    (*it)->markToRemove();
                    input->add_score(100);
                }
                // else it++;
            }
            // else it++;
        }
    }
}