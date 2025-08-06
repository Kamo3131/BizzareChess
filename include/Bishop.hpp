#pragma once
#include "Piece.hpp"

struct Bishop : public Piece{
    /**
     * @brief Default constructor. Increases the amount of bishops by 1. Names the bishop according to it's number.
     */
    Bishop(const Piece::Team team);
    /**
     * @brief Checks if bishop can move by given horizontal value and given vertical value.
     * @param horizontal value marked as x on chessboard
     * @param vertical value marked as y on chessboard
     * @returns true if bishop can move by given params. False if it cannot.
     */
    bool move(const int horizontal, const int vertical);
    /**
     * @brief Checks if bishop can attack by given horizontal value and given vertical value.
     * @param horizontal value marked as x on chessboard
     * @param vertical value marked as y on chessboard
     * @returns true if bishop can attack by given params. False if it cannot.
     */
    bool attack(const int horizontal, const int vertical);
    private:
    static std::size_t amount; //number of initialized pawns
};

