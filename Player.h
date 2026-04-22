#pragma once
#include <string>
#include <vector>
#include "Card.h"

// Abstract Base Class for all player types.
// Cannot be instantiated directly due to the pure virtual function.
class Player {
protected:
    std::string name;
    int balance;
    std::vector<Card> hand;
    bool isFolded;

public:
    // Constructor
    Player(std::string name, int balance = 1000);

    // Virtual destructor — essential for any class used as a base class
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

    // --- Pure Virtual Function ---
    // Every derived class MUST implement this, making Player abstract
    virtual void takeTurn() = 0;
};