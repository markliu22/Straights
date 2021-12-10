#ifndef GAME_H
#define GAME_H
#include "card.h"
#include <memory>
#include <vector>

class Player;
class Display;

class Game {
protected:
	unsigned seed;
	std::vector<std::shared_ptr<Player>> players;
	std::vector<Card> deck;
	std::vector<Card> table;
	std::shared_ptr<Display> dist;
	bool executeRound(bool loadingMode, std::vector<Card> loadedTable, std::vector<std::vector<Card>> loadedHands, std::vector<std::vector<Card>> loadedDiscards, std::vector<int> loadedScores, int loadedStartingPlayerId);
	int getStartPlayerId();
	bool ranOutOfCards();
	virtual std::vector<Card> getLegalPlays(std::shared_ptr<Player> p) = 0;
	virtual void handleAction(char action, Card c, std::vector<Card> legalPlays, int id, bool &playedOrDiscarded) = 0;
public:
	Game(unsigned seed);
	void executeGame(bool changeStrat, bool loadingMode, std::vector<Card> loadedTable, std::vector<std::vector<Card>> loadedHands, std::vector<std::vector<Card>> loadedDiscards, std::vector<int> loadedScores, int loadedStartingPlayerId);
};

#endif
