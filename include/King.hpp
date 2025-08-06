#pragma once
#include "Piece.hpp"

struct King : public Piece{
    /**
     * @brief Default constructor. Increases the amount of kings by 1. Names the king according to it's number.
     */
    King(const Piece::Team team);
    /**
     * @brief Checks if king can move by given horizontal value and given vertical value.
     * @param horizontal value marked as x on chessboard
     * @param vertical value marked as y on chessboard
     * @returns true if king can move by given params. False if it cannot.
     */
    bool move(const int horizontal, const int vertical);
    /**
     * @brief Checks if king can attack by given horizontal value and given vertical value.
     * @param horizontal value marked as x on chessboard
     * @param vertical value marked as y on chessboard
     * @returns true if king can attack by given params. False if it cannot.
     */
    bool attack(const int horizontal, const int vertical);
    private:
    static std::size_t amount; //number of initialized pawns
};

