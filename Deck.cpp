#include "Deck.h"
#include <algorithm>   // std::shuffle
#include <random>      // std::mt19937, std::random_device
#include <stdexcept>   // std::runtime_error

Deck::Deck() {
    // All four suits
    Suit suits[] = { Suit::Spades, Suit::Hearts, Suit::Diamonds, Suit::Clubs };

    // Ranks 2 through 14 (14 = Ace)
    for (Suit s : suits) {
        for (int rank = 2; rank <= 14; ++rank) {
            cards.push_back(Card(rank, s));
        }
    }
    // Deck now contains exactly 52 cards in sorted order
}

void Deck::shuffle() {
    // std::random_device seeds the Mersenne Twister with true hardware entropy
    std::random_device rd;
    std::mt19937 rng(rd());

    // std::shuffle performs a Fisher-Yates shuffle — guaranteed uniform distribution
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card Deck::deal() {
    if (cards.empty()) {
        throw std::runtime_error("Cannot deal from an empty deck.");
    }

    // Treat the back of the vector as the "top" of the deck
    Card topCard = cards.back();
    cards.pop_back();   // O(1) removal from the back
    return topCard;
}

int Deck::remaining() const {
    return static_cast<int>(cards.size());
}