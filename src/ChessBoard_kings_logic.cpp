#include "ChessBoard.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <array> //for tests only

#define DEBUG 0

/**
 * @brief vector from point a to point b
 */
std::pair<int, int> vector(const std::pair<int, int> a, const std::pair<int, int> b){
    return {b.first-a.first, b.second-a.second};
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

bool ChessBoard::kingCanMove(const Piece::Team team) const{
    size_pair position;
    if(Piece::Team::WHITE == team){
        position = getWhiteKingsPosition();
    } else{
        position = getBlackKingsPosition();
    }

    for(int i = 1; i > -2; i--){
        for(int j = 1; j > -2; j--){
            if(0 == i &&  0 == j){
                continue;
            } else if(canMove(position.first, position.second, i, j)){
                return true;
            }
        }
    }
    return false;
        
}

bool ChessBoard::inCheck(const Piece::Team team, const size_pair position) const{
    size_pair original_kings_position = position;
    if(!pieces[position.first][position.second]){
        if(team == Piece::Team::WHITE){
            original_kings_position = getWhiteKingsPosition();
        } else{
            original_kings_position = getBlackKingsPosition();
        }
        pieces[position.first][position.second] 
        = std::move(pieces[original_kings_position.first][original_kings_position.second]);
    }
    #if DEBUG == 1
    printBoard();
    #endif

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
    #if DEBUG == 1
    std::cout << "King at (" << position.first << ", " << position.second << ")\n";
    std::cout << _horizontal << "x" << _vertical << "y" << std::endl;
    std::vector<std::vector<int>> board_check(static_cast<int>(_horizontal), std::vector<int>(static_cast<int>(_vertical), 0));
    board_check[position.first][position.second] = 3; //king position
    #endif
    int x_min = x, y_max = y;
    bool temp = false;
    for(int i = y; i >= y_min; i--){
        for(int j = x; j<=x_max; j++){
            if(i == static_cast<int>(position.second) && j == static_cast<int>(position.first)){
                continue;
            }
            if(pieces[j][i] && canAttackKing(j, i, vector({j, i}, {position.first, position.second}).first, 
            vector({j, i}, {position.first, position.second}).second)){
                temp = true;
                #if DEBUG == 1
                board_check[j][i] = 2; 
                #endif
                // return true;
            } 
            #if DEBUG == 1
            else{
                board_check[j][i] = 1;
            }
            #endif
        }
    }
    if(y_min > 0){
        for(int i = 0; i < y_min; i++){
            if(pieces[position.first][i] && canAttackKing(position.first, i, 0, 
            vector({position.first, i}, {position.first, position.second}).second)){
                temp = true;
                #if DEBUG == 1
                board_check[position.first][i] = 2;
                #endif
                // return true;
            } 
            #if DEBUG == 1
            else{
                board_check[position.first][i] = 1;
            }
            #endif
        }
    }
    if(y_max < static_cast<int>(_vertical)-1){
        for(int i = static_cast<int>(_vertical)-1; y_max < i; i--){
            if(pieces[position.first][i] && canAttackKing(position.first, i, 0, 
            vector({position.first, i}, {position.first, position.second}).second)){
                temp = true;
                #if DEBUG == 1
                board_check[position.first][i] = 2;
                #endif
                // return true;
            } 
            #if DEBUG == 1
            else{
                board_check[position.first][i] = 1;
            }
            #endif
        }
    }
    if(x_min > 0){
        for(int j = 0; j < x_min; j++){
            if(pieces[j][position.second] && canAttackKing(j, position.second, 
                vector({j, position.second}, {position.first, position.second}).first, 0)){
                temp = true;
                #if DEBUG == 1
                board_check[j][position.second] = 2;
                #endif
                    // return true;
            }
            #if DEBUG == 1
            else{
                board_check[j][position.second] = 1;
            }
            #endif
        }
    }
    if(x_max < static_cast<int>(_horizontal)-1){
        for(int j = static_cast<int>(_horizontal)-1; x_max < j; j--){
            if(pieces[j][position.second] && canAttackKing(j, position.second, 
                vector({j, position.second}, {position.first, position.second}).first, 0)){
                temp = true;
                #if DEBUG == 1
                board_check[j][position.second] = 2;
                #endif
                    // return true;
            }
            #if DEBUG == 1
            else{
                board_check[j][position.second] = 1;
            }
            #endif
        }
    }

    // 1 math quarter
    if(x_max < static_cast<int>(_horizontal)-1 && y_max < static_cast<int>(_vertical)-1){
        for(int diff = static_cast<int>(_vertical)-1 - y_max > static_cast<int>(_horizontal)-1 - x_max 
        ? static_cast<int>(_horizontal)-1 - x_max : static_cast<int>(_vertical)-1 - y_max
        ; diff > 0; diff--){
            if(pieces[x_max+diff][y_max+diff] && canAttackKing(x_max+diff, y_max+diff, vector({x_max+diff, y_max+diff}, {position.first, position.second}).first, 
            vector({x_max+diff, y_max+diff}, {position.first, position.second}).second)){
                temp = true;
                #if DEBUG == 1
                board_check[x_max+diff][y_max+diff] = 2;
                #endif
                // return true;
            }
            #if DEBUG == 1
            else{
                board_check[x_max+diff][y_max+diff] = 1;
            }
            #endif
        }
    }
    // 2 math quarter
    if(x_min > 0 && y_max < static_cast<int>(_vertical)-1){
        for(int diff = static_cast<int>(_vertical)-1 - y_max > x_min ? x_min : static_cast<int>(_vertical)-1 - y_max
        ; diff > 0; diff--){
            if(pieces[x_min-diff][y_max+diff] && canAttackKing(x_min-diff, y_max+diff, vector({x_min-diff, y_max+diff}, 
            {position.first, position.second}).first, vector({x_min-diff, y_max+diff}, 
            {position.first, position.second}).second)){
                temp = true;
                #if DEBUG == 1
                board_check[x_min-diff][y_max+diff] = 2;
                #endif
                // return true;
            }
            #if DEBUG == 1
            else{
                board_check[x_min-diff][y_max+diff] = 1;
            }
            #endif
        }
    }
    // 3 math quarter
    if(x_min > 0 && y_min > 0){
        for(int diff = x_min > y_min ? y_min : x_min; diff > 0; diff--){
            if(pieces[x_min-diff][y_min-diff] && canAttackKing(x_min-diff, y_min-diff, vector({x_min-diff, y_min-diff}, {position.first, position.second}).first, 
            vector({x_min-diff, y_min-diff}, {position.first, position.second}).second)){
                temp = true;
                #if DEBUG == 1
                board_check[x_min-diff][y_min-diff] = 2;
                #endif
                // return true;
            }
            #if DEBUG == 1
            else{
                board_check[x_min-diff][y_min-diff] = 1;
            }
            #endif
        }
    }
    // 4 math quarter
    if(x_max < static_cast<int>(_horizontal)-1 && y_min > 0){
        for(int diff = static_cast<int>(_horizontal)-1 - x_max > y_min ? y_min : static_cast<int>(_horizontal)-1 - x_max
        ; diff > 0; diff--){
            if(pieces[x_max+diff][y_min-diff] && canAttackKing(x_max+diff, y_min-diff, vector({x_max+diff, y_min-diff}, 
            {position.first, position.second}).first, vector({x_max+diff, y_min-diff}, 
            {position.first, position.second}).second)){
                temp = true;
                #if DEBUG == 1
                board_check[x_max+diff][y_min-diff] = 2;
                #endif
                // return true;
            }
            #if DEBUG == 1
            else{
                board_check[x_max+diff][y_min-diff] = 1;
            }
            #endif
        }
    }
    
    if(!pieces[original_kings_position.first][original_kings_position.second]){
        pieces[original_kings_position.first][original_kings_position.second] 
        = std::move(pieces[position.first][position.second]);
    }
    #if DEBUG == 1
    printBoard();

    for(int j = static_cast<int>(_vertical)-1; j > -1; j--){
        for(int i = 0; i < static_cast<int>(_horizontal); i++){
            std::cout << board_check[i][j] << " ";
        }
        std::cout << std::endl;
    }
    #endif
    return temp;
}

bool ChessBoard::inCheck(const Piece::Team team) const{
    size_pair position;
    if(Piece::Team::WHITE == team){
        position = getWhiteKingsPosition();
    } else{
        position = getBlackKingsPosition();
    }

    return inCheck(team, position);
}

bool ChessBoard::inCheckmate(const Piece::Team team) const{
    #if DEBUG == 1
    bool temp = false;
    #endif
    if(inCheck(team) && !kingCanMove(team)){
        #if DEBUG == 1
        std::cout << "Checkmate!\n";
        temp = true;
        #endif
        return true;
    }
    #if DEBUG == 1
    return temp;
    #endif
    return false;
    
}