#include "AIPlayer.h"
#include <iostream>

AIPlayer::AIPlayer(std::string name, int balance)
    : Player(name, balance) {}

void AIPlayer::takeTurn() {
    if (isFolded) {
        std::cout << name << " has already folded. Skipping turn.\n";
        return;
    }

    std::cout << "\n=============================\n";
    std::cout << "  " << name << "'s Turn  (AI)  |  Balance: $" << balance << "\n";
    std::cout << "=============================\n";
    std::cout << "[AI] " << name << " studies their cards...\n";
    std::cout << "[AI] " << name << " chooses to Bet!\n";
}