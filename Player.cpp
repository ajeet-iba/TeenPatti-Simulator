#include "Player.h"
#include <iostream>
using namespace std;

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
    std::cout << "\n" << name << "'s Hand:\n";
    std::cout << "-------------------\n";
    for (int i = 0; i < (int)hand.size(); i++) {
        std::cout << "[" << i + 1 << "] "
                  << hand[i].toString() << "\n";
    }
    std::cout << "-------------------\n";
}

void Player::fold() {
    isFolded = true;
    std::cout << name << " folded.\n";
}

void Player::bet(int amount) {
    if (amount <= balance) {
        balance -= amount;
        std::cout << name << " bets $" << amount << "\n";
    } else {
        std::cout << name << " doesn't have enough chips.\n";
    }
}

void Player::seeCards() {
    isSeen = true;
    std::cout << name << " has seen their cards.\n";
}

std::string Player::getName() const {
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