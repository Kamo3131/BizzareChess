#include "Chessboard3D.hpp"


Chessboard3D::Chessboard3D(sf::Vector2f size_of_square) : _size_of_square{size_of_square}{}
void Chessboard3D::drawPiece(const Piece::Type type, const Piece::Team color, const sf::Vector2i position, const float scale){
    switch(type){
        case Piece::Type::PAWN:
            drawDefaultPawn(color, position, scale);
            break;
        case Piece::Type::BISHOP:
            drawDefaultBishop(color, position, scale);
            break;
        case Piece::Type::KING:
            drawDefaultKing(color, position, scale);
            break;
        case Piece::Type::QUEEN:
            drawDefaultQueen(color, position, scale);
            break;
        case Piece::Type::KNIGHT:
            drawDefaultKnight(color, position, scale);
            break;
        case Piece::Type::ROOK:
            drawDefaultRook(color, position, scale);
            break;
        default:
            return;
    }
}
void Chessboard3D::drawDefaultPawn(Piece::Team color, sf::Vector2i position, float scale){
    glLineWidth(2.0);
    float scaled_square = scale * _size_of_square.x;
    float half_size_of_square = (scaled_square) / 2.f;
    if( color == Piece::Team::WHITE){
        glColor3f(0.95f, 0.95f, 0.70f);
    } else {
        glColor3f(0.2f, 0.2f, 0.5f);
    }
    float height = 1.f * scale;
    //Bottom
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
    glEnd();
    //Top
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //West
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //East
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //North
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
    glEnd();
    //South
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    glLineWidth(1.0);
}
void Chessboard3D::drawDefaultKnight(Piece::Team color, sf::Vector2i position, float scale){
    glLineWidth(2.0);
    float scaled_square = scale * _size_of_square.x;
    float half_size_of_square = (scaled_square) / 2.f;
    if( color == Piece::Team::WHITE){
        glColor3f(0.95f, 0.95f, 0.70f);
    } else {
        glColor3f(0.2f, 0.2f, 0.5f);
    }
    float height = 2.f * scale;
    //Bottom
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
    glEnd();
    //Top
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //West
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //East
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //North
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
    glEnd();
    //South
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //Helmet
    glColor3f(0.2f, 0.4f, 0.7f);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + 0.1f, height+0.2f, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height+0.2f, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height+0.2f, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height+0.2f, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    glLineWidth(1.0);
}
void Chessboard3D::drawDefaultKing(Piece::Team color, sf::Vector2i position, float scale){
    glLineWidth(2.0);
    float scaled_square = scale * _size_of_square.x;
    float half_size_of_square = (scaled_square) / 2.f;
    if( color == Piece::Team::WHITE){
        glColor3f(0.95f, 0.95f, 0.70f);
    } else {
        glColor3f(0.2f, 0.2f, 0.5f);
    }
    float height = 2.f * scale;
    //Bottom
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
    glEnd();
    //Top
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //West
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //East
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //North
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
    glEnd();
    //South
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();

    //Crown
    glColor3f(0.8f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + 0.1f, height+0.2f, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height+0.2f, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height+0.2f, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height+0.2f, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    glLineWidth(1.0);
}
void Chessboard3D::drawDefaultQueen(Piece::Team color, sf::Vector2i position, float scale){
    glLineWidth(2.0);
    float scaled_square = scale * _size_of_square.x;
    float half_size_of_square = (scaled_square) / 2.f;
    if( color == Piece::Team::WHITE){
        glColor3f(0.95f, 0.95f, 0.70f);
    } else {
        glColor3f(0.2f, 0.2f, 0.5f);
    }
    float height = 2.f * scale;
    //Bottom
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
    glEnd();
    //Top
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //West
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //East
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //North
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
    glEnd();
    //South
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //Crown    
    glColor3f(0.3f, 0.1f, 0.3f);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + 0.1f, height+0.2f, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height+0.2f, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height+0.2f, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height+0.2f, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    glLineWidth(1.0);
}
void Chessboard3D::drawDefaultRook(Piece::Team color, sf::Vector2i position, float scale){
    glLineWidth(2.0);
    float scaled_square = scale * _size_of_square.x;
    float half_size_of_square = (scaled_square) / 2.f;
    if( color == Piece::Team::WHITE){
        glColor3f(0.95f, 0.95f, 0.70f);
    } else {
        glColor3f(0.2f, 0.2f, 0.5f);
    }
    float height = 2.5f * scale;
    //Bottom
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
    glEnd();
    //Top
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //West
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //East
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //North
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
    glEnd();
    //South
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    glLineWidth(1.0);
}
void Chessboard3D::drawDefaultBishop(Piece::Team color, sf::Vector2i position, float scale){
    glLineWidth(2.0);
    float scaled_square = scale * _size_of_square.x;
    float half_size_of_square = (scaled_square) / 2.f;
    if( color == Piece::Team::WHITE){
        glColor3f(0.95f, 0.95f, 0.70f);
    } else {
        glColor3f(0.2f, 0.2f, 0.5f);
    }
    float height = 2.f * scale;
    //Bottom
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
    glEnd();
    //Top
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //West
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //East
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //North
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + 0.1f);
    glEnd();
    //South
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + scaled_square, 0.01f, position.y + half_size_of_square + scaled_square);
        glVertex3f(position.x + half_size_of_square + 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    //This bishops hat, I don't know the name
    glColor3f(1.0f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(position.x + half_size_of_square + 0.1f, height+0.2f, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height+0.2f, position.y + half_size_of_square + 0.1f);
        glVertex3f(position.x + half_size_of_square + 0.1f, height+0.2f, position.y + half_size_of_square + scaled_square - 0.1f);
        glVertex3f(position.x + half_size_of_square + scaled_square - 0.1f, height+0.2f, position.y + half_size_of_square + scaled_square - 0.1f);
    glEnd();
    glLineWidth(1.0);
}
void Chessboard3D::drawSquareTile(Piece::Team color, sf::Vector2f position){

    glLineWidth(2.0);
    
    glBegin(GL_QUADS);
        if( color == Piece::Team::WHITE){
            glColor3f(1.f, 1.f, 1.f);
        } else {
            glColor3f(0.f, 0.f, 0.f);
        }
        glVertex3f(position.x, 0, position.y); 
        glVertex3f(position.x + _size_of_square.x, 0, position.y);
        glVertex3f(position.x + _size_of_square.x, 0, position.y + _size_of_square.x);
        glVertex3f(position.x, 0, position.y + _size_of_square.x);
        
        glColor3f(0.6f, 0.3f, 0.1f);
        glVertex3f(position.x, - 0.5f * getSize().y, position.y); 
        glVertex3f(position.x + _size_of_square.x, - 0.5f * getSize().y, position.y);
        glVertex3f(position.x + _size_of_square.x, - 0.5f * getSize().y, position.y + _size_of_square.x);
        glVertex3f(position.x, - 0.5f * getSize().y, position.y + _size_of_square.x);
    glEnd();
    glLineWidth(1.0);
}

void Chessboard3D::drawChessboardWall(sf::Vector2f position, Chessboard3D::Direction direction)
{
        glColor3f(0.6f, 0.3f, 0.1f);
        glLineWidth(2.0);
        glBegin(GL_QUADS);
        switch(direction){
            case Chessboard3D::Direction::EAST:
                glVertex3f(position.x + _size_of_square.x, 0, position.y); 
                glVertex3f(position.x + _size_of_square.x, 0, position.y + _size_of_square.x);
                glVertex3f(position.x + _size_of_square.x, - 0.5f * getSize().y, position.y + _size_of_square.x);
                glVertex3f(position.x + _size_of_square.x, - 0.5f * getSize().y, position.y);
                break;
            case Chessboard3D::Direction::SOUTH:
                glVertex3f(position.x, 0, position.y + _size_of_square.x); 
                glVertex3f(position.x + _size_of_square.x, 0, position.y + _size_of_square.x);
                glVertex3f(position.x + _size_of_square.x, - 0.5f * getSize().y, position.y + _size_of_square.x);
                glVertex3f(position.x, - 0.5f * getSize().y, position.y + _size_of_square.x);
                break;
            case Chessboard3D::Direction::WEST:
                glVertex3f(position.x, 0, position.y); 
                glVertex3f(position.x, 0, position.y + _size_of_square.x);
                glVertex3f(position.x, - 0.5f * getSize().y, position.y + _size_of_square.x);
                glVertex3f(position.x, - 0.5f * getSize().y, position.y);
                break;
            case Chessboard3D::Direction::NORTH:
                glVertex3f(position.x, 0, position.y); 
                glVertex3f(position.x + _size_of_square.x, 0, position.y);
                glVertex3f(position.x + _size_of_square.x, - 0.5f * getSize().y, position.y);
                glVertex3f(position.x, - 0.5f * getSize().y, position.y);
                break;
        }
        glEnd();
        glLineWidth(1.0);
}
[[nodiscard]] sf::Vector2f Chessboard3D::getSize() const{
    return _size_of_square;
}

void Chessboard3D::drawCircle(float cx, float cy, float r, int num_segments) const{
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < (num_segments+1); i++)   {
        float theta = 2.0f * 3.1415926f * static_cast<float>(i) / static_cast<float>(num_segments);
        float x = r * cosf(theta); 
        float y = r * sinf(theta);
        glVertex3f(x + cx, 0.01f, y + cy);
        x = (r - 0.1f) * cosf(theta); 
        y = (r - 0.1f) * sinf(theta);
        glVertex3f(x + cx, 0.01f, y + cy);
    }
    glEnd();
}

void Chessboard3D::highlightSelectedPiece(sf::Vector2f position){
    glColor3f(0.0f, 0.5f, 1.0f);
    float half_of_square = _size_of_square.x/2.f;
    drawCircle(position.x + half_of_square, position.y + half_of_square, half_of_square, 16);
}
void Chessboard3D::highlightPossibleSquare(sf::Vector2f position){
    glColor3f(1.0f, 1.0f, 0.0f);
    float half_of_square = _size_of_square.x/2.f;
    drawCircle(position.x + half_of_square, position.y + half_of_square, half_of_square, 16);
}