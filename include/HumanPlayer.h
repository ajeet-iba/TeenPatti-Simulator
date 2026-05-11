#pragma once
#include "Player.h"

// Concrete derived class representing a human-controlled player.
// Implements takeTurn() via std::cin input.
class HumanPlayer : public Player {
public:
    // Inherits Player's constructor
    HumanPlayer(std::string name, int balance = 1000);

    // Overrides the pure virtual function
    void takeTurn() override;
};
