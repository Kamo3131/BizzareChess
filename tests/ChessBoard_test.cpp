#include <gtest/gtest.h>
#include "ChessBoard.hpp"
#include "Piece.hpp"
#include "Pawn.hpp"

/**
 * Test the ChessBoard constructor initializes horizontal and vertical sizes to 8.
 */
TEST(ChessBoardTests, DefaultConstructor) {
    ChessBoard board;
    EXPECT_EQ(board.getHorizontal(), 8) << "Default constructor failed to set horizontal size!";
    EXPECT_EQ(board.getVertical(), 8) << "Default constructor failed to set vertical size!";
}

/**
 * Test the ChessBoard constructor initializes horizontal and vertical sizes to specified values.
 */
TEST(ChessBoardTests, ParameterizedConstructor){
    ChessBoard board(10, 12);
    EXPECT_EQ(board.getHorizontal(), 10) << "Parameterized constructor failed to set horizontal size!";
    EXPECT_EQ(board.getVertical(), 12) << "Parameterized constructor failed to set vertical size!";
}

/**
 * Test the ChessBoard constructor does not allow horizontal size to exceed 26.
 */
TEST(ChessBoardTests, ConstructorExceedsHorizontalLimit){
    ChessBoard board(30, 10);
    EXPECT_EQ(board.getHorizontal(), 26) << "Constructor should limit horizontal size to 26!";
    EXPECT_EQ(board.getVertical(), 10) << "Constructor should not limit vertical size to 26!"; 
}

/**
 * Test the ChessBoard constructor does not allow vertical size to exceed 26.
 */
TEST(ChessBoardTests, ConstructorExceedsVerticalLimit){
    ChessBoard board(10, 30);
    EXPECT_EQ(board.getHorizontal(), 10) << "Constructor should not limit horizontal size to 26!";
    EXPECT_EQ(board.getVertical(), 26) << "Constructor should limit vertical size to 26!";
}

/**
 * Test the ChessBoard::init method initializes the board correctly.
 */
TEST(ChessBoardTests, InitMethod){
    ChessBoard board;
    board.init();
    EXPECT_EQ(board.isInitialized(), true) << "Init method failed to set chessboard!";
}

/**
 * Test there is a piece at a specific tile after setting it.
 */
TEST(ChessBoardTests, SetPieceAtTile){
    ChessBoard board;
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    board.setPiece(0, 0, std::move(pawn1B));
    EXPECT_TRUE(board.isPieceAt(0, 0)) << "Piece should be set at (0, 0)!";
}
/**
 * Test there is no piece at a specific tile after killing it.
 */
TEST(ChessBoardTests, KillPieceAtTile){
    ChessBoard board;
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    board.setPiece(0, 0, std::move(pawn1B));
    board.killPiece(0, 0);
    EXPECT_FALSE(board.isPieceAt(0, 0)) << "Piece should not be set at (0, 0)!";
}

/**
 * Test the ChessBoard::move method moves a piece correctly.
 */
TEST(ChessBoardTests, MovePawn){
    ChessBoard board;
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    board.setPiece(0, 0, std::move(pawn1B));
    board.move(0, 0, 0, 1);
    EXPECT_FALSE(board.isPieceAt(0, 0)) << "Piece should not be at (0, 0) after move!";
    EXPECT_TRUE(board.isPieceAt(0, 1)) << "Piece should be at (0, 1) after move!";
}

/**
 * Test the ChessBoard::move method kills an enemy piece with one health point after moving onto it.
 */

TEST(ChessBoardTests, AttackEnemyPiece){
    ChessBoard board;
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    std::unique_ptr<Piece> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    pawn1B->setDamage(1); // Set damage to 1 to ensure it can kill
    pawn1W->setHealth(1); // Set health to 1 to ensure it can be killed
    board.setPiece(0, 0, std::move(pawn1B));
    board.setPiece(1, 1, std::move(pawn1W));
    board.move(0, 0, 1, 1);
    EXPECT_FALSE(board.isPieceAt(0, 0)) << "Black pawn should not be at (0, 0) after move!";
    EXPECT_TRUE(board.isPieceAt(1, 1)) << "Black pawn should be at (1, 1) after move!";
}

/**
 * Test the ChessBoard::move method damages an enemy piece 
 * with more than one health point after moving onto it, when moved piece has 1 damage.
 */
TEST(ChessBoardTests, DamageEnemyPiece){
    ChessBoard board;
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    std::unique_ptr<Piece> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    pawn1B->setDamage(1); // Set damage to 1
    pawn1W->setHealth(2); // Set health to 2 to ensure it can be damaged but not killed
    board.setPiece(0, 0, std::move(pawn1B));
    board.setPiece(1, 1, std::move(pawn1W));
    board.move(0, 0, 1, 1);
    EXPECT_TRUE(board.isPieceAt(0, 0)) << "Black pawn should be at (0, 0) after move!";
    EXPECT_TRUE(board.isPieceAt(1, 1)) << "White pawn should be at (1, 1) after move!";
    EXPECT_EQ(board.getHealthOfPiece(1, 1), 1) << "White pawn should have health reduced to 1 after being damaged!";
}