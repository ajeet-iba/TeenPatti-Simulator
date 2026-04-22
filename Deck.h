#pragma once
#include <vector>
#include "Card.h"

class Deck {
private:
    std::vector<Card> cards;  // Stores all 52 cards

public:
    // Constructor: populates the deck with all 52 cards
    Deck();

    // Shuffles the deck using a Mersenne Twister RNG
    void shuffle();

    // Deals the "top" card (back of vector) and removes it
    // Throws std::runtime_error if the deck is empty
    Card deal();

    // Utility: how many cards remain?
    int remaining() const;
};