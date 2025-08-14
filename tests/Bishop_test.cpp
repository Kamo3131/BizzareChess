#include <gtest/gtest.h>
#include "ChessBoard.hpp"
#include "Bishop.hpp"
/**
 * Test the Bishop::move method allows moving diagonally by any number of tiles.
 */
TEST(BishopTests, MoveDiagonally) {
    std::unique_ptr<Piece> bishop1B = std::make_unique<Bishop>(Piece::Team::BLACK);
    EXPECT_TRUE(bishop1B->move(3, 3)) << "Bishop should be able to move diagonally by 3 tiles!";
    EXPECT_TRUE(bishop1B->move(-2, -2)) << "Bishop should be able to move diagonally by -2 tiles!";
    EXPECT_TRUE(bishop1B->move(2, -2)) << "Bishop should be able to move diagonally by 2 tiles in opposite direction!";
    EXPECT_TRUE(bishop1B->move(-3, 3)) << "Bishop should be able to move diagonally by -3 tiles in opposite direction!";
}
/**
 * Test the Bishop::move method does not allow moving horizontally.
 */
TEST(BishopTests, MoveHorizontally) {
    std::unique_ptr<Piece> bishop1B = std::make_unique<Bishop>(Piece::Team::BLACK);
    EXPECT_FALSE(bishop1B->move(3, 0)) << "Bishop should not be able to move horizontally by 3 tiles!";
    EXPECT_FALSE(bishop1B->move(-2, 0)) << "Bishop should not be able to move horizontally by -2 tiles!";
}
/**
 * Test the Bishop::move method does not allow moving vertically.
 */
TEST(BishopTests, MoveVertically) {
    std::unique_ptr<Piece> bishop1B = std::make_unique<Bishop>(Piece::Team::BLACK);
    EXPECT_FALSE(bishop1B->move(0, 4)) << "Bishop should not be able to move vertically by 4 tiles!";
    EXPECT_FALSE(bishop1B->move(0, -3)) << "Bishop should not be able to move vertically by -3 tiles!";
}
/**
 * Test the Bishop::move method does not allow moving in any other direction.
 */
TEST(BishopTests, MoveInvalidDirections) {
    std::unique_ptr<Piece> bishop1B = std::make_unique<Bishop>(Piece::Team::BLACK);
    EXPECT_FALSE(bishop1B->move(2, 3)) << "Bishop should not be able to move this way!";
    EXPECT_FALSE(bishop1B->move(-3, 1)) << "Bishop should not be able to move this way!";
    EXPECT_FALSE(bishop1B->move(1, -2)) << "Bishop should not be able to move this way!";
}
/**
 * Test the Bishop::move method does not allow moving if no movement is specified.
 */
TEST(BishopTests, MoveNoMovement) {
    std::unique_ptr<Piece> bishop1B = std::make_unique<Bishop>(Piece::Team::BLACK);
    EXPECT_FALSE(bishop1B->move(0, 0)) << "Bishop should not be able to move if no movement is specified!";
}
/**
 * Test the Bishop::attack method allows attacking diagonally.
 */
TEST(BishopTests, AttackDiagonally) {
    std::unique_ptr<Piece> bishop1B = std::make_unique<Bishop>(Piece::Team::BLACK);
    EXPECT_TRUE(bishop1B->attack(3, 3)) << "Bishop should be able to attack diagonally by 3 tiles!";
    EXPECT_TRUE(bishop1B->attack(-2, -2)) << "Bishop should be able to attack diagonally by -2 tiles!";
    EXPECT_TRUE(bishop1B->attack(2, -2)) << "Bishop should be able to attack diagonally by 2 tiles in opposite direction!";
    EXPECT_TRUE(bishop1B->attack(-3, 3)) << "Bishop should be able to attack diagonally by -3 tiles in opposite direction!";
}
/**
 * Test the Bishop::attack method does not allow attacking horizontally.
 */
TEST(BishopTests, AttackHorizontally) {
    std::unique_ptr<Piece> bishop1B = std::make_unique<Bishop>(Piece::Team::BLACK);
    EXPECT_FALSE(bishop1B->attack(3, 0)) << "Bishop should not be able to attack horizontally by 3 tiles!";
    EXPECT_FALSE(bishop1B->attack(-2, 0)) << "Bishop should not be able to attack horizontally by -2 tiles!";
}
/**
 * Test the Bishop::attack method does not allow attacking vertically.
 */
TEST(BishopTests, AttackVertically) {
    std::unique_ptr<Piece> bishop1B = std::make_unique<Bishop>(Piece::Team::BLACK);
    EXPECT_FALSE(bishop1B->attack(0, 4)) << "Bishop should not be able to attack vertically by 4 tiles!";
    EXPECT_FALSE(bishop1B->attack(0, -3)) << "Bishop should not be able to attack vertically by -3 tiles!";
}
/**
 * Test the Bishop::attack method does not allow attacking in any other direction.
 */
TEST(BishopTests, AttackInvalidDirections) {
    std::unique_ptr<Piece> bishop1B = std::make_unique<Bishop>(Piece::Team::BLACK);
    EXPECT_FALSE(bishop1B->attack(2, 3)) << "Bishop should not be able to attack this way!";
    EXPECT_FALSE(bishop1B->attack(-3, 1)) << "Bishop should not be able to attack this way!";
    EXPECT_FALSE(bishop1B->attack(1, -2)) << "Bishop should not be able to attack this way!";
}
/**
 * Test the Bishop::attack method does not allow attacking if no movement is specified.
 */
TEST(BishopTests, AttackNoMovement) {
    std::unique_ptr<Piece> bishop1B = std::make_unique<Bishop>(Piece::Team::BLACK);
    EXPECT_FALSE(bishop1B->attack(0, 0)) << "Bishop should not be able to attack if no movement is specified!";
}
/**
 * Test the Bishop type is correctly set.
 */
TEST(BishopTests, TypeIsBishop) {
    std::unique_ptr<Piece> bishop1B = std::make_unique<Bishop>(Piece::Team::BLACK);
    EXPECT_EQ(bishop1B->getType(), Piece::Type::BISHOP) << "Bishop type should be BISHOP!";
}