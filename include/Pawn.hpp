#pragma once
#include "Piece.hpp"
#include <utility>

struct Pawn : public Piece{
    /**
     * @brief Default constructor. Increases the amount of pawns by 1. Names the pawn according to it's number.
     */
    Pawn(const Piece::Team team);
    /**
     * @brief Checks if pawn can move by given horizontal value and given vertical value.
     * @param horizontal value marked as x on chessboard
     * @param vertical value marked as y on chessboard
     * @returns true if pawn can move by given params. False if it cannot.
     */
    bool move(const int horizontal, const int vertical);
    /**
     * @brief Checks if pawn can attack by given horizontal value and given vertical value.
     * @param horizontal value marked as x on chessboard
     * @param vertical value marked as y on chessboard
     * @returns true if pawn can attack by given params. False if it cannot.
     */
    bool attack(const int horizontal, const int vertical);
    /**
     * @brief Gets the en passant status of the pawn.
     */
    std::pair<int, bool> getEnPassant() const;
    /**
     * @brief Sets the en passant status of the pawn.
     * @param turnsLeft The number of turns left for en passant.
     * @param canCapture Indicates if the pawn can be captured en passant.
     */
    void setEnPassant(int turnsLeft, bool canCapture);
    private:
    static std::size_t amount; //number of initialized pawns
    std::pair<int, bool> enPassant{0, false}; //boolean value indicates if pawn can be captured en passant, 
    //int value indicates the number of turns left for en passant
};

