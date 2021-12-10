#include "player.h"
#include "card.h"
using namespace std;

Player::Player(int id, vector<Card> hand) : id{id}, hand{hand} {
	newScore = 0;
	score = 0;
};
