#include "ChessBoard.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
void ChessBoard::init(){
    for(std::size_t i = 0; i<_horizontal; i++){
            std::vector<std::unique_ptr<Piece>> column;
            for(std::size_t j = 0; j<_vertical; j++){
                column.push_back(nullptr);
            }
            pieces.push_back(std::move(column));
        }
}

void ChessBoard::initPieces(){
}
ChessBoard::ChessBoard() : _horizontal{8}, _vertical{8}{
    init();
}
ChessBoard::ChessBoard(const size horizontal, const size vertical) : _horizontal{horizontal>26 ? 26 : horizontal}, _vertical{vertical>26 ? 26 : vertical}{
    init();
}
std::size_t ChessBoard::getHorizontal() const{
    return _horizontal;
}
std::size_t ChessBoard::getVertical() const{
    return _vertical;
}
void ChessBoard::printSquares() const{
    const char char_horizontal = static_cast<char>(_horizontal+65);
    bool condition = _vertical > 9 ? true : false;
    for(int i = _vertical; i>0; i--){
        for(char c = 'A'; c < char_horizontal && c<='Z'; c++){
                std::ostringstream ss;
                if(true==condition){
                    if(i<10){
                        ss << c << '0' << i;
                    } else{
                        ss << c << i;
                    }
                    std::cout << std::setw(4) << ss.str() << " ";
                } else{
                    ss << c << i;
                    std::cout << ss.str() << " ";
                }
            }
            std::cout << std::endl;
        }
    }
void ChessBoard::printBoard() const{
    //Tu jest coś zepsute, NAPRAWIĆ!
        for(int i = _vertical; i>-1; i--){
            for(int j = -1; j < static_cast<int>(_horizontal); j++){
                std::ostringstream ss;
                if(-1==j && 0!=i){
                    if(_vertical > 9 && 10>i){
                        ss << '0' << i;
                    } else{
                        ss << i;
                    }
                } else if(-1==j && 0==i){
                    ss << "  ";
                } else if(-1!=j && 0==i){
                    ss << static_cast<char>(j+65) << "  ";
                } else if(pieces[j][i]==nullptr){
                    ss << "  ";
                } else if(pieces[j][i]!=nullptr){
                    ss << (pieces[j][i]->getName())[0];
                    if(pieces[j][i]->getTeam() == Piece::Team::WHITE){
                        ss << "W  ";
                    } else if(pieces[j][i]->getTeam() == Piece::Team::BLACK){
                        ss << "B  ";
                    } else {
                        ss << "?  "; // Unknown team
                    };
                }
                std::cout << ss.str();
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void ChessBoard::move(const std::size_t o_x, const std::size_t o_y, const int x, const int y){
        if(pieces[o_x][o_y]->move(x, y) && pieces[o_x+x][o_y+y] == nullptr){
            pieces[o_x][o_y]->increaseMoveNumber();
            pieces[o_x+x][o_y+y] = std::move(pieces[o_x][o_y]);
        } 
        else if(pieces[o_x][o_y]->attack(x, y) && pieces[o_x+x][o_y+y] != nullptr && 
        pieces[o_x+x][o_y+y]->getTeam() != pieces[o_x][o_y]->getTeam()){
            std::cout << pieces[o_x][o_y]->getName() << " attacks " << pieces[o_x+x][o_y+y]->getName() << " at (" << o_x+x << ", " << o_y+y << ")." << std::endl;
            damagePiece(o_x+x, o_y+y);
            if(pieces[o_x+x][o_y+y] == nullptr){
                pieces[o_x+x][o_y+y] = std::move(pieces[o_x][o_y]);
            }
        } 
        else{
            std::cout << pieces[o_x][o_y]->getName() << " cannot be moved to this square." << std::endl;
        }
    }

    void ChessBoard::setPiece(const std::size_t o_x, const std::size_t o_y, std::unique_ptr<Piece> piece){
        pieces[o_x][o_y] = std::move(piece);
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