#include "Pawn.hpp"
#include <iostream>
#include <sstream>
std::size_t Pawn::amount = 0;
Pawn::Pawn() : Piece(){
    std::ostringstream ss;
    ss << "Pawn(" << amount << ")";
    setName(ss.str());
    amount++;
}
bool Pawn::move(const int horizontal, const int vertical){
    if(horizontal != 0){
        return false;
    } else if(vertical == 1){
        return true;
    } else if(vertical == 2 && getMoveNumber() == 0){
        return true;
    }
    return false;
}

bool Pawn::attack(const int horizontal, const int vertical){
    return (horizontal==1 || horizontal==-1) && vertical==1 ? true : false;
}