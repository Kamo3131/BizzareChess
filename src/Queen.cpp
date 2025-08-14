#include "Queen.hpp"
#include <iostream>
#include <sstream>
std::size_t Queen::amount = 0;
Queen::Queen(const Piece::Team team) : Piece(){
    setType(Piece::Type::QUEEN);
    setTeam(team);
    std::ostringstream ss;
    ss << "Queen(" << amount << ")";
    setName(ss.str());
    amount++;
}
bool Queen::move(const int horizontal, const int vertical){
    if(horizontal == 0 && vertical == 0){
        return false; // No movement
    } else if(horizontal == vertical || horizontal == -vertical){
        return true; // Can move diagonally
    } else if(horizontal != 0 && vertical == 0){
        return true; // Can move horizontally
    } else if(horizontal == 0 && vertical != 0){
        return true; // Can move vertically
    }
    return false;
}

bool Queen::attack(const int horizontal, const int vertical){
    return move(horizontal, vertical);
}