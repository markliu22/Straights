#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H 
#include "player.h"
#include "normalstrategy.h"
#include "droploweststrategy.h"

class Card;

class ComputerPlayer: public Player {
NormalStrategy Nstrat;
DropLowestStrategy DLstrat;
int strat;
public:
	ComputerPlayer(int id, std::vector<Card> hand, int strat = 1);
	virtual std::pair<char, Card> getAction(std::vector<Card> legalPlays) override;
};

#endif
 
