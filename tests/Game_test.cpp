#include <gtest/gtest.h>
#include "Game.hpp"
#include <string>
#include <sstream>
#include <functional>

/**
 * Test the Game constructor initializes the turn to 0 and creates a ChessBoard with default size.
 */
TEST(GameTests, DefaultConstructor) {
    Game game;
    EXPECT_EQ(game.getTurn(), 0) << "Default constructor failed to initialize turn to 0!";
    EXPECT_EQ(game.getChessBoard().getHorizontal(), 8) << "Default constructor failed to create ChessBoard with horizontal size 8!";
    EXPECT_EQ(game.getChessBoard().getVertical(), 8) << "Default constructor failed to create ChessBoard with vertical size 8!";
}
/**
 * Test the Game constructor initializes the turn to 0 and creates a ChessBoard with specified size.
 */
TEST(GameTests, ParametrizedConstructor) {
    Game game(10, 12);
    EXPECT_EQ(game.getTurn(), 0) << "Parameterized constructor failed to initialize turn to 0!";
    EXPECT_EQ(game.getChessBoard().getHorizontal(), 10) << "Parameterized constructor failed to create ChessBoard with horizontal size 10!";
    EXPECT_EQ(game.getChessBoard().getVertical(), 12) << "Parameterized constructor failed to create ChessBoard with vertical size 12!";
}
/**
 * Test the Game constructor initializes the turn to a specified value and creates a ChessBoard.
 */
TEST(GameTests, ConstructorWithTurnAndChessBoard) {
    ChessBoard chessBoard(10, 12);
    Game game(5, std::move(chessBoard));
    EXPECT_EQ(game.getTurn(), 5) << "Constructor with turn and ChessBoard failed to initialize turn correctly!";
    EXPECT_EQ(game.getChessBoard().getHorizontal(), 10) << "Constructor with turn and ChessBoard failed to create ChessBoard with horizontal size 10!";
    EXPECT_EQ(game.getChessBoard().getVertical(), 12) << "Constructor with turn and ChessBoard failed to create ChessBoard with vertical size 12!";
}
/**
 * Test the Game::printCurrentGameState method prints the current game state correctly.
 */
TEST(GameTests, PrintCurrentGameState) {
    Game game;
    std::ostringstream oss1;
    game.printCurrentGameState(oss1);
    std::ostringstream oss2;
    game.getChessBoard().printBoard(oss2);
    EXPECT_EQ(oss1.str(), oss2.str() + "Turn: 0\n") << "printCurrentGameState did not print the correct game state!";
}

/**
 * Test the Game::nextTurn method increments the turn correctly.
 */
TEST(GameTests, NextTurn) {
    Game game;
    int initialTurn = game.getTurn();
    game.nextTurn();
    EXPECT_EQ(game.getTurn(), initialTurn + 1) << "nextTurn method failed to increment turn!";
}
/**
 * Test the Game::previousTurn method decrements the turn correctly.
 */
TEST(GameTests, PreviousTurn) {
    Game game;
    game.nextTurn(); // Increment to ensure we have a turn to go back to
    int initialTurn = game.getTurn();
    game.previousTurn();
    EXPECT_EQ(game.getTurn(), initialTurn - 1) << "previousTurn method failed to decrement turn!";
}


