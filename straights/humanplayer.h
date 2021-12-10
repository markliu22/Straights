#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "player.h"

class Card;

class HumanPlayer: public Player {
public:
	HumanPlayer(int id, std::vector<Card> hand);
	virtual std::pair<char, Card> getAction(std::vector<Card> legalPlays) override;
};

#endif

