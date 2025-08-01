#include <gtest/gtest.h>
#include "ChessBoard.hpp"

/**
 * Test the ChessBoard constructor initializes horizontal and vertical sizes to 8.
 */
TEST(ChessBoardTests, DefaultConstructor) {
    ChessBoard board;
    EXPECT_EQ(board.getHorizontal(), 8) << "[FAIL] Default constructor failed to set horizontal size!";
    EXPECT_EQ(board.getVertical(), 8) << "[FAIL] Default constructor failed to set vertical size!";
}