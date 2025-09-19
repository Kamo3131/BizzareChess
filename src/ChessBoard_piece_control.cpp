#include "ChessBoard.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

bool ChessBoard::isPieceAt(const std::size_t o_x, const std::size_t o_y) const {
    return pieces[o_x][o_y] != nullptr;
}

void ChessBoard::killPiece(const std::size_t o_x, const std::size_t o_y){
    std::cout << pieces[o_x][o_y]->getName() << " at (" << o_x << ", " << o_y << ") has been slayed." << std::endl;
    pieces[o_x][o_y] = nullptr;
}

void ChessBoard::healPiece(const std::size_t o_x, const std::size_t o_y, const int health){
    if(pieces[o_x][o_y] != nullptr){
        const int current_health = pieces[o_x][o_y]->getHealth();
        pieces[o_x][o_y]->setHealth(current_health + health);
        std::cout << pieces[o_x][o_y]->getName() << " at (" << o_x << ", " << o_y << ") has been healed by " << health << ". New health: " << pieces[o_x][o_y]->getHealth() << "." << std::endl;
    } else {
        std::cout << "No piece at (" << o_x << ", " << o_y << ") to heal." << std::endl;
    }
}

int ChessBoard::getHealthOfPiece(const std::size_t o_x, const std::size_t o_y) const {
    if(o_x < getHorizontal() && o_y < getVertical() && pieces[o_x][o_y] != nullptr){
        return pieces[o_x][o_y]->getHealth();
    }
    return -1; // or throw an exception
}
void ChessBoard::damagePiece(const std::size_t o_x, const std::size_t o_y){
    if(pieces[o_x][o_y] != nullptr){
        const int health = pieces[o_x][o_y]->getHealth();
        const int damage = pieces[o_x][o_y]->getDamage();
        if(health - damage <= 0){
            killPiece(o_x, o_y);
        } else{
            pieces[o_x][o_y]->setHealth(health - damage);
            std::cout << pieces[o_x][o_y]->getName() << " at (" << o_x << ", " << o_y << ") has been damaged by " << damage << ". Remaining health: " << pieces[o_x][o_y]->getHealth() << "." << std::endl;
        }
    } else {
        std::cout << "No piece at (" << o_x << ", " << o_y << ") to damage." << std::endl;
    }
}

void ChessBoard::damagePiece(const std::size_t o_x, const std::size_t o_y, const int damage){
    if(pieces[o_x][o_y] != nullptr){
        const int health = pieces[o_x][o_y]->getHealth();
        if(health - damage <= 0){
            killPiece(o_x, o_y);
        } else{
            pieces[o_x][o_y]->setHealth(health - damage);
            std::cout << pieces[o_x][o_y]->getName() << " at (" << o_x << ", " << o_y << ") has been damaged by " << damage << ". Remaining health: " << pieces[o_x][o_y]->getHealth() << "." << std::endl;
        }
    } else {
        std::cout << "No piece at (" << o_x << ", " << o_y << ") to damage." << std::endl;
    }
}

int ChessBoard::getDamageOfPiece(const std::size_t o_x, const std::size_t o_y) const {
    if(o_x < getHorizontal() && o_y < getVertical() && pieces[o_x][o_y] != nullptr){
        return pieces[o_x][o_y]->getDamage();
    }
    return -1; // or throw an exception
}
Piece::Team ChessBoard::getTeamOfPiece(const std::size_t o_x, const std::size_t o_y) const{
    if(o_x < getHorizontal() && o_y < getVertical() && pieces[o_x][o_y] != nullptr){
        return pieces[o_x][o_y]->getTeam();
    }
    return Piece::Team::WHITE; // or throw an exception, or return a default value
}

void ChessBoard::enPassantTurnUpdate(const Piece::Team team){
    for(size i = 0; i < _horizontal; i++){
        for(size j = 0; j < _vertical; j++){
            if(pieces[i][j] && pieces[i][j]->getTeam() == team && pieces[i][j]->getType() == Piece::Type::PAWN){
                Pawn* pawn = dynamic_cast<Pawn*>(pieces[i][j].get());
                if(pawn->getEnPassant().first > 0){
                    pawn->setEnPassant(pawn->getEnPassant().first - 1, pawn->getEnPassant().first - 1 > 0);
                } else if((pawn->getEnPassant().first == 0 || (pawn->getEnPassant().first < 0 && pawn->getEnPassant().first != -999)) && 
                          pawn->getEnPassant().second == true){
                    pawn->setEnPassant(0, false);
                }
            }
        }
    }
}

//utility function
