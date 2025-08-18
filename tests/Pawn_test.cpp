#include <gtest/gtest.h>
#include "ChessBoard.hpp"
#include "Pawn.hpp"

/**
 * Test the Pawn::move method allows moving forward (or backwards if black team) by 1 tile. 
 */
TEST(PawnTests, MoveForwardByOneTile) {
    std::unique_ptr<Piece> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    EXPECT_TRUE(pawn1W->move(0, 1)) << "Pawn should be at (0, 1) after move!";
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_TRUE(pawn1B->move(0, -1)) << "Pawn should be at (0, -1) after move!";
}
/**
 * Test the Pawn::move method allows moving forward (or backwards if black team) by 2 tiles on first move.
 */
TEST(PawnTests, MoveForwardByTwoTilesOnFirstMove) {
    std::unique_ptr<Piece> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    EXPECT_TRUE(pawn1W->move(0, 2)) << "Pawn should be at (0, 2) after move!";
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_TRUE(pawn1B->move(0, -2)) << "Pawn should be at (0, -2) after move!";
}
/**
 * Test the Pawn::move method does not allow moving forward (or backwards if black team) by 2 tiles after first move.
 */
TEST(PawnTests, MoveForwardByTwoTilesAfterFirstMove) {
    std::unique_ptr<Piece> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    pawn1W->increaseMoveNumber(); // Simulate first move
    EXPECT_FALSE(pawn1W->move(0, 2)) << "Pawn should not be able to move forward by 2 tiles after first move!";
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    pawn1B->increaseMoveNumber(); // Simulate first move
    EXPECT_FALSE(pawn1B->move(0, -2)) << "Pawn should not be able to move forward by 2 tiles after first move!";
}
/**
 * Test if en passant status can be set and retrieved correctly.
 */
TEST(PawnTests, EnPassantStatus) {
    std::unique_ptr<Pawn> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE); 
    pawn1W->setEnPassant(1, true);
    auto enPassantStatus = pawn1W->getEnPassant();
    EXPECT_EQ(enPassantStatus.first, 1) << "En passant turns left should be 1!";
    EXPECT_TRUE(enPassantStatus.second) << "Pawn should be able to be captured en passant!";

    std::unique_ptr<Pawn> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    pawn1B->setEnPassant(0, false);
    enPassantStatus = pawn1B->getEnPassant();
    EXPECT_EQ(enPassantStatus.first, 0) << "En passant turns left should be 0!";
    EXPECT_FALSE(enPassantStatus.second) << "Pawn should not be able to be captured en passant!";
}
/**
 * Test the Pawn::move method does not allow moving backwards (or forward if black team) by any tiles.
 */
TEST(PawnTests, MoveBackwards) {
    std::unique_ptr<Piece> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    EXPECT_FALSE(pawn1W->move(0, -1)) << "Pawn should not be able to move backwards!";
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_FALSE(pawn1B->move(0, 1)) << "Pawn should not be able to move backwards!";
}
/**
 * Test the Pawn::move method does not allow moving horizontally regardless of the team.
 */
TEST(PawnTests, MoveHorizontally) {
    std::unique_ptr<Piece> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    EXPECT_FALSE(pawn1W->move(1, 0)) << "Pawn should not be able to move horizontally to the right!";
    EXPECT_FALSE(pawn1W->move(-1, 0)) << "Pawn should not be able to move horizontally to the left!";
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_FALSE(pawn1B->move(1, 0)) << "Pawn should not be able to move horizontally to the right!";
    EXPECT_FALSE(pawn1B->move(-1, 0)) << "Pawn should not be able to move horizontally to the left!";
}

/**
 * Test the Pawn::attack method allows attacking diagonally.
 */
TEST(PawnTests, AttackDiagonally) {
    std::unique_ptr<Piece> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    EXPECT_TRUE(pawn1W->attack(1, 1)) << "Pawn should be able to attack diagonally to the right!";
    EXPECT_TRUE(pawn1W->attack(-1, 1)) << "Pawn should be able to attack diagonally to the left!";
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_TRUE(pawn1B->attack(1, -1)) << "Pawn should be able to attack diagonally to the right!";
    EXPECT_TRUE(pawn1B->attack(-1, -1)) << "Pawn should be able to attack diagonally to the left!";
}
/**
 * Test the Pawn::attack method does not allow attacking straight ahead.
 */
TEST(PawnTests, AttackForward) {
    std::unique_ptr<Piece> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    EXPECT_FALSE(pawn1W->attack(0, 1)) << "Pawn should not be able to attack straight ahead!";
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_FALSE(pawn1B->attack(0, 1)) << "Pawn should not be able to attack straight ahead!";
}
/**
 * Test the Pawn::attack method does not allow attacking backwards.
 */
TEST(PawnTests, AttackBackwards) {
    std::unique_ptr<Piece> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    EXPECT_FALSE(pawn1W->attack(0, -1)) << "Pawn should not be able to attack backwards!";
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_FALSE(pawn1B->attack(0, 1)) << "Pawn should not be able to attack backwards!";
}
/**
 * Test the Pawn::attack method does not allow attacking diagonally backwards.
 */
TEST(PawnTests, AttackDiagonallyBackwards) {
    std::unique_ptr<Piece> pawn1W = std::make_unique<Pawn>(Piece::Team::WHITE);
    EXPECT_FALSE(pawn1W->attack(1, -1)) << "Pawn should not be able to attack diagonally backwards!";
    EXPECT_FALSE(pawn1W->attack(-1, -1)) << "Pawn should not be able to attack diagonally backwards!";

    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_FALSE(pawn1B->attack(1, 1)) << "Pawn should not be able to attack diagonally backwards!";
    EXPECT_FALSE(pawn1B->attack(-1, 1)) << "Pawn should not be able to attack diagonally backwards!";
}
/**
 * Test the Pawn type is correctly set.
 */
TEST(PawnTests, TypeIsPawn) {
    std::unique_ptr<Piece> pawn1B = std::make_unique<Pawn>(Piece::Team::BLACK);
    EXPECT_EQ(pawn1B->getType(), Piece::Type::PAWN) << "Pawn type should be PAWN!";
}