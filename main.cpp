#include <iostream>
#include "Deck.h"

int main() {
    // 1. Create a fresh 52-card deck
    Deck deck;
    std::cout << "Deck created. Cards remaining: " << deck.remaining() << "\n\n";

    // 2. Shuffle the deck
    deck.shuffle();
    std::cout << "Deck shuffled.\n\n";

    // 3. Deal 3 cards (one Teen Patti hand) and print each
    std::cout << "Dealing 3 cards:\n";
    std::cout << "-------------------------\n";
    for (int i = 1; i <= 3; ++i) {
        Card c = deck.deal();
        std::cout << "  Card " << i << ": " << c.toString() << "\n";
    }
    std::cout << "-------------------------\n";
    std::cout << "\nCards remaining in deck: " << deck.remaining() << "\n";

    return 0;
}