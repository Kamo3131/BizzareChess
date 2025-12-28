#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include <cmath>
#include "imgui.h"
#include "imgui-SFML.h"
#include "Piece.hpp"

class Chessboard3D{
    public:
    using size = std::size_t;
    Chessboard3D(sf::Vector2f size_of_square);
    /**
     * @brief draws piece based on their team and type.
     * @param type is the type of piece which will be drawn.
     * @param color defines color of the piece.
     * @param position defines where on the chessboard piece will be drawn.
     * @param scale defines size of the piece. Max scale is 1.0f. Min scale is 0.1f.
     */
    void drawPiece(const Piece::Type type, const Piece::Team color, const sf::Vector2i position, const float scale = 0.5f);
    /**
     * @brief draws 3D square tile shape.
     * @param color defines color of the tile.
     * @param position defines position of the square.
     */
    void drawSquareTile(Piece::Team color, sf::Vector2f position);
    enum Direction {
        EAST, SOUTH, WEST, NORTH
    };
    /**
     * @brief draws chessboard wall.
     * @param position defines position of the wall.
     * @param direction defines which direction wall faces.
     */
    void drawChessboardWall(sf::Vector2f position, Direction direction);

    void highlightSelectedPiece(sf::Vector2f position);
    void highlightPossibleSquare(sf::Vector2f position);

    [[nodiscard]] sf::Vector2f getSize() const;
    private:
    /**
     * @brief draws default 3D pawn shape.
     * @param color defines color of the pawn.
     * @param position defines where on the chessboard piece will be drawn.
     * @param scale defines size of the piece. Max scale is 1.0f. Min scale is 0.1f.
     */
    void drawDefaultPawn(Piece::Team color, sf::Vector2i position, float scale = 0.5f);
    /**
     * @brief draws default 3D knight shape.
     * @param color defines color of the knight.
     * @param position defines where on the chessboard piece will be drawn.
     * @param scale defines size of the piece. Max scale is 1.0f. Min scale is 0.1f.
     */
    void drawDefaultKnight(Piece::Team color, sf::Vector2i position, float scale = 0.5f);
    /**
     * @brief draws default 3D king shape.
     * @param color defines color of the king.
     * @param position defines where on the chessboard piece will be drawn.
     * @param scale defines size of the piece. Max scale is 1.0f. Min scale is 0.1f.
     */
    void drawDefaultKing(Piece::Team color, sf::Vector2i position, float scale = 0.5f);
    /**
     * @brief draws default 3D queen shape.
     * @param color defines color of the queen.
     * @param position defines where on the chessboard piece will be drawn.
     * @param scale defines size of the piece. Max scale is 1.0f. Min scale is 0.1f.
     */
    void drawDefaultQueen(Piece::Team color, sf::Vector2i position, float scale = 0.5f);
    /**
     * @brief draws default 3D rook shape.
     * @param color defines color of the rook.
     * @param position defines where on the chessboard piece will be drawn.
     * @param scale defines size of the piece. Max scale is 1.0f. Min scale is 0.1f.
     */
    void drawDefaultRook(Piece::Team color, sf::Vector2i position, float scale = 0.5f);
    /**
     * @brief draws default 3D bishop shape.
     * @param color defines color of the bishop.
     * @param position defines where on the chessboard piece will be drawn.
     * @param scale defines size of the piece. Max scale is 1.0f. Min scale is 0.1f.
     */
    void drawDefaultBishop(Piece::Team color, sf::Vector2i position, float scale = 0.5f);
    /**
     * @brief draws a basic circle.
     * @param cx is an x coordinate of circle.
     * @param cy is an y coordinate of circle.
     * @param r is a radius of circle.
     * @param num_segments is a number of segments which make the circle.
     */
    void drawCircle(float cx, float cy, float r, int num_segments) const;
    /**
     * Default size of the piece is about 50% size of the square (it depends on the piece too). 
     * Size.x serves as a width and depth of the tile. Size.y serves as it's height
     */
    sf::Vector2f _size_of_square;
};