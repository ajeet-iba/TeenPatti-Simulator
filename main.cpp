#include <iostream>
#include "Deck.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"

int main() {
    std::cout << "===========================\n";
    std::cout << "   Teen Patti Simulator    \n";
    std::cout << "===========================\n\n";

    // --- 1. Set up the deck ---
    Deck deck;
    deck.shuffle();
    std::cout << "Deck shuffled. Cards remaining: " << deck.remaining() << "\n\n";

    // --- 2. Create players ---
    // Player* allows polymorphism — we can call takeTurn() on both
    // without knowing at compile time whether it's Human or AI
    Player* human = new HumanPlayer("Ali");
    Player* ai    = new AIPlayer("Bot-1");

    // --- 3. Deal 3 cards each (standard Teen Patti hand) ---
    std::cout << "Dealing cards...\n";
    for (int i = 0; i < 3; ++i) {
        human->addCard(deck.deal());
        ai->addCard(deck.deal());
    }
    std::cout << "Cards remaining in deck: " << deck.remaining() << "\n";

    // --- 4. Take turns (polymorphic dispatch) ---
    // The correct takeTurn() is called automatically based on the real object type
    human->takeTurn();
    ai->takeTurn();

    // --- 5. Clean up heap memory ---
    delete human;
    delete ai;

    std::cout << "\n===========================\n";
    std::cout << "     End of Round 1        \n";
    std::cout << "===========================\n";

    return 0;
}