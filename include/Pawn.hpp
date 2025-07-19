#pragma once
#include "Piece.hpp"

struct Pawn : public Piece{
    Pawn();
    bool move(const int horizontal, const int vertical);
    bool attack(const int horizontal, const int vertical);
    private:
    static std::size_t amount;
};

