#include <gtest/gtest.h>
#include "ChessBoard.hpp"
#include "King.hpp"
/**
 * Test the King::move method allows moving diagonally by 1 tile.
 */
TEST(KingTests, MoveDiagonally) {
    std::unique_ptr<Piece> king1B = std::make_unique<King>(Piece::Team::BLACK);
    EXPECT_TRUE(king1B->move(1, 1)) << "King should be able to move diagonally by 1 tile!";
    EXPECT_TRUE(king1B->move(-1, -1)) << "King should be able to move diagonally by -1 tile!";
    EXPECT_TRUE(king1B->move(1, -1)) << "King should be able to move diagonally by 1 tile in opposite direction!";
    EXPECT_TRUE(king1B->move(-1, 1)) << "King should be able to move diagonally by -1 tile in opposite direction!";
}
/**
 * Test the King::move method allows moving horizontally by 1 tile.
 */
TEST(KingTests, MoveHorizontally) {
    std::unique_ptr<Piece> king1B = std::make_unique<King>(Piece::Team::BLACK);
    EXPECT_TRUE(king1B->move(1, 0)) << "King should be able to move horizontally by 1 tile!";
    EXPECT_TRUE(king1B->move(-1, 0)) << "King should be able to move horizontally by -1 tile!";
}
/**
 * Test the King::move method allows moving vertically by 1 tile.
 */
TEST(KingTests, MoveVertically) {
    std::unique_ptr<Piece> king1B = std::make_unique<King>(Piece::Team::BLACK);
    EXPECT_TRUE(king1B->move(0, 1)) << "King should be able to move vertically by 1 tile!";
    EXPECT_TRUE(king1B->move(0, -1)) << "King should be able to move vertically by -1 tile!";
}
/**
 * Test the King::move method does not allow moving in any other direction.
 */
TEST(KingTests, MoveInvalidDirections) {
    std::unique_ptr<Piece> king1B = std::make_unique<King>(Piece::Team::BLACK);
    EXPECT_FALSE(king1B->move(2, 2)) << "King should not be able to move this way!";
    EXPECT_FALSE(king1B->move(-2, -2)) << "King should not be able to move this way!";
    EXPECT_FALSE(king1B->move(2, -1)) << "King should not be able to move this way!";
    EXPECT_FALSE(king1B->move(-1, 2)) << "King should not be able to move this way!";
}
/**
 * Test the King::move method does not allow moving if no movement is specified.
 */
TEST(KingTests, MoveNoMovement) {
    std::unique_ptr<Piece> king1B = std::make_unique<King>(Piece::Team::BLACK);
    EXPECT_FALSE(king1B->move(0, 0)) << "King should not be able to move if no movement is specified!";
}
/**
 * Test the King::attack method allows attacking diagonally by 1 tile.
 */
TEST(KingTests, AttackDiagonally) {
    std::unique_ptr<Piece> king1B = std::make_unique<King>(Piece::Team::BLACK);
    EXPECT_TRUE(king1B->attack(1, 1)) << "King should be able to attack diagonally by 1 tile!";
    EXPECT_TRUE(king1B->attack(-1, -1)) << "King should be able to attack diagonally by -1 tile!";
    EXPECT_TRUE(king1B->attack(1, -1)) << "King should be able to attack diagonally by 1 tile in opposite direction!";
    EXPECT_TRUE(king1B->attack(-1, 1)) << "King should be able to attack diagonally by -1 tile in opposite direction!";
}
/**
 * Test the King::attack method allows attacking horizontally by 1 tile.
 */
TEST(KingTests, AttackHorizontally) {
    std::unique_ptr<Piece> king1B = std::make_unique<King>(Piece::Team::BLACK);
    EXPECT_TRUE(king1B->attack(1, 0)) << "King should be able to attack horizontally by 1 tile!";
    EXPECT_TRUE(king1B->attack(-1, 0)) << "King should be able to attack horizontally by -1 tile!";
}
/**
 * Test the King::attack method allows attacking vertically by 1 tile.
 */
TEST(KingTests, AttackVertically) {
    std::unique_ptr<Piece> king1B = std::make_unique<King>(Piece::Team::BLACK);
    EXPECT_TRUE(king1B->attack(0, 1)) << "King should be able to attack vertically by 1 tile!";
    EXPECT_TRUE(king1B->attack(0, -1)) << "King should be able to attack vertically by -1 tile!";
}
/**
 * Test the King::attack method does not allow attacking in any other direction.
 */
TEST(KingTests, AttackInvalidDirections) {
    std::unique_ptr<Piece> king1B = std::make_unique<King>(Piece::Team::BLACK);
    EXPECT_FALSE(king1B->attack(2, 2)) << "King should not be able to attack this way!";
    EXPECT_FALSE(king1B->attack(-2, -2)) << "King should not be able to attack this way!";
    EXPECT_FALSE(king1B->attack(2, -1)) << "King should not be able to attack this way!";
    EXPECT_FALSE(king1B->attack(-1, 2)) << "King should not be able to attack this way!";
}
/**
 * Test the King::attack method does not allow attacking if no movement is specified.
 */
TEST(KingTests, AttackNoMovement) {
    std::unique_ptr<Piece> king1B = std::make_unique<King>(Piece::Team::BLACK);
    EXPECT_FALSE(king1B->attack(0, 0)) << "King should not be able to attack if no movement is specified!";
}

/**
 * Test the King type is correctly set.
 */
TEST(KingTests, TypeIsKing) {
    std::unique_ptr<Piece> king1B = std::make_unique<King>(Piece::Team::BLACK);
    EXPECT_EQ(king1B->getType(), Piece::Type::KING) << "King type should be KING!";
}