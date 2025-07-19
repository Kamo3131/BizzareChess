#pragma once
#include <string>

struct Piece{
    Piece();
    Piece(std::string name, const int damage);
    Piece(std::string name, const int damage, const int health);
    virtual ~Piece(); 
    virtual bool move(const int horizontal, const int vertical) = 0;
    virtual bool attack(const int horizontal, const int vertical) = 0;
    std::string getName() const;
    int getHealth() const;
    int getMoveNumber() const;
    int getDamage() const;
    void setName(const std::string name);
    void setHealth(const int health);
    void setDamage(const int damage);
    void increaseMoveNumber();
    private:
    std::string _name;
    int _move_number = 0; // Tracks the number of moves made by the piece
    /**
     * I don't know if it will be used.
     */
    int _damage; // Default damage value, can be overridden by derived classes
    int _health;
    
};