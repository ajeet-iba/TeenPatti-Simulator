#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Card.h"

using namespace std;

class Player {
protected:
    string name;
    int balance;
    vector<Card> hand;
    bool isFolded;
    bool isSeen;

public:
    // Constructor
    Player(string n, int b = 1000);

    // Virtual destructor
    virtual ~Player();

    // Pure virtual function
    virtual void takeTurn() = 0;

    // Card functions
    void addCard(const Card& c);
    void clearHand();
    void printHand() const;
    vector<Card> getHand() const;

    // Game actions
    void fold();
    void bet(int amount);
    void seeCards();

    // Getters
    string getName() const;
    int getBalance() const;
    bool getIsFolded() const;
    bool getIsSeen() const;

    // Money
    void addBalance(int amount);

    // Hand helper
    int getHighestCard() const;
};
