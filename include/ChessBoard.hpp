#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Piece.hpp"


class ChessBoard{
    public:
    using size = std::size_t;
    /**
     * Default constructor. Initializes _horizontal and _vertical with 8.
     */
    ChessBoard();
    /**
     * Constructor for chessboards with different sizes..
     * @param should not exceed 26
     */
    ChessBoard(const size horizontal, const size vertical);
    void init();
    /**
     * Displays codes of the squares. Does not take parameters.
     */
    void printSquares() const;
    /**
     * Displays current state of chessboard.
     */
    void printBoard() const;

    void move(const std::size_t o_x, const std::size_t o_y, const int x, const int y);
    size getHorizontal() const;
    size getVertical() const;
    void setPiece(const std::size_t o_x, const std::size_t o_y, std::unique_ptr<Piece> piece);
    void killPiece(const std::size_t o_x, const std::size_t o_y);
    void healPiece(const std::size_t o_x, const std::size_t o_y, const int health);
    void damagePiece(const std::size_t o_x, const std::size_t o_y);
    void damagePiece(const std::size_t o_x, const std::size_t o_y, const int damage);
    private:
    const size _horizontal;
    const size _vertical;
    std::vector<std::vector<std::unique_ptr<Piece>>> pieces;
};

