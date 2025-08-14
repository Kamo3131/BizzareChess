#include <gtest/gtest.h>
#include "ChessBoard.hpp"
#include "Queen.hpp"

/**
 * Test the Queen::move method allows moving diagonally by any number of tiles.
 */
TEST(QueenTests, MoveDiagonally){
    std::unique_ptr<Piece> queen1B = std::make_unique<Queen>(Piece::Team::BLACK);
    EXPECT_TRUE(queen1B->move(3, 3)) << "Queen should be able to move diagonally by 3 tiles!";
    EXPECT_TRUE(queen1B->move(-2, -2)) << "Queen should be able to move diagonally by -2 tiles!";
    EXPECT_TRUE(queen1B->move(2, -2)) << "Queen should be able to move diagonally by 2 tiles in opposite direction!";
    EXPECT_TRUE(queen1B->move(-3, 3)) << "Queen should be able to move diagonally by -3 tiles in opposite direction!";
}
/**
 * Test the Queen::move method allows moving horizontally by any number of tiles.
 */
TEST(QueenTests, MoveHorizontally){
    std::unique_ptr<Piece> queen1B = std::make_unique<Queen>(Piece::Team::BLACK);
    EXPECT_TRUE(queen1B->move(5, 0)) << "Queen should be able to move horizontally by 5 tiles!";
    EXPECT_TRUE(queen1B->move(-4, 0)) << "Queen should be able to move horizontally by -4 tiles!";
}
/**
 * Test the Queen::move method allows moving vertically by any number of tiles.
 */
TEST(QueenTests, MoveVertically){
    std::unique_ptr<Piece> queen1B = std::make_unique<Queen>(Piece::Team::BLACK);
    EXPECT_TRUE(queen1B->move(0, 6)) << "Queen should be able to move vertically by 6 tiles!";
    EXPECT_TRUE(queen1B->move(0, -5)) << "Queen should be able to move vertically by -5 tiles!";
}
/**
 * Test the Queen::move method does not allow moving in any other direction.
 */
TEST(QueenTests, MoveInvalidDirections){
    std::unique_ptr<Piece> queen1B = std::make_unique<Queen>(Piece::Team::BLACK);
    EXPECT_FALSE(queen1B->move(2, 3)) << "Queen should not be able to move this way!";
    EXPECT_FALSE(queen1B->move(-3, 1)) << "Queen should not be able to move this way!";
    EXPECT_FALSE(queen1B->move(1, -2)) << "Queen should not be able to move this way!";
}
/**
 * Test the Queen::move method does not allow moving if no movement is specified.
 */
TEST(QueenTests, MoveNoMovement){
    std::unique_ptr<Piece> queen1B = std::make_unique<Queen>(Piece::Team::BLACK);
    EXPECT_FALSE(queen1B->move(0, 0)) << "Queen should not be able to move if no movement is specified!";
}
/**
 * Test the Queen::attack method allows attacking diagonally.
 */
TEST(QueenTests, AttackDiagonally){
    std::unique_ptr<Piece> queen1B = std::make_unique<Queen>(Piece::Team::BLACK);
    EXPECT_TRUE(queen1B->attack(3, 3)) << "Queen should be able to attack diagonally by 3 tiles!";
    EXPECT_TRUE(queen1B->attack(-2, -2)) << "Queen should be able to attack diagonally by -2 tiles!";
    EXPECT_TRUE(queen1B->attack(2, -2)) << "Queen should be able to attack diagonally by 2 tiles in opposite direction!";
    EXPECT_TRUE(queen1B->attack(-3, 3)) << "Queen should be able to attack diagonally by -3 tiles in opposite direction!";
}
/**
 * Test the Queen::attack method allows attacking horizontally.
 */
TEST(QueenTests, AttackHorizontally){
    std::unique_ptr<Piece> queen1B = std::make_unique<Queen>(Piece::Team::BLACK);
    EXPECT_TRUE(queen1B->attack(5, 0)) << "Queen should be able to attack horizontally by 5 tiles!";
    EXPECT_TRUE(queen1B->attack(-4, 0)) << "Queen should be able to attack horizontally by -4 tiles!";
}
/**
 * Test the Queen::attack method allows attacking vertically.
 */
TEST(QueenTests, AttackVertically){
    std::unique_ptr<Piece> queen1B = std::make_unique<Queen>(Piece::Team::BLACK);
    EXPECT_TRUE(queen1B->attack(0, 6)) << "Queen should be able to attack vertically by 6 tiles!";
    EXPECT_TRUE(queen1B->attack(0, -5)) << "Queen should be able to attack vertically by -5 tiles!";
}
/**
 * Test the Queen::attack method does not allow attacking in any other direction.
 */
TEST(QueenTests, AttackInvalidDirections){
    std::unique_ptr<Piece> queen1B = std::make_unique<Queen>(Piece::Team::BLACK);
    EXPECT_FALSE(queen1B->attack(2, 3)) << "Queen should not be able to attack this way!";
    EXPECT_FALSE(queen1B->attack(-3, 1)) << "Queen should not be able to attack this way!";
    EXPECT_FALSE(queen1B->attack(1, -2)) << "Queen should not be able to attack this way!";
}
/**
 * Test the Queen::attack method does not allow attacking if no movement is specified.
 */
TEST(QueenTests, AttackNoMovement){
    std::unique_ptr<Piece> queen1B = std::make_unique<Queen>(Piece::Team::BLACK);
    EXPECT_FALSE(queen1B->attack(0, 0)) << "Queen should not be able to attack if no movement is specified!";
}
/**
 * Test the Queen type is correctly set.
 */
TEST(QueenTests, TypeIsQueen) {
    std::unique_ptr<Piece> queen1B = std::make_unique<Queen>(Piece::Team::BLACK);
    EXPECT_EQ(queen1B->getType(), Piece::Type::QUEEN) << "Queen type should be QUEEN!";
}
