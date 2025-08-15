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

    for(int i = 0; i < 8; i++){
        setPiece(i, 1, std::make_unique<Pawn>(Piece::Team::WHITE));
        setPiece(i, 6, std::make_unique<Pawn>(Piece::Team::BLACK));
    }
    setPiece(0, 0, std::make_unique<Rook>(Piece::Team::WHITE));
    setPiece(7, 0, std::make_unique<Rook>(Piece::Team::WHITE));
    setPiece(0, 7, std::make_unique<Rook>(Piece::Team::BLACK));
    setPiece(7, 7, std::make_unique<Rook>(Piece::Team::BLACK));

    setPiece(1, 0, std::make_unique<Knight>(Piece::Team::WHITE));
    setPiece(6, 0, std::make_unique<Knight>(Piece::Team::WHITE));
    setPiece(1, 7, std::make_unique<Knight>(Piece::Team::BLACK));
    setPiece(6, 7, std::make_unique<Knight>(Piece::Team::BLACK));

    setPiece(2, 0, std::make_unique<Bishop>(Piece::Team::WHITE));
    setPiece(5, 0, std::make_unique<Bishop>(Piece::Team::WHITE));
    setPiece(2, 7, std::make_unique<Bishop>(Piece::Team::BLACK));
    setPiece(5, 7, std::make_unique<Bishop>(Piece::Team::BLACK));

    setPiece(3, 0, std::make_unique<Queen>(Piece::Team::WHITE));
    setPiece(4, 0, std::make_unique<King>(Piece::Team::WHITE));
    setPiece(3, 7, std::make_unique<Queen>(Piece::Team::BLACK));
    setPiece(4, 7, std::make_unique<King>(Piece::Team::BLACK));
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

bool ChessBoard::isInitialized() const{
        for(std::size_t i = 0; i < _horizontal; i++){
            for(std::size_t j = 0; j < _vertical; j++){
                if(pieces[i][j] != nullptr){
                    return false;
                }
            }
        }
        return true;
}
void ChessBoard::printSquares(std::ostream& os) const{
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
                    os << std::setw(4) << ss.str() << " ";
                } else{
                    ss << c << i;
                    os << ss.str() << " ";
                }
            }
            os << std::endl;
        }
    }
void ChessBoard::printBoard(std::ostream& os) const{
        for(int i = _vertical-1; i>-2; i--){
            for(int j = -1; j < static_cast<int>(_horizontal); j++){
                std::ostringstream ss;
                if(-1==j && -1!=i){
                    if(_vertical > 9 && 9>i){
                        ss << '0' << i+1 << "|";
                    } else{
                        ss << i+1 << "|";
                    }
                } else if(-1==j && -1==i){
                    ss << "  ";
                } else if(-1!=j && -1==i){
                    ss << " "<< static_cast<char>(j+65) << " ";
                } else if(pieces[j][i]==nullptr){
                    ss << "  |";
                } else if(pieces[j][i]!=nullptr){
                    // Check if the piece is a Knight
                    if(pieces[j][i]->getName().substr(0, 6) != "Knight"){
                        // If it is not a Knight, display the first letter of the name
                        ss << (pieces[j][i]->getName())[0];
                        if(pieces[j][i]->getTeam() == Piece::Team::WHITE){
                            ss << "W|";
                        } else if(pieces[j][i]->getTeam() == Piece::Team::BLACK){
                            ss << "B|";
                        } else {
                            ss << "?|"; // Unknown team
                        };
                        // If it is a Knight, display 'N' instead
                    } else{
                        ss << "N";
                        if(pieces[j][i]->getTeam() == Piece::Team::WHITE){
                            ss << "W|";
                        } else if(pieces[j][i]->getTeam() == Piece::Team::BLACK ){
                            ss << "B|";
                        } else {
                            ss << "?|"; // Unknown team
                        };
                    }
                }
                os << ss.str();
            }
            os << std::endl;
        }
        os << std::endl;
    }

    void ChessBoard::move(const std::size_t o_x, const std::size_t o_y, const int x, const int y){
        // Check if the original position is within bounds
        if(o_x >= _horizontal || o_y >= _vertical){
            std::cerr << "Error: Attempt to invoke move on piece out of bounds at (" << o_x << ", " << o_y << ")." << std::endl;
            return;
        }
        // Check if there is a piece at the original position
        if(pieces[o_x][o_y] == nullptr){
            std::cerr << "Error: No piece at (" << o_x << ", " << o_y << ") to move." << std::endl;
            return;
        }
        // Check if the target square is within bounds
        if(o_x+x >= _horizontal || o_y+y >= _vertical){
            std::cerr << "Error: Attempt to move "<< pieces[o_x][o_y]->getName() << " out of bounds to (" << o_x+x << ", " << o_y+y << ")." << std::endl;
            return;
        }
        // If the piece can move to the target square and there is no piece
        if(pieces[o_x][o_y]->move(x, y) && pieces[o_x+x][o_y+y] == nullptr){
            pieces[o_x][o_y]->increaseMoveNumber();
            pieces[o_x+x][o_y+y] = std::move(pieces[o_x][o_y]);
        } 
        // If the piece can attack the target square and there is an enemy piece
        else if(pieces[o_x][o_y]->attack(x, y) && pieces[o_x+x][o_y+y] != nullptr && 
        pieces[o_x+x][o_y+y]->getTeam() != pieces[o_x][o_y]->getTeam()){
            std::cout << pieces[o_x][o_y]->getName() << " attacks " << pieces[o_x+x][o_y+y]->getName() << " at (" << o_x+x << ", " << o_y+y << ")." << std::endl;
            damagePiece(o_x+x, o_y+y);
            if(pieces[o_x+x][o_y+y] == nullptr){
                pieces[o_x+x][o_y+y] = std::move(pieces[o_x][o_y]);
            }
        } 
        // If castling can be performed
        else if(canCastle(o_x, o_y, x, y)){
            std::cout << pieces[o_x][o_y]->getName() << " is castling with " << pieces[o_x+x][o_y+y]->getName() << " at (" << o_x+x << ", " << o_y+y << ")." << std::endl;
            castling(o_x, o_x+x);
        }
        else {
            std::cout << pieces[o_x][o_y]->getName() << " cannot be moved to this square." << std::endl;
        }
    }

    bool ChessBoard::canMove(const std::size_t o_x, const std::size_t o_y, const int x, const int y) const {
        if(o_x >= _horizontal || o_y >= _vertical){
            std::cerr << "Error: Attempt to check move on piece out of bounds at (" << o_x << ", " << o_y << ")." << std::endl;
            return false;
        }
        if(pieces[o_x][o_y] == nullptr){
            std::cerr << "Error: No piece at (" << o_x << ", " << o_y << ") to check move." << std::endl;
            return false;
        }
        return pieces[o_x][o_y]->move(x, y);
    }
    bool ChessBoard::canCastle(const std::size_t o_x, const std::size_t o_y, const int x, const int y) const {
        if(pieces[o_x][o_y]->getType() != Piece::Type::KING || pieces[o_x+x][o_y+y]->getType() != Piece::Type::ROOK){
            std::cerr << "Error: Castling can only be performed with a King and a Rook." << std::endl;
            return false;
        }
        if(pieces[o_x+x][o_y+y]->getMoveNumber() > 0 || pieces[o_x][o_y]->getMoveNumber() > 0){
            std::cerr << "Error: Castling cannot be performed as either the King or the Rook has already moved." << std::endl;
            return false;
        }
        bool direction = (x > 0) ? true : false;
        int start_x = static_cast<int>(o_x) + (direction ? 1 : -1);
        int end_x = static_cast<int>(o_x) + x;
        for(; direction ? start_x < end_x : start_x > end_x; start_x += direction ? 1 : -1){
            if(pieces[start_x][o_y] != nullptr){
                std::cout << "Cannot castle, there is a piece at (" << start_x << ", " << o_y << ")." << std::endl;
                return false;
            }
        }
        return true;

    }
    void ChessBoard::castling(const std::size_t k_x, const std::size_t r_x){
        if(r_x < k_x){
            pieces[k_x][0] -> increaseMoveNumber();
            pieces[k_x-2][0] = std::move(pieces[k_x][0]);
            pieces[k_x-1][0] = std::move(pieces[r_x][0]);
        } else if(r_x > k_x){
            pieces[k_x][0] -> increaseMoveNumber();
            pieces[k_x+2][0] = std::move(pieces[k_x][0]);
            pieces[k_x+1][0] = std::move(pieces[r_x][0]);
        } else {
            std::cerr << "Error: Invalid castling move." << std::endl;
        }

    }
    void ChessBoard::setPiece(const std::size_t o_x, const std::size_t o_y, std::unique_ptr<Piece> piece){
        if(o_x >= _horizontal || o_y >= _vertical){
            std::cerr << "Error: Attempt to set piece out of bounds at (" << o_x << ", " << o_y << ")." << std::endl;
            return;
        }
        if(pieces[o_x][o_y] != nullptr){
            std::cerr << "Error: Square (" << o_x << ", " << o_y << ") is already occupied by " 
                      << pieces[o_x][o_y]->getName() << ". Cannot set new piece." << std::endl;
            return;
        }
        if(piece == nullptr){
            std::cerr << "Error: Attempt to set a null piece at (" << o_x << ", " << o_y << ")." << std::endl;
            return;
        }
        std::cout << "Setting piece " << piece->getName() << " at (" << o_x << ", " << o_y << ")." << std::endl;
        pieces[o_x][o_y] = std::move(piece);
    }

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