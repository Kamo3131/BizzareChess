#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Piece.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Pawn.hpp"


class ChessBoard{
    public:
    using size = std::size_t;
    /**
     * @brief Default constructor. Initializes _horizontal and _vertical with 8.
     */
    ChessBoard();
    
    /**
     * @brief Constructor for chessboards with different sizes.
     * @param horizontal sets horizontal tile number, should not exceed 26
     * @param vertical sets vertical lenght, should not exceed 26
     */
    ChessBoard(const size horizontal, const size vertical);

    /**
     * @brief Inits chessboard
     */
    void init();
    /**
     * @brief Inits pieces on the board.
     */
    void initPieces();

    /**
     * @brief Displays codes of the squares. Does not take parameters.
     */
    void printSquares(std::ostream& os = std::cout) const;

    /**
     * @brief Displays current state of chessboard.
     */
    void printBoard(std::ostream& os = std::cout) const;

    /**
     * @brief Moves figure by x,y.
     * @param o_x original x tile value
     * @param o_y original y tile value
     * @param x shift from original x (positive values to right, negative to left)
     * @param y shift from original y (positive values to top, negative to bottom)
     */
    void move(const std::size_t o_x, const std::size_t o_y, const int x, const int y);

    /**
     * @brief Checks if castling is possible.
     * @param o_x original x tile value
     * @param o_y original y tile value
     * @param x shift from original x (positive values to right, negative to left)
     * @param y shift from original y (positive values to top, negative to bottom)
     * @return true if castling is possible, false otherwise
     */
    bool canCastle(const std::size_t o_x, const std::size_t o_y, const int x, const int y) const;
    /**
     * @brief Moves king by 2 tiles and rook jumps over king.
     * @param k_x king's horizontal position.
     * @param r_x rook's horizontal position.
     * @note: This function assumes that the king and rook are on the same row.
     */
    void castling(const std::size_t k_x, const std::size_t r_x);
    void pawnPromotion(const std::size_t o_x, const std::size_t o_y);
    void enPassant(const std::size_t o_x, const std::size_t o_y);
    /**
     * @brief Return hotizpntal length
     * @return horizontal lenght
     */
    size getHorizontal() const;

    /**
     * @brief Return vertical lenght
     * @return vertical lenght
     */
    size getVertical() const;

    /**
     * @brief Checks if container has been created but not set.
     * @return true if container has been created but not set, false otherwise
     */
    bool isInitialized() const;

    /**
     * @brief Sets given figure at o(x,y)
     * @param o_x x tile value
     * @param o_y y tile value
     * @param piece figure to set
     */
    void setPiece(const std::size_t o_x, const std::size_t o_y, std::unique_ptr<Piece> piece);

    /**
     * @brief Gets if there is a piece at given o(x,y) tile
     * @param o_x x tile value
     * @param o_y y tile value
     * @return true if there is a piece at given o(x,y) tile, false otherwise
     */
    bool isPieceAt(const std::size_t o_x, const std::size_t o_y) const;
    /**
     * @brief Destroyes figure at given o(x,y) tile
     * @param o_x x tile value
     * @param o_y y tile value
     */
    void killPiece(const std::size_t o_x, const std::size_t o_y);

    /**
     * @brief Increases figure's health value at o(x,y) tile for given health
     * @param o_x x tile value
     * @param o_y y tile value
     * @param health heals for given value
     */
    void healPiece(const std::size_t o_x, const std::size_t o_y, const int health);

    /**
     * @brief Gets health of piece at given o(x,y) tile
     * @param o_x x tile value
     * @param o_y y tile value
     * @return health of piece at given o(x,y) tile, -1 if there is no piece at given o(x,y) tile
     */
    int getHealthOfPiece(const std::size_t o_x, const std::size_t o_y) const;
    
    /**
     * @brief Damages figure at given o(x,y) for default value
     * @param o_x x tile value
     * @param o_y y tile value
     */
    void damagePiece(const std::size_t o_x, const std::size_t o_y);

    /**
     * @brief Damages figure at o(x,y) tile for given damage value
     * @param o_x x tile value
     * @param o_y y tile value
     * @param damage value of damage
     */
    void damagePiece(const std::size_t o_x, const std::size_t o_y, const int damage);
    /**
     * @brief Gets damage of piece at given o(x,y) tile
     * @param o_x x tile value
     * @param o_y y tile value
     * @return damage of piece at given o(x,y) tile, -1 if there is no piece at given o(x,y) tile
     */
    int getDamageOfPiece(const std::size_t o_x, const std::size_t o_y) const;
    private:
    const size _horizontal; //height
    const size _vertical;   //width
    std::vector<std::vector<std::unique_ptr<Piece>>> pieces; //stores figures

};

