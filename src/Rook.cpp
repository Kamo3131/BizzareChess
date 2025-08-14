#include "Rook.hpp"
#include <iostream>
#include <sstream>
std::size_t Rook::amount = 0;
Rook::Rook(const Piece::Team team) : Piece(){
    setType(Piece::Type::ROOK);
    setTeam(team);
    std::ostringstream ss;
    ss << "Rook(" << amount << ")";
    setName(ss.str());
    amount++;
}
bool Rook::move(const int horizontal, const int vertical){
    if(horizontal == 0 && vertical ==0){
        return false; // No movement
    } else if(horizontal != 0 && vertical != 0){
        return false; // Can't move diagonally
    } else if(horizontal != 0 && vertical == 0){
        return true; // Can move horizontally
    } else if(horizontal == 0 && vertical != 0){
        return true; // Can move vertically
    }
    return false;
}

bool Rook::attack(const int horizontal, const int vertical){
    return move(horizontal, vertical);
}