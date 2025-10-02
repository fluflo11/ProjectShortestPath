#include "agent.hpp"
#include "grid.hpp"
#include <tuple>


std::tuple<int,int> Agent::move(Move move, int x, int y) const {
    int next_x = x;
    int next_y = y;
    switch(move){
        case Move::LEFT:       
            next_x--; 
            break;
        case Move::RIGHT:      
            next_x++; 
            break;
        case Move::UP:         
            next_y--; 
            break;
        case Move::DOWN:       
            next_y++;
            break;
        case Move::LEFT_UP:    
            next_x--; next_y--; 
            break;
        case Move::LEFT_DOWN:  
            next_x--; next_y++; 
            break;
        case Move::RIGHT_UP:   
            next_x++; next_y--; 
            break;
        case Move::RIGHT_DOWN: 
            next_x++; next_y++; 
            break;
    }
    return std::make_tuple(next_x,next_y);
}