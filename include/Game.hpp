#pragma once
#include <iostream>
#include <ChessBoard.hpp>
#include <vector>
#include "Piece.hpp"
#include "King.hpp"
#include <memory>
class Game{
    public:
    using size = std::size_t;
    /**
     * @brief Default constructor. Initializes _turn with 0 and _chessBoard with 8x8.
     */
    Game();
    /**
     * @brief Constructor for game with different chessboard sizes.
     * @param horizontal sets horizontal tile number, should not exceed 26
     * @param vertical sets vertical lenght, should not exceed 26
     */
    Game(const size horizontal, const size vertical);
    /**
     * @brief Constructor for game with given turn and chessboard.
     * @param turn sets current turn
     * @param chessBoard sets chessboard
     */
    Game(const int turn, ChessBoard&& chessBoard);
    /**
     * @brief Prints current game state, including chessboard state and turn number.
     */
    void printCurrentGameState() const;
    /**
     * @brief main game loop, handles user input and game commands.
     * @details Displays current game state, prompts for commands, and processes them.
     */
    void gameLoop();
    /**
     * @brief Moves a piece on the chessboard.
     * @details Prompts user to select a piece and a target square, validates input, and performs the move.
     */
    void movePiece();
    /**
     * @brief Surrenders the game.
     * @return false if the game is surrendered, true otherwise
     */
    bool surrender();
    /**
     * @brief Quits the game.
     * @return false if the game is quit, true otherwise
     */
    bool quitGame();
    /**
     * @brief Advances to the next turn.
     */
    void nextTurn();
    /**
     * @brief Goes back to the previous turn.
     * @details This function is a placeholder for future implementation.
     */
    void previousTurn();
    private:
    int _turn;
    ChessBoard _chessBoard;
};


