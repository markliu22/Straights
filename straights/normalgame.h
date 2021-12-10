#ifndef NORMAL_GAME_H
#define NORMAL_GAME_H
#include "game.h"
#include <memory>
#include <vector>

class Card;
class Player;

class NormalGame : public Game {
	std::vector<Card> getLegalPlays(std::shared_ptr<Player> p) override;
	virtual void handleAction(char action, Card c, std::vector<Card> legalPlays, int id, bool &playedOrDiscarded) override;
public:
	NormalGame(unsigned seed);
};

#endif
