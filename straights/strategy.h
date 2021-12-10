#ifndef STRATEGY_H
#define STRATEGY_H
#include <utility>
#include <vector>

class Card;

class Strategy {
public:
        virtual std::pair<char, Card> executeStrategy(std::vector<Card> legalPlays, std::vector<Card> hand) = 0;
};

#endif
