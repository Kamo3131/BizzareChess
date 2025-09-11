#include "ChessBoard.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <array> //for tests only


std::pair<int, int> vector(const std::pair<int, int> a, const std::pair<int, int> b);
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


using size_pair = std::pair<std::size_t, std::size_t>;
size_pair ChessBoard::getWhiteKingsPosition() const{
    return _whiteKingsPosition;
}

size_pair ChessBoard::getBlackKingsPosition() const{
    return _blackKingsPosition;
}

void ChessBoard::setWhiteKingsPosition(const size x, const size y){
    _whiteKingsPosition.first = x;
    _whiteKingsPosition.second = y;
}

void ChessBoard::setBlackKingsPosition(const size x, const size y){
    _blackKingsPosition.first = x;
    _blackKingsPosition.second = y;
}

bool ChessBoard::inCheck(const Piece::Team team){
    size_pair position;
    if(Piece::Team::WHITE == team){
        position = getWhiteKingsPosition();
    } else{
        position = getBlackKingsPosition();
    }

    int x;
    if(static_cast<int>(position.first) - 2 > -1){
        x = static_cast<int>(position.first) - 2;
    } else if(static_cast<int>(position.first) - 1 > -1){
        x = static_cast<int>(position.first) - 1;
    } else{
        x = static_cast<int>(position.first);
    }
    int y;
    if(static_cast<int>(position.second) + 2 < static_cast<int>(_vertical)){
        y = static_cast<int>(position.second) + 2;
    } else if(static_cast<int>(position.second) + 1 < static_cast<int>(_vertical)){
        y = static_cast<int>(position.second) + 1;
    } else{
        y = static_cast<int>(position.second);
    }
    int x_max;
    if(static_cast<int>(position.first) + 2 < static_cast<int>(_horizontal)){
        x_max = static_cast<int>(position.first) + 2;
    } else if(static_cast<int>(position.first) + 1 < static_cast<int>(_horizontal)){
        x_max = static_cast<int>(position.first) + 1;
    } else{
        x_max = static_cast<int>(position.first);
    }
    
    int y_min;
    if(static_cast<int>(position.second) - 2 > -1){
        y_min = static_cast<int>(position.second) - 2;
    } else if(static_cast<int>(position.second) - 1 > -1){
        y_min = static_cast<int>(position.second) - 1;
    } else{
        y_min = static_cast<int>(position.second);
    }
    std::cout << "King at (" << position.first << ", " << position.second << ")\n";
    std::cout << _horizontal << "x" << _vertical << "y" << std::endl;
    std::vector<std::vector<int>> board_check(static_cast<int>(_horizontal), std::vector<int>(static_cast<int>(_vertical), 0));
    board_check[position.first][position.second] = 3; //king position
    int x_min = x, y_max = y;
    bool temp = false;
    for(int i = y; i >= y_min; i--){
        for(int j = x; j<=x_max; j++){
            if(i == static_cast<int>(position.second) && j == static_cast<int>(position.first)){
                continue;
            }
            if(pieces[j][i] && canMove(j, i, vector({j, i}, {position.first, position.second}).first, 
            vector({j, i}, {position.first, position.second}).second)){
                temp = true;
                board_check[j][i] = 2; 
                // return true;
            } 
            else{
                board_check[j][i] = 1;
            }
        }
    }
    if(y_min > 0){
        for(int i = 0; i < y_min; i++){
            if(pieces[position.first][i] && canMove(position.first, i, 0, 
            vector({position.first, i}, {position.first, position.second}).second)){
                temp = true;
                board_check[position.first][i] = 2;
                // return true;
            } 
            else{
                board_check[position.first][i] = 1;
            }
        }
    }
    if(y_max < static_cast<int>(_vertical)-1){
        for(int i = static_cast<int>(_vertical)-1; y_max < i; i--){
            if(pieces[position.first][i] && canMove(position.first, i, 0, 
            vector({position.first, i}, {position.first, position.second}).second)){
                temp = true;
                board_check[position.first][i] = 2;
                // return true;
            } 
            else{
                board_check[position.first][i] = 1;
            }
        }
    }
    if(x_min > 0){
        for(int j = 0; j < x_min; j++){
            if(pieces[j][position.second] && canMove(j, position.second, 
                vector({j, position.second}, {position.first, position.second}).first, 0)){
                temp = true;
                board_check[j][position.second] = 2;
                    // return true;
            }
            else{
                board_check[j][position.second] = 1;
            }
        }
    }
    if(x_max < static_cast<int>(_horizontal)-1){
        for(int j = static_cast<int>(_horizontal)-1; x_max < j; j--){
            if(pieces[j][position.second] && canMove(j, position.second, 
                vector({j, position.second}, {position.first, position.second}).first, 0)){
                temp = true;
                board_check[j][position.second] = 2;
                    // return true;
            }
            else{
                board_check[j][position.second] = 1;
            }
        }
    }

    // 1 math quarter
    if(x_max < static_cast<int>(_horizontal)-1 && y_max < static_cast<int>(_vertical)-1){
        for(int diff = static_cast<int>(_vertical)-1 - y_max > static_cast<int>(_horizontal)-1 - x_max 
        ? static_cast<int>(_horizontal)-1 - x_max : static_cast<int>(_vertical)-1 - y_max
        ; diff > 0; diff--){
            if(pieces[x_max+diff][y_max+diff] && canMove(x_max+diff, y_max+diff, vector({x_max+diff, y_max+diff}, {position.first, position.second}).first, 
            vector({x_max+diff, y_max+diff}, {position.first, position.second}).second)){
                temp = true;
                board_check[x_max+diff][y_max+diff] = 2;
                // return true;
            }
            else{
                board_check[x_max+diff][y_max+diff] = 1;
            }
        }
    }
    // 2 math quarter
    if(x_min > 0 && y_max < static_cast<int>(_vertical)-1){
        for(int diff = static_cast<int>(_vertical)-1 - y_max > x_min ? x_min : static_cast<int>(_vertical)-1 - y_max
        ; diff > 0; diff--){
            if(pieces[x_min-diff][y_max+diff] && canMove(x_min-diff, y_max+diff, vector({x_min-diff, y_max+diff}, 
            {position.first, position.second}).first, vector({x_min-diff, y_max+diff}, 
            {position.first, position.second}).second)){
                temp = true;
                board_check[x_min-diff][y_max+diff] = 2;
                // return true;
            }
            else{
                board_check[x_min-diff][y_max+diff] = 1;
            }
        }
    }
    // 3 math quarter
    if(x_min > 0 && y_min > 0){
        for(int diff = x_min > y_min ? y_min : x_min; diff > 0; diff--){
            if(pieces[x_min-diff][y_min-diff] && canMove(x_min-diff, y_min-diff, vector({x_min-diff, y_min-diff}, {position.first, position.second}).first, 
            vector({x_min-diff, y_min-diff}, {position.first, position.second}).second)){
                temp = true;
                board_check[x_min-diff][y_min-diff] = 2;
                // return true;
            }
            else{
                board_check[x_min-diff][y_min-diff] = 1;
            }
        }
    }
    // 4 math quarter
    if(x_max < static_cast<int>(_horizontal)-1 && y_min > 0){
        for(int diff = static_cast<int>(_horizontal)-1 - x_max > y_min ? y_min : static_cast<int>(_horizontal)-1 - x_max
        ; diff > 0; diff--){
            if(pieces[x_max+diff][y_min-diff] && canMove(x_max+diff, y_min-diff, vector({x_max+diff, y_min-diff}, 
            {position.first, position.second}).first, vector({x_max+diff, y_min-diff}, 
            {position.first, position.second}).second)){
                temp = true;
                board_check[x_max+diff][y_min-diff] = 2;
                // return true;
            }
            else{
                board_check[x_max+diff][y_min-diff] = 1;
            }
        }
    }
    
    for(int j = static_cast<int>(_vertical)-1; j > -1; j--){
        for(int i = 0; i < static_cast<int>(_horizontal); i++){
            std::cout << board_check[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return temp;
}
//utility function
/**
 * @brief vector from point a to point b
 */
std::pair<int, int> vector(const std::pair<int, int> a, const std::pair<int, int> b){
    return {b.first-a.first, b.second-a.second};
}