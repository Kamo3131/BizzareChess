#include "Bishop.hpp"
#include <iostream>
#include <sstream>
std::size_t Bishop::amount = 0;
Bishop::Bishop(const Piece::Team team) : Piece(){
    setTeam(team);
    std::ostringstream ss;
    ss << "Bishop(" << amount << ")";
    setName(ss.str());
    amount++;
}
bool Bishop::move(const int horizontal, const int vertical){
    if(horizontal == 0 && vertical ==0){
        return false; // No movement
    } else if(horizontal == vertical || horizontal == -vertical){
        return true; // Can move diagonally
    } else if(horizontal != 0 && vertical == 0){
        return false; // Can't move horizontally
    } else if(horizontal == 0 && vertical != 0){
        return false; // Can't move vertically
    }
    return false;
}

bool Bishop::attack(const int horizontal, const int vertical){
    return move(horizontal, vertical);
}