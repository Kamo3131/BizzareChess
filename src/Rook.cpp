#include "Rook.hpp"
#include <iostream>
#include <sstream>
std::size_t Rook::amount = 0;
Rook::Rook(const Piece::Team team) : Piece(){
    setTeam(team);
    std::ostringstream ss;
    ss << "Rook(" << amount << ")";
    setName(ss.str());
    amount++;
}
bool Rook::move(const int horizontal, const int vertical){
    if(horizontal != 0 && vertical != 0){
        return false;
    } else if(horizontal != 0 && vertical == 0){
        return true;

    } else if(horizontal == 0 && vertical != 0){
        return true;
    }
    return false;
}

bool Rook::attack(const int horizontal, const int vertical){
    return move(horizontal, vertical);
}