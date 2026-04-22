#pragma once
#include "Player.h"

// Concrete derived class representing a computer-controlled player.
// Phase 1: Uses simple hardcoded logic. Will be expanded in later phases.
class AIPlayer : public Player {
public:
    AIPlayer(std::string name, int balance = 1000);

    // Overrides the pure virtual function
    void takeTurn() override;
};