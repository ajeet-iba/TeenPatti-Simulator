#pragma once
#include <vector>
#include "Card.h"

class HandEvaluator {
public:
    static int evaluate(const std::vector<Card>& hand);
    static std::string handName(int rank);
};