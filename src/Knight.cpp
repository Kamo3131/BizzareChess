#include "Knight.hpp"
#include <iostream>
#include <sstream>
std::size_t Knight::amount = 0;
Knight::Knight(const Piece::Team team) : Piece(){
    setType(Piece::Type::KNIGHT);
    setTeam(team);
    std::ostringstream ss;
    ss << "Knight(" << amount << ")";
    setName(ss.str());
    amount++;
}
bool Knight::move(const int horizontal, const int vertical){
    if(horizontal == 0 && vertical ==0){
        return false; // No movement
    } else if((vertical == 2 || vertical == -2) && (horizontal == 1 || horizontal == -1)){
        return true; // Can move vertically by 2 tiles and horizontally by 1 tile
    } else if((horizontal == 2 || horizontal == -2) && (vertical == 1 || vertical == -1)){
        return true; // Can move horizontally by 2 tiles and vertically by 1 tile
    }
    return false;
}

bool Knight::attack(const int horizontal, const int vertical){
    return move(horizontal, vertical);
}