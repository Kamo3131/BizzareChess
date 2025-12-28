#include "Game3D.hpp"
#include "Chessboard3D.hpp"
#include <string>
#include <sstream>
#include <regex>

Game3D::Game3D() : _turn{1}, _zoom{0.850f}, _chessBoard{8, 8}{
    _chessBoard.initPieces();
}

Game3D::Game3D(const size horizontal, const size vertical) : _turn{1}, _zoom{0.850f}, _chessBoard{horizontal, vertical}{
    _chessBoard.initPieces();
}
Game3D::Game3D(const int turn, ChessBoard&& chessBoard) : _turn{turn}, _zoom{0.850f}, _chessBoard{std::move(chessBoard)}{
    
}
bool Game3D::surrender(){
    return true;
}

void Game3D::enPassantTurnCycle(){
    if(_turn % 2 == 0){
        _chessBoard.enPassantTurnUpdate(Piece::Team::BLACK);
    } else{
        _chessBoard.enPassantTurnUpdate(Piece::Team::WHITE);
    }
}

bool Game3D::quitGame(){
    return true;
}
void Game3D::restart(){
    

}

void Game3D::movePiece(){

}
void Game3D::initOpengl() const{
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
}
void Game3D::setupCamera() const{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    gluPerspective(45.0, static_cast<double>(viewport[2]) / static_cast<double>(viewport[3]), 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10.0/_zoom, 10.0/_zoom, 10.0/_zoom,
                2.0,  -2.0,  2.0,  
                0.0,  1.0,  0.0);
}

void Game3D::updatePossibleMoves(){
    _possibleMoves.clear();
    if(!_selectedSquare){
        return;
    }
    std::size_t width = _chessBoard.getHorizontal();
    std::size_t height = _chessBoard.getVertical();
    if((_selectedSquare->x < 0 || _selectedSquare->x >= width) 
    && (_selectedSquare->y < 0 || _selectedSquare->y >= height)){
        return;
    }

    for(int i = width - 1; i > -1; i--){
        for(int j = height - 1; j > -1; j--){
            float move_x = static_cast<float>(i) - _selectedSquare->x;
            float move_y = static_cast<float>(j) - _selectedSquare->y; 
            // std::cout << move_x << " " << move_y << std::endl;
            if(0 == move_x && 0 == move_y) continue;
            if(_chessBoard.canMove(static_cast<size_t>(_selectedSquare->x), static_cast<size_t>(_selectedSquare->y), move_x, move_y)){
                _possibleMoves.emplace_back(i, j);
            }
        }
    }
}
void Game3D::gameLoop(){
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 2;
    settings.minorVersion = 0;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Chess Project - OpenGL 2.0", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    if (!ImGui::SFML::Init(window)) return;
    sf::Clock deltaClock;
    Chessboard3D chess3D(sf::Vector2f(1.0f, 1.0f));
    int horizontal = _chessBoard.getHorizontal();
    int vertical = _chessBoard.getVertical();
    initOpengl();
    bool isCheckmate = false, isStalemate = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) window.close();
            
            if (event.type == sf::Event::Resized) {
                glViewport(0, 0, event.size.width, event.size.height);
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                handleMouseClick(chess3D, event.mouseButton.x, event.mouseButton.y);
            }
        }
        if (_selectedSquare) {
            if (_selectedSquare->x < 0 ||
                _selectedSquare->y < 0 ||
                _selectedSquare->x >= _chessBoard.getHorizontal() ||
                _selectedSquare->y >= _chessBoard.getVertical() ||
                !_chessBoard.getPiece(_selectedSquare->x,
                                    _selectedSquare->y)) {
                _selectedSquare.reset();
                _possibleMoves.clear();
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        setupCamera();
        for(int i = horizontal - 1; i > -1; i--){
            for(int j = vertical - 1; j > -1; j--){
                if(i%2 == j%2){
                    chess3D.drawSquareTile(Piece::Team::BLACK, sf::Vector2f(i * chess3D.getSize().x, j * chess3D.getSize().y));
                } else {
                    chess3D.drawSquareTile(Piece::Team::WHITE, sf::Vector2f(i * chess3D.getSize().x, j * chess3D.getSize().y));
                }
                if(0 == i){
                    chess3D.drawChessboardWall(sf::Vector2f(i * chess3D.getSize().x, j * chess3D.getSize().y), Chessboard3D::Direction::WEST);
                }
                if((horizontal-1) == i){
                    chess3D.drawChessboardWall(sf::Vector2f(i * chess3D.getSize().x, j * chess3D.getSize().y), Chessboard3D::Direction::EAST);
                }
                if(0 == j) {
                    chess3D.drawChessboardWall(sf::Vector2f(i * chess3D.getSize().x, j * chess3D.getSize().y), Chessboard3D::Direction::NORTH);
                }
                if((vertical-1) == j){
                    chess3D.drawChessboardWall(sf::Vector2f(i * chess3D.getSize().x, j * chess3D.getSize().y), Chessboard3D::Direction::SOUTH); 
                }
                if(_chessBoard.getPiece(static_cast<size_t>(i), static_cast<size_t>(j))){
                    std::unique_ptr<Piece> &piece = _chessBoard.getPiece(static_cast<size_t>(i), static_cast<size_t>(j));
                    chess3D.drawPiece(piece->getType(), piece->getTeam(), sf::Vector2i(i * static_cast<int>(chess3D.getSize().x),
                    j * static_cast<int>(chess3D.getSize().y)));
                    if(_selectedSquare && i == _selectedSquare->x && j == _selectedSquare->y){
                        chess3D.highlightSelectedPiece(sf::Vector2f(i * chess3D.getSize().x, j * chess3D.getSize().y));
                    }

                } else {
                    continue;
                }

            }
        }
        glDisable(GL_LIGHTING);
        if(_selectedSquare){
            for(const sf::Vector2i& move : _possibleMoves){
                chess3D.highlightPossibleSquare(sf::Vector2f(move.x * chess3D.getSize().x, move.y * chess3D.getSize().y));
            }
        }
        if(_selectedSquare && _chessBoard.getPiece(_selectedSquare->x, _selectedSquare->y)){
            for(int i = horizontal - 1; i > -1; i--){
                for(int j = vertical - 1; j > -1; j--){
                    float move_x = i - _selectedSquare->x;
                    float move_y = j - _selectedSquare->y; 
                    // std::cout << move_x << " " << move_y << std::endl;
                    if((_selectedSquare->x + move_x >= horizontal) || (_selectedSquare->x + move_x < 0)){
                        std::cout << "Cannot move out of bonds!\n";
                        continue;
                    }
                    if((_selectedSquare->y + move_y >= vertical) || (_selectedSquare->y + move_y < 0)){
                        std::cout << "Cannot move out of bonds!\n";
                        continue;
                    }
                    if(_chessBoard.canMove(_selectedSquare->x, _selectedSquare->y, move_x, move_y)){
                        chess3D.highlightPossibleSquare(sf::Vector2f(i * chess3D.getSize().x, j * chess3D.getSize().y));
                    }
                }
            }
        }
        glEnable(GL_LIGHTING);


        ImGui::Begin("Debug Menu");
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
            ImGui::SliderFloat("Zoom", &_zoom, 0.5f, 4.0f);

            if(ImGui::Button("Quit")){
                if(quitGame()){
                    return;
                }
            }
            if(ImGui::Button("Surrender")){
                if(surrender()){
                    return;
                }
            }
            if(ImGui::Button("Restart")){
                if(surrender()){
                    return;
                }
            }
        ImGui::End();
        ImGui::Begin("Game Status");
        ImGui::SeparatorText("Selection");
        if (_selectedSquare->x >= 0 && _selectedSquare->x < 8 && _selectedSquare->y >= 0 && _selectedSquare->y < 8) {
            ImGui::Text("Square: (%d, %d)", _selectedSquare->x, _selectedSquare->y);
            std::unique_ptr<Piece>& piece = _chessBoard.getPiece(_selectedSquare->x, _selectedSquare->y);
            if (piece) {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "[%s]", piece->getName().c_str());
            } else {
                ImGui::SameLine();
                ImGui::TextDisabled("[Empty]");
            }
        } else {
            ImGui::TextDisabled("No square selected");
        }

        // --- 2. King Status Section ---
        ImGui::Spacing();
        ImGui::SeparatorText("King Status");

        // Helper lambda to draw status text
        auto DrawKingStatus = [&](const char* label, Piece::Team team, std::pair<int, int> kingPos) {
            isCheckmate = _chessBoard.inCheckmate(team);
            bool isCheck = false;
                        
            ImGui::Text("%s:", label);
            ImGui::SameLine();
            if(!isCheckmate){
                isStalemate = _chessBoard.inStalemate(team);
            } else {
                ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "CHECKMATED!");
                return; 
            }
            if(!isStalemate){
                isCheck = _chessBoard.inCheck(team, kingPos);
            } else {
                ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.2f, 1.0f), "IT'S A STALEMATE!");
                return; 
            }
            
            if (isCheck) {
                ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.2f, 1.0f), "IN CHECK!");
                return; 
            } else {
                ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Safe");
                return;
            }
        };
        std::pair<int, int> wPos = _chessBoard.getWhiteKingsPosition();
        DrawKingStatus("White King", Piece::Team::WHITE, wPos);
        std::pair<int, int> bPos = _chessBoard.getBlackKingsPosition();
        DrawKingStatus("Black King", Piece::Team::BLACK, bPos);

        ImGui::End();

        window.pushGLStates();
        ImGui::SFML::Render(window);
        window.popGLStates();

        window.display();
    }

    ImGui::SFML::Shutdown();
}
void Game3D::nextTurn(){
    _turn++;
}
void Game3D::previousTurn(){
    _turn--;
}
int Game3D::getTurn() const {
    return _turn;
}
const ChessBoard& Game3D::getChessBoard() const {
    return _chessBoard;
}

void Game3D::handleMouseClick(const Chessboard3D chess3D, int mouseX, int mouseY){
    setupCamera();
    _raySelection.screenToWorld(mouseX, mouseY);
    if( !_raySelection.intersectBoard()){
        return;
    }
    std::optional<sf::Vector2i> square = _raySelection.worldToBoardSquare(chess3D, 
        _chessBoard.getHorizontal(), _chessBoard.getVertical());

    if(!square){
        std::cout << "No square selected!\n";
        return; 
    }
    std::unique_ptr<Piece>& targetPiece = _chessBoard.getPiece(square->x, square->y);

    bool isFriendly = targetPiece && ((targetPiece->getTeam() == Piece::Team::WHITE && getTurn() % 2 == 1) || (targetPiece->getTeam() == Piece::Team::BLACK && getTurn() % 2 == 0));
    if(!_selectedSquare || isFriendly){
        if(isFriendly){
            std::cout << "Square with piece (" << square->x << ", " << square->y << ") selected!\n"; 
            _selectedSquare = square;
            updatePossibleMoves();
            std::cout << "Possible moves updated!" << std::endl;
        }
        return;
    }
    else {
        sf::Vector2i moveVector = sf::Vector2i(square->x - _selectedSquare->x, square->y - _selectedSquare->y);
        std::unique_ptr<Piece>& piece = _chessBoard.getPiece(_selectedSquare->x, _selectedSquare->y);
        std::cout << "Square (" << square->x << ", " << square->y << ") selected!\n"; 
        if(piece){

            if(_chessBoard.canMove(_selectedSquare->x, _selectedSquare->y, moveVector.x, moveVector.y)){
                std::cout << "Piece can move!\n";
                enPassantTurnCycle();
                _chessBoard.move(_selectedSquare->x, _selectedSquare->y, moveVector.x, moveVector.y);
                nextTurn();
                _selectedSquare.reset();
                _possibleMoves.clear();
            } else {
                std::cout << "Piece can't move to this square!\n";
                _selectedSquare.reset();
                _possibleMoves.clear();
            }
        }
        return;
    }
}