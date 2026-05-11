#include "GameEngine.h"
#include "HandEvaluator.h"
#include <iostream>

using namespace std;

GameEngine::GameEngine() {
    pot = 0;
}

void GameEngine::addPlayer(Player* p) {
    players.push_back(p);
}

void GameEngine::startRound() {
    cout << "\n====================================\n";
    cout << "        NEW ROUND STARTED           \n";
    cout << "====================================\n";

    deck = Deck();
    deck.shuffle();
    pot = 0;

    for (Player* p : players) {
        p->clearHand();
    }
}

void GameEngine::dealCards() {
    cout << "\nDealing cards...\n";

    for (int i = 0; i < 3; i++) {
        for (Player* p : players) {
            p->addCard(deck.deal());
        }
    }

    cout << "Cards dealt successfully.\n";
    cout << "Remaining deck: " << deck.remaining() << "\n";
}

void GameEngine::playTurns() {
    cout << "\n========== PLAYER TURNS ==========\n";

    for (Player* p : players) {
        if (!p->getIsFolded()) {

            p->printHand();
            p->takeTurn();

            if (!p->getIsFolded()) {
                p->bet(50);
                pot += 50;
            }
        }
    }
}

Player* GameEngine::determineWinner() {
    Player* winner = nullptr;
    int bestRank = -1;

    cout << "\n========== HAND RESULTS ==========\n";

    for (Player* p : players) {
        if (!p->getIsFolded()) {

            int rank = HandEvaluator::evaluate(p->getHand());

            cout << p->getName()
                 << " → "
                 << HandEvaluator::handName(rank)
                 << endl;

            if (rank > bestRank) {
                bestRank = rank;
                winner = p;
            }
        }
    }

    return winner;
}

void GameEngine::awardWinner(Player* winner) {
    if (winner == nullptr) {
        cout << "\nNo winner (all players folded)\n";
        return;
    }

    winner->addBalance(pot);

    cout << "\n====================================\n";
    cout << " WINNER: " << winner->getName() << "\n";
    cout << " Won Pot: $" << pot << "\n";
    cout << " New Balance: $" << winner->getBalance() << "\n";
    cout << "====================================\n";

    pot = 0;
}

void GameEngine::resetRound() {
    for (Player* p : players) {
        p->clearHand();
    }

    pot = 0;
}
