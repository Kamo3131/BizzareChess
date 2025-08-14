#include "King.hpp"
#include <iostream>
#include <sstream>
std::size_t King::amount = 0;
King::King(const Piece::Team team) : Piece(){
    setType(Piece::Type::KING);
    setTeam(team);
    std::ostringstream ss;
    ss << "King(" << amount << ")";
    setName(ss.str());
    amount++;
}
bool King::move(const int horizontal, const int vertical){
    if(horizontal == 0 && vertical ==0){
        return false; // No movement
    } else if((horizontal == 1 || horizontal == -1) && (horizontal == vertical || horizontal == -vertical)){
        return true; // Can move diagonally by 1 tile
    } else if((horizontal == 1 || horizontal == -1) && vertical == 0){
        return true; // Can move horizontally by 1 tile
    } else if(horizontal == 0 && (vertical == 1 || vertical == -1)){
        return true; // Can move vertically by 1 tile
    }
    return false;
}

bool King::attack(const int horizontal, const int vertical){
    return move(horizontal, vertical);
}