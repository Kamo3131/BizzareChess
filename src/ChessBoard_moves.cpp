#include "ChessBoard.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

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
    //If the piece is a pawn and can perform en passant
    if(enPassantAvailable(o_x, o_y, x, y)){
        std::cout << pieces[o_x][o_y] -> getName() << " performs en passant at (" << o_x+x << ", " << o_y+y << ")." << std::endl;
        enPassant(o_x, o_y, x, y);
        return;
    }
    // If the piece can move to the target square and there is no piece
    else if(pieces[o_x][o_y]->move(x, y) && pieces[o_x+x][o_y+y] == nullptr){
        pieces[o_x][o_y]->increaseMoveNumber();
        pieces[o_x+x][o_y+y] = std::move(pieces[o_x][o_y]);
        pieces[o_x][o_y] = nullptr;
    } 
    // If the piece can attack the target square and there is an enemy piece
    else if(pieces[o_x][o_y]->attack(x, y) && pieces[o_x+x][o_y+y] != nullptr && 
    pieces[o_x+x][o_y+y]->getTeam() != pieces[o_x][o_y]->getTeam()){
        std::cout << pieces[o_x][o_y]->getName() << " attacks " << pieces[o_x+x][o_y+y]->getName() << " at (" << o_x+x << ", " << o_y+y << ")." << std::endl;
        damagePiece(o_x+x, o_y+y);
        if(pieces[o_x+x][o_y+y] == nullptr){
            pieces[o_x+x][o_y+y] = std::move(pieces[o_x][o_y]);
            pieces[o_x][o_y] = nullptr;
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
    if(pieces[o_x+x][o_y+y]->getType() == Piece::Type::PAWN && pieces[o_x+x][o_y+y]->getTeam() == Piece::Team::WHITE && (o_y+y == getVertical() - 1)){
        std::cout << pieces[o_x+x][o_y+y]->getName() << " is being promoted at (" << o_x+x << ", " << o_y+y << ")." << std::endl;
        pawnPromotionChoice(o_x+x, o_y+y);
    } else if(pieces[o_x+x][o_y+y]->getType() == Piece::Type::PAWN && pieces[o_x+x][o_y+y]->getTeam() == Piece::Team::BLACK && (o_y+y == 0)){
        std::cout << pieces[o_x+x][o_y+y]->getName() << " is being promoted at (" << o_x+x << ", " << o_y+y << ")." << std::endl;
        pawnPromotionChoice(o_x+x, o_y+y);
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
    if(enPassantAvailable(o_x, o_y, x, y)){
        return true;
    }
    if(pieces[o_x+x][o_y+y]){
        return pieces[o_x][o_y]->attack(x, y);
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
        // pieces[k_x][0] == nullptr;
        pieces[k_x-1][0] = std::move(pieces[r_x][0]);
        // pieces[r_x][0] == nullptr;
    } else if(r_x > k_x){
        pieces[k_x][0] -> increaseMoveNumber();
        pieces[k_x+2][0] = std::move(pieces[k_x][0]);
        // pieces[k_x][0] == nullptr;
        pieces[k_x+1][0] = std::move(pieces[r_x][0]);
        // pieces[r_x][0] == nullptr;
    } else {
        std::cerr << "Error: Invalid castling move." << std::endl;
    }

}

void ChessBoard::pawnPromotionChoice(const std::size_t o_x, const std::size_t o_y) {
    std::cout << "Choose a piece to promote your pawn to (Q for Queen, R for Rook, B for Bishop, N for Knight): ";
    char choice;
    std::cin >> choice;
    switch(toupper(choice)) {
        case 'Q':
            pawnPromotion(o_x, o_y, Piece::Type::QUEEN);
            break;
        case 'R':
            pawnPromotion(o_x, o_y, Piece::Type::ROOK);
            break;
        case 'B':
            pawnPromotion(o_x, o_y, Piece::Type::BISHOP);
            break;
        case 'N':
            pawnPromotion(o_x, o_y, Piece::Type::KNIGHT);
            break;
        default:
            std::cout << "Invalid choice. Promoting to Queen by default." << std::endl;
            pawnPromotion(o_x, o_y, Piece::Type::QUEEN);
    }
}

void ChessBoard::pawnPromotion(const std::size_t o_x, const std::size_t o_y, Piece::Type type) {
    std::unique_ptr<Piece> promoted_piece;
    switch(type) {
        case Piece::Type::QUEEN:
            promoted_piece = std::make_unique<Queen>(pieces[o_x][o_y]->getTeam());
            break;
        case Piece::Type::ROOK:
            promoted_piece = std::make_unique<Rook>(pieces[o_x][o_y]->getTeam());
            break;
        case Piece::Type::BISHOP:
            promoted_piece = std::make_unique<Bishop>(pieces[o_x][o_y]->getTeam());
            break;
        case Piece::Type::KNIGHT:
            promoted_piece = std::make_unique<Knight>(pieces[o_x][o_y]->getTeam());
            break;
        default:
            std::cerr << "Invalid promotion type. Defaulting to Queen." << std::endl;
            promoted_piece = std::make_unique<Queen>(pieces[o_x][o_y]->getTeam());
    }
    pieces[o_x][o_y] = nullptr;
    pieces[o_x][o_y] = std::move(promoted_piece);
    std::cout << "Pawn at (" << o_x << ", " << o_y << ") has been promoted to " 
              << pieces[o_x][o_y]->getName() << "." << std::endl;
}


bool ChessBoard::enPassantAvailable(const std::size_t o_x, const std::size_t o_y, const int x, const int y) const{
    // Only pawns can perform en passant
    if(pieces[o_x][o_y] && pieces[o_x][o_y]->getType() == Piece::Type::PAWN){
        // Check if the move is diagonal and one square forward
        if(pieces[o_x+x][o_y+y] == nullptr && abs(x) == 1 
        && ((pieces[o_x][o_y]->getTeam() == Piece::Team::WHITE 
        && y == 1) || (pieces[o_x][o_y]->getTeam() == Piece::Team::BLACK && y == -1))){
            // Check if the pawn can be captured en passant
            if(pieces[o_x+x][o_y] && pieces[o_x+x][o_y]->getType() == Piece::Type::PAWN && 
               pieces[o_x+x][o_y]->getTeam() != pieces[o_x][o_y]->getTeam()){
                Pawn* adjacentPawn = dynamic_cast<Pawn*>(pieces[o_x+x][o_y].get());
                return (adjacentPawn->getEnPassant().second && adjacentPawn->getEnPassant().first > 0);
            }
    }
}
return false;
}

void ChessBoard::enPassant(const std::size_t o_x, const std::size_t o_y, const int x, const int y){
    if(abs(x) == 1 && abs(y) == 1){
    // Assuming pieces[o_x+x][o_y] is a Pawn and can be captured en passant
        damagePiece(o_x+x, o_y);
        if(pieces[o_x+x][o_y] != nullptr){
            Pawn* pawn = dynamic_cast<Pawn*>(pieces[o_x+x][o_y].get());
            pawn->setEnPassant(0, false); // Reset en passant status
        }
        pieces[o_x+x][o_y+y] = std::move(pieces[o_x][o_y]);
        pieces[o_x][o_y] = nullptr; // Clear the original position
    }
}