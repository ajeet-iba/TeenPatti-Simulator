#include "Card.h"

Card::Card(int rank, Suit suit) : rank(rank), suit(suit) {}

int Card::getRank() const {
    return rank;
}

Suit Card::getSuit() const {
    return suit;
}

std::string Card::toString() const {
    // --- Rank to string ---
    std::string rankStr;
    switch (rank) {
        case 11: rankStr = "Jack";  break;
        case 12: rankStr = "Queen"; break;
        case 13: rankStr = "King";  break;
        case 14: rankStr = "Ace";   break;
        default: rankStr = std::to_string(rank); break;  // 2-10
    }

    // --- Suit to string ---
    std::string suitStr;
    switch (suit) {
        case Suit::Spades:   suitStr = "Spades";   break;
        case Suit::Hearts:   suitStr = "Hearts";   break;
        case Suit::Diamonds: suitStr = "Diamonds"; break;
        case Suit::Clubs:    suitStr = "Clubs";    break;
    }

    return rankStr + " of " + suitStr;
}