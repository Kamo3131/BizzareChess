#include <iostream>
#include "ChessBoard.hpp"
#include "Pawn.hpp"

int main(){
    ChessBoard chessBoard;
    chessBoard.printSquares();
    chessBoard.printBoard();
    auto pawn1 = std::make_unique<Pawn>();
    chessBoard.setPiece(1, 1, std::move(pawn1));
    chessBoard.printBoard();
    chessBoard.move(1, 1, 0, 2);
    chessBoard.printBoard();
    chessBoard.move(1, 3, 0, 2);
    chessBoard.printBoard();
    chessBoard.healPiece(1, 3, 5);
    chessBoard.damagePiece(1, 3, 1);
    chessBoard.printBoard();
    // ChessBoard chessBoard2(26, 32);
    // chessBoard2.printSquares();
    // chessBoard2.printBoard();
    return 0;
}