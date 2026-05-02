#include <iostream>
#include "GameEngine.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

int main() {
    std::cout << "===========================\n";
    std::cout << "   TEEN PATTI SIMULATOR    \n";
    std::cout << "===========================\n\n";

    // -------------------------
    // 1. CREATE GAME ENGINE
    // -------------------------
    GameEngine game;

    // -------------------------
    // 2. CREATE PLAYERS
    // -------------------------
    Player* human = new HumanPlayer("Ali");
    Player* ai    = new AIPlayer("Bot-1");

    game.addPlayer(human);
    game.addPlayer(ai);

    // -------------------------
    // 3. START ROUND
    // -------------------------
    game.startRound();

    // -------------------------
    // 4. DEAL CARDS
    // -------------------------
    game.dealCards();

    std::cout << "\n===== PLAYER HANDS =====\n";
    human->printHand();
    ai->printHand();

    // -------------------------
    // 5. PLAY TURNS
    // -------------------------
    game.playTurns();

    // -------------------------
    // 6. DETERMINE WINNER
    // (uses HandEvaluator inside GameEngine)
    // -------------------------
    Player* winner = game.determineWinner();

    // -------------------------
    // 7. AWARD WINNER
    // -------------------------
    game.awardWinner(winner);

    // -------------------------
    // 8. RESET ROUND
    // -------------------------
    game.resetRound();

    // -------------------------
    // 9. CLEANUP MEMORY
    // -------------------------
    delete human;
    delete ai;

    std::cout << "\n===========================\n";
    std::cout << "       GAME OVER           \n";
    std::cout << "===========================\n";

    return 0;
}
