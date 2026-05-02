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
    bool isSeen;          // Blind / Seen system later

public:
    // Constructor
    Player(string n, int b = 1000)
        : name(n), balance(b), isFolded(false), isSeen(false) {}

    // Virtual destructor
    virtual ~Player() {}

    // Pure virtual function (Polymorphism)
    virtual void takeTurn() = 0;

    // Add card to hand
    void addCard(const Card& c) {
        if (hand.size() < 3) {
            hand.push_back(c);
        }
    }

    // Clear hand for new round
    void clearHand() {
        hand.clear();
        isFolded = false;
        isSeen = false;
    }

    // Display cards
    void printHand() const {
        cout << "\n" << name << "'s Hand:\n";
        cout << "-------------------\n";

        for (int i = 0; i < hand.size(); i++) {
            cout << "[" << i + 1 << "] "
                 << hand[i].toString() << endl;
        }

        cout << "-------------------\n";
    }

    // Get hand vector
    vector<Card> getHand() const {
        return hand;
    }

    // Fold logic
    void fold() {
        isFolded = true;
        cout << name << " folded.\n";
    }

    // Betting
    void bet(int amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << name << " bets $" << amount << endl;
        }
        else {
            cout << name << " doesn't have enough chips.\n";
        }
    }

    // See cards
    void seeCards() {
        isSeen = true;
        cout << name << " has seen their cards.\n";
    }

    // Getters
    string getName() const {
        return name;
    }

    int getBalance() const {
        return balance;
    }

    bool getIsFolded() const {
        return isFolded;
    }

    bool getIsSeen() const {
        return isSeen;
    }

    // Add chips when winning
    void addBalance(int amount) {
        balance += amount;
    }

    // Hand ranking helper
    int getHighestCard() const {
        int highest = 0;

        for (const Card& c : hand) {
            if (c.getRank() > highest)
                highest = c.getRank();
        }

        return highest;
    }
};
