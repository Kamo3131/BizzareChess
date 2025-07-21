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
     * @param horizontal sets horizontal tile number, should not exceed 26
     * @param vertical sets vertical lenght, should not exceed 26
     */
    ChessBoard(const size horizontal, const size vertical);

    /**
     * Inits chessboard
     */
    void init();

    /**
     * Displays codes of the squares. Does not take parameters.
     */
    void printSquares() const;

    /**
     * Displays current state of chessboard.
     */
    void printBoard() const;

    /**
     * Moves figure from o(x,y) to new (x,y)
     * @param o_x before x tile value
     * @param o_y before t tile value
     * @param x new x tile value
     * @param y new y tile value
     */
    void move(const std::size_t o_x, const std::size_t o_y, const int x, const int y);

    /**
     * Return hotizpntal length
     * @return horizontal lenght
     */
    size getHorizontal() const;

    /**
     * Return vertical lenght
     * @return vertical lenght
     */
    size getVertical() const;

    /**
     * Sets given figure at o(x,y)
     * @param o_x x tile value
     * @param o_y y tile value
     * @param piece figure to set
     */
    void setPiece(const std::size_t o_x, const std::size_t o_y, std::unique_ptr<Piece> piece);

    /**
     * Destroyes figure at given o(xy) tile
     * @param o_x x tile value
     * @param o_y y tile value
     */
    void killPiece(const std::size_t o_x, const std::size_t o_y);

    /**
     * Heals figure at o(x,y) tile for given health
     * @param o_x x tile value
     * @param o_y y tile value
     * @param health heals for given value
     */
    void healPiece(const std::size_t o_x, const std::size_t o_y, const int health);

    /**
     * Damages figure at given o(x,y) for default value
     * @param o_x x tile value
     * @param o_y y tile value
     */
    void damagePiece(const std::size_t o_x, const std::size_t o_y);

    /**
     * Damages figure at o(x,y) tile for given damage value
     * @param o_x x tile value
     * @param o_y y tile value
     * @param damage value of damage
     */
    void damagePiece(const std::size_t o_x, const std::size_t o_y, const int damage);
    private:
    const size _horizontal; //hight
    const size _vertical;   //width
    std::vector<std::vector<std::unique_ptr<Piece>>> pieces; //stores figures
};

