#include "game.hpp"

void Game::collide_check(Entity *input){
    // for(Entity* it : *entities.get_entities()){
    for(std::vector<Entity*>::iterator it = entities.get_entities()->begin(); it != entities.get_entities()->end();){
        if ((*it)->get_object().x == input->get_object().x && (*it)->get_object().y == input->get_object().y){
            if ((*it)->get_object().type == DOT && input->get_object().type == PACMAN){
                *entities.get_entities()->erase(it);
                input->add_score(100);
            }
            else it++;
            
        }
        else it++;
    }
}