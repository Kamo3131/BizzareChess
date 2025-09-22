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
    EXPECT_EQ(game.getTurn(), 1) << "Default constructor failed to initialize turn to 0!";
    EXPECT_EQ(game.getChessBoard().getHorizontal(), 8) << "Default constructor failed to create ChessBoard with horizontal size 8!";
    EXPECT_EQ(game.getChessBoard().getVertical(), 8) << "Default constructor failed to create ChessBoard with vertical size 8!";
}
/**
 * Test the Game constructor initializes the turn to 0 and creates a ChessBoard with specified size.
 */
TEST(GameTests, ParametrizedConstructor) {
    Game game(10, 12);
    EXPECT_EQ(game.getTurn(), 1) << "Parameterized constructor failed to initialize turn to 0!";
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
    EXPECT_EQ(oss1.str(), oss2.str() + "Team: White\nTurn: 1\n") << "printCurrentGameState did not print the correct game state!";
}

/**
 * Test the Game::printCurrentGameState method prints the current game state correctly if there is a check.
 */
TEST(GameTests, PrintCurrentGameStatKingInCheck) {
    ChessBoard board;
    board.setPiece(3, 2, std::make_unique<King>(Piece::Team::BLACK));
    board.setBlackKingsPosition(3, 2);
    board.setPiece(3, 0, std::make_unique<Rook>(Piece::Team::WHITE));

    Game game(2, std::move(board));
    std::ostringstream oss1;
    game.printCurrentGameState(oss1);
    std::ostringstream oss2;
    game.getChessBoard().printBoard(oss2);
    EXPECT_EQ(oss1.str(), oss2.str() + "Team: Black\nKing in check!\nTurn: 2\n") << "printCurrentGameState did not print the correct game state!";
}

/**
 * Test the Game::printCurrentGameState method prints the current game state correctly if there is a checkmate on black king.
 */
TEST(GameTests, PrintCurrentGameStatBlackKingInCheckmate) {
    ChessBoard board;
    board.setPiece(4, 4, std::make_unique<King>(Piece::Team::BLACK));
    board.setBlackKingsPosition(4, 4);
    board.setPiece(3, 7, std::make_unique<Rook>(Piece::Team::WHITE));
    board.setPiece(4, 7, std::make_unique<Rook>(Piece::Team::WHITE));
    board.setPiece(5, 7, std::make_unique<Rook>(Piece::Team::WHITE));

    Game game(2, std::move(board));
    std::ostringstream oss1;
    game.printCurrentGameState(oss1);
    std::ostringstream oss2;
    game.getChessBoard().printBoard(oss2);
    EXPECT_EQ(oss1.str(), oss2.str() + "Team: Black\nCheckmate! Team Black has lost!\nTurn: 2\n") << "printCurrentGameState did not print the correct game state!";
}

/**
 * Test the Game::printCurrentGameState method prints the current game state correctly if there is a checkmate on white king.
 */
TEST(GameTests, PrintCurrentGameStatWhiteKingInCheckmate) {
    ChessBoard board;
    board.setPiece(4, 4, std::make_unique<King>(Piece::Team::WHITE));
    board.setWhiteKingsPosition(4, 4);
    board.setPiece(3, 7, std::make_unique<Rook>(Piece::Team::BLACK));
    board.setPiece(4, 7, std::make_unique<Rook>(Piece::Team::BLACK));
    board.setPiece(5, 7, std::make_unique<Rook>(Piece::Team::BLACK));

    Game game(1, std::move(board));
    std::ostringstream oss1;
    game.printCurrentGameState(oss1);
    std::ostringstream oss2;
    game.getChessBoard().printBoard(oss2);
    EXPECT_EQ(oss1.str(), oss2.str() + "Team: White\nCheckmate! Team White has lost!\nTurn: 1\n") << "printCurrentGameState did not print the correct game state!";
}
/**
 * Test the Game::printCurrentGameState method prints the current game state correctly if there is a stalemate on a king.
 */
TEST(GameTests, PrintCurrentGameStatInStalemate) {
    ChessBoard board;
    board.setPiece(4, 4, std::make_unique<King>(Piece::Team::BLACK));
    board.setWhiteKingsPosition(4, 4);
    board.setPiece(3, 7, std::make_unique<Rook>(Piece::Team::WHITE));
    board.setPiece(5, 7, std::make_unique<Rook>(Piece::Team::WHITE));
    board.setPiece(7, 5, std::make_unique<Rook>(Piece::Team::WHITE));
    board.setPiece(7, 3, std::make_unique<Rook>(Piece::Team::WHITE));

    Game game(2, std::move(board));
    std::ostringstream oss1;
    game.printCurrentGameState(oss1);
    std::ostringstream oss2;
    game.getChessBoard().printBoard(oss2);
    EXPECT_EQ(oss1.str(), oss2.str() + "Team: Black\nStalemate! It's a draw!\nTurn: 2\n") << "printCurrentGameState did not print the correct game state!";
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

/**
 * Test the Game::surrender method returns false when the game is surrendered.
 */
TEST(GameTests, Surrender) {
    Game game;
    std::string test_input = "Y\n"; 
    std::stringstream ss(test_input);
    std::streambuf* old_cin_buf = std::cin.rdbuf();
    std::cin.rdbuf(ss.rdbuf());
    EXPECT_FALSE(game.surrender()) << "surrender method did not return false when the game was surrendered!";
    std::cin.rdbuf(old_cin_buf);
}
/**
 * Test the Game::quitGame method returns false when the game is quit.
 */
TEST(GameTests, QuitGame) {
    Game game;
    std::string test_input = "Y\n"; 
    std::stringstream ss(test_input);
    std::streambuf* old_cin_buf = std::cin.rdbuf();
    std::cin.rdbuf(ss.rdbuf());
    EXPECT_FALSE(game.quitGame()) << "quitGame method did not return false when the game was quit!";
    std::cin.rdbuf(old_cin_buf);
}

/**
 * Test the Game::movePiece method prompts for a piece and moves it correctly.
 */
TEST(GameTests, MovePiece) {
    ChessBoard board;
    board.setPiece(0, 1, std::make_unique<Pawn>(Piece::Team::WHITE));
    Game game(1, std::move(board));
    std::string test_input = "2A\n3A\n"; // Simulate moving a piece from 1A to 2B
    std::stringstream ss(test_input);
    std::streambuf* old_cin_buf = std::cin.rdbuf();
    std::cin.rdbuf(ss.rdbuf());
    EXPECT_TRUE(game.getChessBoard().isPieceAt(0, 1)) << "Initial piece at 2A is not present!";
    EXPECT_EQ(game.getTurn(), 1) << "Initial turn is not 1!";
    game.movePiece();
    EXPECT_TRUE(game.getChessBoard().isPieceAt(0, 2)) << "Piece was not moved to 3A!";
    EXPECT_FALSE(game.getChessBoard().isPieceAt(0, 1)) << "Piece at 1A is still present after move!";
    EXPECT_EQ(game.getTurn(), 2) << "movePiece did not advance the turn after a successful move!";
    std::cin.rdbuf(old_cin_buf);
}

/**
 * Test the Game::movePiece method does not move a piece when the move is invalid.
 */
TEST(GameTests, MovePieceInvalidMove) {
    ChessBoard board;
    board.setPiece(0, 1, std::make_unique<Pawn>(Piece::Team::WHITE));
    Game game(1, std::move(board));
    std::string test_input = "2A\n2A\n3A\n"; // Simulate invalid move from 2A to 2A, then valid move to 3A
    std::stringstream ss(test_input);
    std::streambuf* old_cin_buf = std::cin.rdbuf();
    std::cin.rdbuf(ss.rdbuf());
    EXPECT_TRUE(game.getChessBoard().isPieceAt(0, 1)) << "Initial piece at 2A is not present!";
    EXPECT_EQ(game.getTurn(), 1) << "Initial turn is not 1!";
    game.movePiece();
    EXPECT_TRUE(game.getChessBoard().isPieceAt(0, 2)) << "Piece was not moved to 3A after valid move!";
    EXPECT_FALSE(game.getChessBoard().isPieceAt(0, 1)) << "Piece at 2A is still present after move!";
    EXPECT_EQ(game.getTurn(), 2) << "movePiece did not advance the turn after a successful move!";
    std::cin.rdbuf(old_cin_buf);
}

/**
 * Test the Game::gameLoop method decreases the en passant turn counter correctly for each team.
 */
TEST(GameTests, GameLoopEnPassantTurnUpdate) {
    ChessBoard board;
    std::unique_ptr<Pawn> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    pawn1W->setEnPassant(1, true); // Set en passant turns to 2 for white pawn
    board.setPiece(0, 1, std::move(pawn1W));
    std::unique_ptr<Pawn> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    pawn1B->setEnPassant(1, true); // Set en passant turns to 2 for black pawn
    board.setPiece(1, 6, std::move(pawn1B));
    
    Game game(1, std::move(board));

    game.enPassantTurnCycle();
    game.nextTurn();
    game.enPassantTurnCycle();
    game.nextTurn();

    
    std::pair<int, bool> enPassantStatusW = game.getChessBoard().getEnPassantStatus(0, 1);
    std::pair<int, bool> enPassantStatusB = game.getChessBoard().getEnPassantStatus(1, 6);
    
    EXPECT_EQ(enPassantStatusW.first, 0) << "White pawn's en passant turn counter was not decremented correctly!";
    EXPECT_FALSE(enPassantStatusW.second) << "White pawn's en passant status was not updated correctly!";
    
    EXPECT_EQ(enPassantStatusB.first, 0) << "Black pawn's en passant turn counter was not decremented correctly!";
    EXPECT_FALSE(enPassantStatusB.second) << "Black pawn's en passant status was not updated correctly!";
}