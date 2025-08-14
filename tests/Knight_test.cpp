#include <gtest/gtest.h>
#include "ChessBoard.hpp"
#include "Knight.hpp"

/**
 * Test the Knight::move method allows moving vertically by 2 tiles and horizontally by 1 tile.
 */
TEST(KnightTests, MoveVerticalByTwoAndHorizontalByOne) {
    std::unique_ptr<Piece> knight1B = std::make_unique<Knight>(Piece::Team::BLACK);
    EXPECT_TRUE(knight1B->move(1, 2)) << "Knight should be able to move forward by 2 tiles and to the right 1 tile!";
    EXPECT_TRUE(knight1B->move(-1, 2)) << "Knight should be able to move forward by 2 tiles and to the left 1 tile!";
    EXPECT_TRUE(knight1B->move(1, -2)) << "Knight should be able to move backward by 2 tiles and to the right 1 tile!";
    EXPECT_TRUE(knight1B->move(-1, -2)) << "Knight should be able to move backward by 2 tiles and to the left 1 tile!";
}
/**
 * Test the Knight::move method allows moving horizontally by 2 tiles and vertically by 1 tile.
 */
TEST(KnightTests, MoveHorizontalByTwoAndVerticalByOne) {
    std::unique_ptr<Piece> knight1B = std::make_unique<Knight>(Piece::Team::BLACK);
    EXPECT_TRUE(knight1B->move(2, 1)) << "Knight should be able to move to the right by 2 tiles and forward by 1 tile!";
    EXPECT_TRUE(knight1B->move(-2, 1)) << "Knight should be able to move to the left by 2 tiles and forward by 1 tile!";
    EXPECT_TRUE(knight1B->move(2, -1)) << "Knight should be able to move to the right by 2 tiles and backward by 1 tile!";
    EXPECT_TRUE(knight1B->move(-2, -1)) << "Knight should be able to move to the left by 2 tiles and backward by 1 tile!";
}
/**
 * Test the Knight::move method does not allow moving in any other direction.
 */
TEST(KnightTests, MoveInvalidDirections) {
    std::unique_ptr<Piece> knight1B = std::make_unique<Knight>(Piece::Team::BLACK);
    EXPECT_FALSE(knight1B->move(3, 3)) << "Knight should not be able to move this way!";
    EXPECT_FALSE(knight1B->move(-3, -3)) << "Knight should not be able to move this way!";
    EXPECT_FALSE(knight1B->move(3, -1)) << "Knight should not be able to move this way!";
    EXPECT_FALSE(knight1B->move(-1, 3)) << "Knight should not be able to move this way!";
}
/**
 * Test the Knight::move method does not allow moving if no movement is specified.
 */
TEST(KnightTests, MoveNoMovement) {
    std::unique_ptr<Piece> knight1B = std::make_unique<Knight>(Piece::Team::BLACK);
    EXPECT_FALSE(knight1B->move(0, 0)) << "Knight should not be able to move if no movement is specified!";
}
/**
 * Test the Knight::attack method allows attacking vertically by 2 tiles and horizontally by 1 tile.
 */
TEST(KnightTests, AttackVerticalByTwoAndHorizontalByOne) {
    std::unique_ptr<Piece> knight1B = std::make_unique<Knight>(Piece::Team::BLACK);
    EXPECT_TRUE(knight1B->attack(1, 2)) << "Knight should be able to attack forward by 2 tiles and to the right 1 tile!";
    EXPECT_TRUE(knight1B->attack(-1, 2)) << "Knight should be able to attack forward by 2 tiles and to the left 1 tile!";
    EXPECT_TRUE(knight1B->attack(1, -2)) << "Knight should be able to attack backward by 2 tiles and to the right 1 tile!";
    EXPECT_TRUE(knight1B->attack(-1, -2)) << "Knight should be able to attack backward by 2 tiles and to the left 1 tile!";
}
/**
 * Test the Knight::attack method allows attacking horizontally by 2 tiles and vertically by 1 tile.
 */
TEST(KnightTests, AttackHorizontalByTwoAndVerticalByOne) {
    std::unique_ptr<Piece> knight1B = std::make_unique<Knight>(Piece::Team::BLACK);
    EXPECT_TRUE(knight1B->attack(2, 1)) << "Knight should be able to attack to the right by 2 tiles and forward by 1 tile!";
    EXPECT_TRUE(knight1B->attack(-2, 1)) << "Knight should be able to attack to the left by 2 tiles and forward by 1 tile!";
    EXPECT_TRUE(knight1B->attack(2, -1)) << "Knight should be able to attack to the right by 2 tiles and backward by 1 tile!";
    EXPECT_TRUE(knight1B->attack(-2, -1)) << "Knight should be able to attack to the left by 2 tiles and backward by 1 tile!";
}
/**
 * Test the Knight::attack method does not allow attacking in any other direction.
 */
TEST(KnightTests, AttackInvalidDirections) {
    std::unique_ptr<Piece> knight1B = std::make_unique<Knight>(Piece::Team::BLACK);
    EXPECT_FALSE(knight1B->attack(3, 3)) << "Knight should not be able to attack this way!";
    EXPECT_FALSE(knight1B->attack(-3, -3)) << "Knight should not be able to attack this way!";
    EXPECT_FALSE(knight1B->attack(3, -1)) << "Knight should not be able to attack this way!";
    EXPECT_FALSE(knight1B->attack(-1, 3)) << "Knight should not be able to attack this way!";
}
/**
 * Test the Knight::attack method does not allow attacking if no movement is specified.
 */
TEST(KnightTests, AttackNoMovement) {
    std::unique_ptr<Piece> knight1B = std::make_unique<Knight>(Piece::Team::BLACK);
    EXPECT_FALSE(knight1B->attack(0, 0)) << "Knight should not be able to attack if no movement is specified!";
}
/**
 * Test the Knight type is correctly set.
 */
TEST(KnightTests, TypeIsKnight) {
    std::unique_ptr<Piece> knight1B = std::make_unique<Knight>(Piece::Team::BLACK);
    EXPECT_EQ(knight1B->getType(), Piece::Type::KNIGHT) << "Knight type should be KNIGHT!";
}