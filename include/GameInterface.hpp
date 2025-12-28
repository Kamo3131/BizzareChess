#pragma once
#include <iostream>
#include <ChessBoard.hpp>
#include <vector>
#include <memory>
#include "Piece.hpp"
#include "King.hpp"
class GameInterface {
    public:
    using size = std::size_t;
    /**
     * @brief main game loop, handles user input and game commands.
     * @details Displays current game state, prompts for commands, and processes them.
     */
    virtual void gameLoop() = 0;
    /**
     * @brief Moves a piece on the chessboard.
     */
    virtual void movePiece() = 0;
    /**
     * @brief Surrenders the game.
     * @return false if the game is surrendered, true otherwise
     */
    virtual bool surrender() = 0;
    /**
     * @brief Quits the game.
     * @return false if the game is quit, true otherwise
     */
    virtual bool quitGame() = 0;
    /**
     * @brief Advances to the next turn.
     */
    virtual void nextTurn() = 0;
    /**
     * @brief Goes back to the previous turn.
     * @details This function is a placeholder for future implementation.
     */
    virtual void previousTurn() = 0;
    /**
     * @brief Decreases enpassant turn status for all pieces of playing team.
     */
    virtual void enPassantTurnCycle() = 0;
    /**
     * @brief Gets the current turn number.
     * @return Current turn number.
     */
    virtual int getTurn() const = 0;
};