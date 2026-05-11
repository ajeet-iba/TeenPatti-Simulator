#pragma once
#include <vector>
#include "Deck.h"
#include "Player.h"

class GameEngine {
private:
    Deck deck;
    std::vector<Player*> players;
    int pot;

public:
    GameEngine();

    void addPlayer(Player* p);

    void startRound();
    void dealCards();
    void playTurns();

    Player* determineWinner();
    void awardWinner(Player* winner);

    void resetRound();
};
