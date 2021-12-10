#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>

class Card;

class Player {
public:
	int id;
	int newScore;
	int score;
	std::vector<Card> hand;
	std::vector<Card> discards;
	Player(int id, std::vector<Card> hand);
	virtual std::pair<char, Card> getAction(std::vector<Card> legalPlays) = 0;
};

#endif

