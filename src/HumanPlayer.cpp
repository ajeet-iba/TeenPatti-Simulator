#include "HumanPlayer.h"
#include <iostream>
#include <limits>

HumanPlayer::HumanPlayer(std::string name, int balance)  // ✅ No return type
    : Player(name, balance) {}

void HumanPlayer::takeTurn() {
    if (isFolded) {
        std::cout << name << " has already folded. Skipping turn.\n";
        return;
    }

    std::cout << "\n=============================\n";
    std::cout << "  " << name << "'s Turn  |  Balance: $" << balance << "\n";
    std::cout << "=============================\n";
    printHand();
    std::cout << "-----------------------------\n";
    std::cout << "  1 - Bet\n";
    std::cout << "  2 - Fold\n";
    std::cout << "-----------------------------\n";
    std::cout << "Your choice: ";

    int choice = 0;
    while (true) {
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter 1 or 2: ";
            continue;
        }

        if (choice == 1) {
            std::cout << name << " chooses to Bet!\n";
            break;
        } else if (choice == 2) {
            fold();
            break;
        } else {
            std::cout << "Invalid choice. Please enter 1 or 2: ";
        }
    }
}
