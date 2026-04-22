#pragma once
#include <string>

// Enum for the four suits in a standard deck
enum class Suit {
    Spades,
    Hearts,
    Diamonds,
    Clubs
};

class Card {
private:
    int rank;   // 2-14, where 11=Jack, 12=Queen, 13=King, 14=Ace
    Suit suit;

public:
    // Constructor
    Card(int rank, Suit suit);

    // Getters
    int getRank() const;
    Suit getSuit() const;

    // Returns a human-readable string e.g. "Ace of Spades"
    std::string toString() const;
};