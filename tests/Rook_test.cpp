#include <gtest/gtest.h>
#include "ChessBoard.hpp"
#include "Rook.hpp"

/**
 * Test the Rook::move method allows moving horizontally by any number of tiles.
 */
TEST(RookTests, MoveHorizontally) {
    std::unique_ptr<Piece> rook1B = std::make_unique<Rook>(Piece::Team::BLACK);
    EXPECT_TRUE(rook1B->move(3, 0)) << "Rook should be able to move horizontally by 3 tiles!";
    EXPECT_TRUE(rook1B->move(-2, 0)) << "Rook should be able to move horizontally by -2 tiles!";
}
/**
 * Test the Rook::move method allows moving vertically by any number of tiles.
 */
TEST(RookTests, MoveVertically) {
    std::unique_ptr<Piece> rook1B = std::make_unique<Rook>(Piece::Team::BLACK);
    EXPECT_TRUE(rook1B->move(0, 4)) << "Rook should be able to move vertically by 4 tiles!";
    EXPECT_TRUE(rook1B->move(0, -3)) << "Rook should be able to move vertically by -3 tiles!";
}
/**
 * Test the Rook::move method does not allow moving diagonally.
 */
TEST(RookTests, MoveDiagonally) {
    std::unique_ptr<Piece> rook1B = std::make_unique<Rook>(Piece::Team::BLACK);
    EXPECT_FALSE(rook1B->move(2, 2)) << "Rook should not be able to move diagonally!";
    EXPECT_FALSE(rook1B->move(-1, -1)) << "Rook should not be able to move diagonally!";
}
/**
 * Test the Rook::move method does not allow moving in any other direction.
 */
TEST(RookTests, MoveInvalidDirections) {
    std::unique_ptr<Piece> rook1B = std::make_unique<Rook>(Piece::Team::BLACK);
    EXPECT_FALSE(rook1B->move(2, 3)) << "Rook should not be able to move this way!";
    EXPECT_FALSE(rook1B->move(-3, 1)) << "Rook should not be able to move this way!";
    EXPECT_FALSE(rook1B->move(1, -2)) << "Rook should not be able to move this way!";
}
/**
 * Test the Rook::move method does not allow moving if no movement is specified.
 */
TEST(RookTests, MoveNoMovement) {
    std::unique_ptr<Piece> rook1B = std::make_unique<Rook>(Piece::Team::BLACK);
    EXPECT_FALSE(rook1B->move(0, 0)) << "Rook should not be able to move if no movement is specified!";
}
/**
 * Test the Rook::attack method allows attacking horizontally.
 */
TEST(RookTests, AttackHorizontally) {
    std::unique_ptr<Piece> rook1B = std::make_unique<Rook>(Piece::Team::BLACK);
    EXPECT_TRUE(rook1B->attack(3, 0)) << "Rook should be able to attack horizontally by 3 tiles!";
    EXPECT_TRUE(rook1B->attack(-2, 0)) << "Rook should be able to attack horizontally by -2 tiles!";
}
/**
 * Test the Rook::attack method allows attacking vertically.
 */
TEST(RookTests, AttackVertically) {
    std::unique_ptr<Piece> rook1B = std::make_unique<Rook>(Piece::Team::BLACK);
    EXPECT_TRUE(rook1B->attack(0, 4)) << "Rook should be able to attack vertically by 4 tiles!";
    EXPECT_TRUE(rook1B->attack(0, -3)) << "Rook should be able to attack vertically by -3 tiles!";
}
/**
 * Test the Rook::attack method does not allow attacking diagonally.
 */
TEST(RookTests, AttackDiagonally) {
    std::unique_ptr<Piece> rook1B = std::make_unique<Rook>(Piece::Team::BLACK);
    EXPECT_FALSE(rook1B->attack(2, 2)) << "Rook should not be able to attack diagonally!";
    EXPECT_FALSE(rook1B->attack(-1, -1)) << "Rook should not be able to attack diagonally!";
}
/**
 * Test the Rook::attack method does not allow attacking in any other direction.
 */
TEST(RookTests, AttackInvalidDirections) {
    std::unique_ptr<Piece> rook1B = std::make_unique<Rook>(Piece::Team::BLACK);
    EXPECT_FALSE(rook1B->attack(2, 3)) << "Rook should not be able to attack this way!";
    EXPECT_FALSE(rook1B->attack(-3, 1)) << "Rook should not be able to attack this way!";
    EXPECT_FALSE(rook1B->attack(1, -2)) << "Rook should not be able to attack this way!";
}
/**
 * Test the Rook::attack method does not allow attacking if no attack is specified.
 */
TEST(RookTests, AttackNoAttack) {
    std::unique_ptr<Piece> rook1B = std::make_unique<Rook>(Piece::Team::BLACK);
    EXPECT_FALSE(rook1B->attack(0, 0)) << "Rook should not be able to attack if no attack is specified!";
}
