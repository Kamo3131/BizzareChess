#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include "Chessboard3D.hpp"
#include <optional>

class RaySelection {
    public:
    RaySelection();
    void screenToWorld(int mouseX, int mouseY);
    bool intersectBoard();
    std::optional<sf::Vector2i> worldToBoardSquare(const Chessboard3D chess3D, int horizontal, int vertical);
    sf::Vector3f getRayOrigin() const;
    sf::Vector3f getRayDirection() const;
    sf::Vector3f getHitPoint() const;


    private:
    sf::Vector3f _rayOrigin;
    sf::Vector3f _rayDirection;
    sf::Vector3f _hitpoint;
    GLint _viewport[4];
    GLdouble _modelView[16];
    GLdouble _projection[16];
};