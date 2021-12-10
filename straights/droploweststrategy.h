#ifndef DROPLOWEST_STRATEGY_H
#define DROPLOWEST_STRATEGY_H
#include "strategy.h"

class DropLowestStrategy : public Strategy {
public:
        virtual std::pair<char, Card> executeStrategy(std::vector<Card> legalPlays, std::vector<Card> hand) override;
};

#endif
