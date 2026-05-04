#pragma once
#include "Player.h"

class AIPlayer : public Player {
public:
    AIPlayer(std::string name, int balance = 1000);
    void takeTurn() override;
};