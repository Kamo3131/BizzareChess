#include <iostream>
#include "ChessBoard.hpp"
#include "GameTerminal.hpp"
#include "Game3D.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/glu.h>
#include "imgui.h"
#include "imgui-SFML.h"
int main(){
    // GameTerminal game;
    // game.gameLoop();
    std::unique_ptr<GameInterface> game = std::make_unique<Game3D>();
    game->gameLoop();
    return 0;
}
