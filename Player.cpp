#include "Player.h"
#include <iostream>

Player::Player(string n, int b)
    : name(n), balance(b), isFolded(false), isSeen(false) {}

Player::~Player() {}

void Player::addCard(const Card& c) {
    if (hand.size() < 3) {
        hand.push_back(c);
    }
}

void Player::clearHand() {
    hand.clear();
    isFolded = false;
    isSeen = false;
}

void Player::printHand() const {
    cout << "\n" << name << "'s Hand:\n";
    cout << "-------------------\n";

    for (int i = 0; i < hand.size(); i++) {
        cout << "[" << i + 1 << "] "
             << hand[i].toString() << endl;
    }

    cout << "-------------------\n";
}

vector<Card> Player::getHand() const {
    return hand;
}

void Player::fold() {
    isFolded = true;
    cout << name << " folded.\n";
}

void Player::bet(int amount) {
    if (amount <= balance) {
        balance -= amount;
        cout << name << " bets $" << amount << endl;
    }
    else {
        cout << name << " doesn't have enough chips.\n";
    }
}

void Player::seeCards() {
    isSeen = true;
    cout << name << " has seen their cards.\n";
}

string Player::getName() const {
    return name;
}

int Player::getBalance() const {
    return balance;
}

bool Player::getIsFolded() const {
    return isFolded;
}

bool Player::getIsSeen() const {
    return isSeen;
}

void Player::addBalance(int amount) {
    balance += amount;
}

int Player::getHighestCard() const {
    int highest = 0;

    for (const Card& c : hand) {
        if (c.getRank() > highest) {
            highest = c.getRank();
        }
    }

    return highest;
}
