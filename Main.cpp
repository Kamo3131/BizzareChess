#include <iostream>
#include "ChessBoard.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"

int main(){
    ChessBoard chessBoard;
    chessBoard.printSquares();
    chessBoard.printBoard();
    auto pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    auto pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    chessBoard.setPiece(1, 1, std::move(pawn1W));
    chessBoard.setPiece(2, 3, std::move(pawn1B));
    auto rook1W = std::make_unique<Rook>(Piece::Team::WHITE);
    chessBoard.setPiece(7, 1, std::move(rook1W));
    auto rook1B = std::make_unique<Rook>(Piece::Team::BLACK);
    chessBoard.setPiece(7, 8, std::move(rook1B));
    chessBoard.printBoard();
    chessBoard.move(1, 1, 0, 1);
    chessBoard.move(7, 1, 0, 7);
    chessBoard.move(7, 8, -1, 0);
    chessBoard.printBoard();
    chessBoard.move(6, 8, 2, 0);
    chessBoard.printBoard();
    chessBoard.move(1, 2, 1, 1);
    chessBoard.printBoard();
    chessBoard.healPiece(2, 3, 5);
    chessBoard.damagePiece(2, 3, 1);
    chessBoard.printBoard();
    
    
    // ChessBoard chessBoard2(26, 32);
    // chessBoard2.printSquares();
    // chessBoard2.printBoard();
    return 0;
}