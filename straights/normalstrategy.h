#ifndef NORMAL_STRATEGY_H
#define NORMAL_STRATEGY_H
#include "strategy.h"

class NormalStrategy : public Strategy {
public:
        virtual std::pair<char, Card> executeStrategy(std::vector<Card> legalPlays, std::vector<Card> hand) override;
};

#endif
