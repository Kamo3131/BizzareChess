#include "Pawn.hpp"
#include <iostream>
#include <sstream>
std::size_t Pawn::amount = 0;
Pawn::Pawn(const Piece::Team team) : Piece(){
    setType(Piece::Type::PAWN);
    setTeam(team);
    std::ostringstream ss;
    ss << "Pawn(" << amount << ")";
    setName(ss.str());
    amount++;
}
bool Pawn::move(const int horizontal, const int vertical){
        if(horizontal != 0){
            return false; // Pawns cannot move horizontally
        } else if((vertical == 1 && getTeam() == Piece::Team::WHITE) || (vertical == -1 && getTeam() == Piece::Team::BLACK)){
            return true; // Can move forward by 1 tile
        } else if((vertical == 2 && getMoveNumber() == 0 && getTeam() == Piece::Team::WHITE) || 
                  (vertical == -2 && getMoveNumber() == 0 && getTeam() == Piece::Team::BLACK)){
            setEnPassant(1, true);
            return true; // Can move forward by 2 tiles on first move
        }
    return false;
}

bool Pawn::attack(const int horizontal, const int vertical){
    return (horizontal==1 || horizontal==-1) && ((vertical==1 && getTeam() == Piece::Team::WHITE) ||
            (vertical==-1 && getTeam() == Piece::Team::BLACK)) ? true : false; // Can attack diagonally by 1 tile
}

std::pair<int, bool> Pawn::getEnPassant() const {
    return enPassant;
}

void Pawn::setEnPassant(int turnsLeft, bool canCapture) {
    enPassant.first = turnsLeft;
    enPassant.second = canCapture;
}