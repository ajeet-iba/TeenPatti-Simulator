#pragma once
#include <string>
#include <vector>
#include "Card.h"

class Player {
protected:
    std::string name;
    int balance;
    std::vector<Card> hand;
    bool isFolded;
    bool isSeen;        // ← added, was missing

public:
    // Constructor
    Player(std::string name, int balance = 1000);

    // Destructor
    virtual ~Player();

    // --- Card / Hand Management ---
    void addCard(const Card& c);    // ← fixed to const ref
    void clearHand();               // ← added, was missing
    void printHand() const;

    // --- Game Actions ---
    void fold();
    void bet(int amount);           // ← added, was missing
    void seeCards();                // ← added, was missing

    // --- Getters ---
    std::string getName() const;
    int getBalance() const;
    bool getIsFolded() const;
    bool getIsSeen() const;         // ← added, was missing
    int getHighestCard() const;     // ← added, was missing

    // --- Balance ---
    void addBalance(int amount);    // ← added, was missing

    // --- Hand reference for GUI ---
    std::vector<Card>& getHand() { return hand; }

    // --- Pure Virtual Function ---
    virtual void takeTurn() = 0;
};
