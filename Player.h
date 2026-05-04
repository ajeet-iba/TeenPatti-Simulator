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

public:
    // Constructor
    Player(std::string name, int balance = 1000);

    // Virtual destructor
    virtual ~Player() = default;

    // --- Card / Hand Management ---
    void addCard(Card c);
    void printHand() const;

    // --- Game Actions ---
    void fold();

    // --- Getters ---
    std::string getName() const;
    int getBalance() const;
    bool getIsFolded() const;

    // --- Returns reference to hand (fixed) ---
    std::vector<Card>& getHand() { return hand; }

    // --- Pure Virtual Function ---
    virtual void takeTurn() = 0;
};