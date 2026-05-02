#include "HandEvaluator.h"
#include <algorithm>

int HandEvaluator::evaluate(const std::vector<Card>& hand) {
    std::vector<int> ranks;
    std::vector<Suit> suits;

    for (const Card& c : hand) {
        ranks.push_back(c.getRank());
        suits.push_back(c.getSuit());
    }

    std::sort(ranks.begin(), ranks.end());

    bool sameSuit =
        suits[0] == suits[1] &&
        suits[1] == suits[2];

    bool sequence =
        ranks[1] == ranks[0] + 1 &&
        ranks[2] == ranks[1] + 1;

    bool trail =
        ranks[0] == ranks[1] &&
        ranks[1] == ranks[2];

    bool pair =
        ranks[0] == ranks[1] ||
        ranks[1] == ranks[2] ||
        ranks[0] == ranks[2];

    if (trail) return 6;
    if (sequence && sameSuit) return 5;
    if (sequence) return 4;
    if (sameSuit) return 3;
    if (pair) return 2;
    return 1;
}

std::string HandEvaluator::handName(int rank) {
    switch(rank) {
        case 6: return "Trail";
        case 5: return "Pure Sequence";
        case 4: return "Sequence";
        case 3: return "Color";
        case 2: return "Pair";
        default: return "High Card";
    }
}