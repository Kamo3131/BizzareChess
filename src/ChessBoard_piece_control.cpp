#include "ChessBoard.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Utility.hpp"

#define DEBUG 0

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

bool ChessBoard::piecesCanMove(const Piece::Team team) const{
    #if DEBUG == 1
    std::cout << "Pieces movement\n";
    #endif
    for(int j = static_cast<int>(_vertical)-1; j>-1; j--){
        for(int i = 0; i < static_cast<int>(_horizontal); i++){
            if(pieces[i][j] && pieces[i][j]->getTeam() == team){
                switch (pieces[i][j]->getType())
                {
                case Piece::Type::PAWN:
                #if DEBUG == 1
                    std::cout << pieces[i][j]->getName() << std::endl;
                #endif
                    if(pawnCanMove(i, j, team)){
                        return true;
                    }
                    break;
                case Piece::Type::BISHOP:
                #if DEBUG == 1
                    std::cout << pieces[i][j]->getName() << std::endl;
                #endif
                    if(bishopCanMove(i, j)){
                        return true;
                    }
                    break;
                case Piece::Type::KNIGHT:
                #if DEBUG == 1
                    std::cout << pieces[i][j]->getName() << std::endl;
                #endif
                    if(knightCanMove(i, j)){
                        return true;
                    }
                    break;
                case Piece::Type::QUEEN:
                #if DEBUG == 1
                    std::cout << pieces[i][j]->getName() << std::endl;
                #endif
                    if(queenCanMove(i, j)){
                        return true;
                    }
                    break;
                case Piece::Type::ROOK:
                #if DEBUG == 1
                    std::cout << pieces[i][j]->getName() << std::endl;
                #endif
                    if(rookCanMove(i, j)){
                        return true;
                    }
                    break;
                case Piece::Type::KING:
                #if DEBUG == 1
                    std::cout << pieces[i][j]->getName() << std::endl;
                #endif
                    if(kingCanMove(team)){
                        return true;
                    }
                    break;
                default:
                    break;
                }
            } else{
                continue;
            }
        }
    }
    return false;
}

bool ChessBoard::kingCanMove(const Piece::Team team) const{
    size_pair position;
    if(Piece::Team::WHITE == team){
        position = getWhiteKingsPosition();
    } else{
        position = getBlackKingsPosition();
    }
    int pos_first = static_cast<int>(position.first);
    int pos_second = static_cast<int>(position.second);
    for(int i = 1; i > -2; i--){
        for(int j = 1; j > -2; j--){
            if(((pos_first+i < 0) || (pos_first+i) >= static_cast<int>(_horizontal)) 
                && ((pos_second+j) < 0 || (pos_second+j) >= static_cast<int>(_vertical))){
                continue;
            }
            if(0 == i &&  0 == j){
                continue;
            } else if(canMove(position.first, position.second, i, j)){
                return true;
            }
        }
    }
    return false;
        
}

bool ChessBoard::pawnCanMove(const std::size_t o_x, const std::size_t o_y, const Piece::Team team) const{
    if(Piece::Team::WHITE == team){
        for(int i = 1; i < 3; i++){
            if(canMove(o_x, o_y, 0, i)){
                return true;
            }
        }
        if(canMove(o_x, o_y, 1, 1) || canMove(o_x, o_y, -1, 1)){
            return true;
        }
    } else{
        for(int i = -1; i > -3; i--){
            if(canMove(o_x, o_y, 0, i)){
                return true;
            }
        }
        if(canMove(o_x, o_y, 1, -1) || canMove(o_x, o_y, -1, -1)){
            return true;
        }
    }
    return false;
}
bool ChessBoard::rookCanMove(const std::size_t o_x, const std::size_t o_y) const{
    for(int i = 0; i < static_cast<int>(_horizontal); i++){
        if(i == static_cast<int>(o_x)){
            continue;
        }
        if(canMove(o_x, o_y, i-static_cast<int>(o_x), static_cast<int>(o_y))){
            return true;
        }
    }
    for(int i = 0; i < static_cast<int>(_vertical); i++){
        if(i == static_cast<int>(o_y)){
            continue;
        }
        if(canMove(o_x, o_y, static_cast<int>(o_x), i-static_cast<int>(o_y))){
            return true;
        }
    }
    return false;
}
bool ChessBoard::bishopCanMove(const std::size_t o_x, const std::size_t o_y) const{
    for(int i = 0, j = 0; i < static_cast<int>(_horizontal) && j < static_cast<int>(_vertical); i++, j++){
        if(i == static_cast<int>(o_x) && j == static_cast<int>(o_y)){
            continue;
        }
        if(canMove(o_x, o_y, i - static_cast<int>(o_x), j - static_cast<int>(o_y))){
            return true;
        }
    }
    for(int i = static_cast<int>(_horizontal), j = 0; i > 0 && j < static_cast<int>(_vertical); i--, j++){
        if(i == static_cast<int>(o_x) && j == static_cast<int>(o_y)){
            continue;
        }
        if(canMove(o_x, o_y, i - static_cast<int>(o_x), j - static_cast<int>(o_y))){
            return true;
        }
    }
    return false;
}
bool ChessBoard::knightCanMove(const std::size_t o_x, const std::size_t o_y) const{
    if(canMove(o_x, o_y, 2, 1) || canMove(o_x, o_y, -2, 1) || canMove(o_x, o_y, 2, -1) || canMove(o_x, o_y, -2, -1)
    || canMove(o_x, o_y, 1, 2) || canMove(o_x, o_y, 1, -2) || canMove(o_x, o_y, -1, 2) || canMove(o_x, o_y, -1, -2)){
        return true;
    }
    return false;
}
bool ChessBoard::queenCanMove(const std::size_t o_x, const std::size_t o_y) const{
    for(int i = 0; i < static_cast<int>(_horizontal); i++){
        if(i == static_cast<int>(o_x)){
            continue;
        }
        if(canMove(o_x, o_y, i-static_cast<int>(o_x), static_cast<int>(o_y))){
            return true;
        }
    }
    for(int i = 0; i < static_cast<int>(_vertical); i++){
        if(i == static_cast<int>(o_y)){
            continue;
        }
        if(canMove(o_x, o_y, o_x, i-static_cast<int>(o_y))){
            return true;
        }
    }
    for(int i = 0, j = 0; i < static_cast<int>(_horizontal) && j < static_cast<int>(_vertical); i++, j++){
        if(i == static_cast<int>(o_x) && j == static_cast<int>(o_y)){
            continue;
        }
        if(canMove(o_x, o_y, i - static_cast<int>(o_x), j - static_cast<int>(o_y))){
            return true;
        }
    }
    for(int i = static_cast<int>(_horizontal), j = 0; i > 0 && j < static_cast<int>(_vertical); i--, j++){
        if(i == static_cast<int>(o_x) && j == static_cast<int>(o_y)){
            continue;
        }
        if(canMove(o_x, o_y, i - static_cast<int>(o_x), j - static_cast<int>(o_y))){
            return true;
        }
    }
    return false;
}