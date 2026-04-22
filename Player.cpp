#include "Player.h"
#include <iostream>

Player::Player(std::string name, int balance)
    : name(name), balance(balance), isFolded(false) {}

void Player::addCard(Card c) {
    hand.push_back(c);
}

void Player::printHand() const {
    std::cout << name << "'s hand:\n";
    for (int i = 0; i < (int)hand.size(); ++i) {
        std::cout << "  [" << (i + 1) << "] " << hand[i].toString() << "\n";
    }
}

void Player::fold() {
    isFolded = true;
    std::cout << name << " has folded.\n";
}

std::string Player::getName() const { return name; }
int Player::getBalance() const     { return balance; }
bool Player::getIsFolded() const   { return isFolded; }