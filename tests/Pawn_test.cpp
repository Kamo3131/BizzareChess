#include <gtest/gtest.h>
#include "ChessBoard.hpp"
#include "Pawn.hpp"

/**
 * Test the Pawn::move method allows moving forward by 1 tile.
 */
TEST(PawnTests, MoveForwardByOneTile) {
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_TRUE(pawn1B->move(0, 1)) << "Pawn should be at (0, 1) after move!";
}
/**
 * Test the Pawn::move method allows moving forward by 2 tiles on first move.
 */
TEST(PawnTests, MoveForwardByTwoTilesOnFirstMove) {
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_TRUE(pawn1B->move(0, 2)) << "Pawn should be at (0, 2) after move!";
}
/**
 * Test the Pawn::move method does not allow moving forward by 2 tiles after first move.
 */
TEST(PawnTests, MoveForwardByTwoTilesAfterFirstMove) {
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    pawn1B->increaseMoveNumber(); // Simulate first move
    EXPECT_FALSE(pawn1B->move(0, 2)) << "Pawn should not be able to move forward by 2 tiles after first move!";
}
/**
 * Test the Pawn::move method does not allow moving backwards by any tiles.
 */
TEST(PawnTests, MoveBackwards) {
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_FALSE(pawn1B->move(0, -1)) << "Pawn should not be able to move backwards!";
}
/**
 * Test the Pawn::move method does not allow moving horizontally.
 */
TEST(PawnTests, MoveHorizontally) {
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_FALSE(pawn1B->move(1, 0)) << "Pawn should not be able to move horizontally to the right!";
    EXPECT_FALSE(pawn1B->move(-1, 0)) << "Pawn should not be able to move horizontally to the left!";
}

/**
 * Test the Pawn::attack method allows attacking diagonally.
 */
TEST(PawnTests, AttackDiagonally) {
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_TRUE(pawn1B->attack(1, 1)) << "Pawn should be able to attack diagonally to the right!";
    EXPECT_TRUE(pawn1B->attack(-1, 1)) << "Pawn should be able to attack diagonally to the left!";
}
/**
 * Test the Pawn::attack method does not allow attacking straight ahead.
 */
TEST(PawnTests, AttackForward) {
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_FALSE(pawn1B->attack(0, 1)) << "Pawn should not be able to attack straight ahead!";
}
/**
 * Test the Pawn::attack method does not allow attacking backwards.
 */
TEST(PawnTests, AttackBackwards) {
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_FALSE(pawn1B->attack(0, -1)) << "Pawn should not be able to attack backwards!";
}
/**
 * Test the Pawn::attack method does not allow attacking diagonally backwards.
 */
TEST(PawnTests, AttackDiagonallyBackwards) {
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_FALSE(pawn1B->attack(1, -1)) << "Pawn should not be able to attack diagonally backwards!";
    EXPECT_FALSE(pawn1B->attack(-1, -1)) << "Pawn should not be able to attack diagonally backwards!";
}
/**
 * Test the Pawn type is correctly set.
 */
TEST(PawnTests, TypeIsPawn) {
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_EQ(pawn1B->getType(), Piece::Type::PAWN) << "Pawn type should be PAWN!";
}