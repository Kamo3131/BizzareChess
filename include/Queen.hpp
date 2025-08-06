#pragma once
#include "Piece.hpp"

struct Queen : public Piece{
    /**
     * @brief Default constructor. Increases the amount of queens by 1. Names the queen according to it's number.
     */
    Queen(const Piece::Team team);
    /**
     * @brief Checks if queen can move by given horizontal value and given vertical value.
     * @param horizontal value marked as x on chessboard
     * @param vertical value marked as y on chessboard
     * @returns true if queen can move by given params. False if it cannot.
     */
    bool move(const int horizontal, const int vertical);
    /**
     * @brief Checks if queen can attack by given horizontal value and given vertical value.
     * @param horizontal value marked as x on chessboard
     * @param vertical value marked as y on chessboard
     * @returns true if queen can attack by given params. False if it cannot.
     */
    bool attack(const int horizontal, const int vertical);
    private:
    static std::size_t amount; //number of initialized pawns
};

