#include "game.hpp"

void Game::update_all(){
    if(finished){

    }
    else if(reset){
        for(std::vector<Entity*>::iterator it = entities.get_entities()->begin(); it != entities.get_entities()->end();){
            if ((*it)->get_object().type == PACMAN){
                (*it)->reset(14,15);
            }
            if ((*it)->get_object().type > 0 && (*it)->get_object().type < 5){ // ghosts
                (*it)->reset(14,13);
            }
            it++;
        }
        reset = false;
    }
    else{
        for(std::vector<Entity*>::iterator it = entities.get_entities()->begin(); it != entities.get_entities()->end();){
            if ((*it)->get_object().type < 7){ // below 7 are pacman, ghosts
                (*it)->update(get_map());
            }
            it++;
        }
        // run collision checks after updating, since its updating the same vector!!!
        for(std::vector<Entity*>::iterator it = entities.get_entities()->begin(); it != entities.get_entities()->end();){
            if ((*it)->get_object().type == PACMAN){ // only players do collision checks
                collide_check(*it);
            }
            it++;
        }
    }
}

void Game::collide_check(Entity *input){
    // for(Entity* it : *entities.get_entities()){
    if (input->get_object().type == PACMAN){
        for(std::vector<Entity*>::iterator it = entities.get_entities()->begin(); it != entities.get_entities()->end();){

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
                    *entities.get_entities()->erase(it);
                    input->add_score(100);
                }
                else it++;
            }
            else it++;
        }
    }
}