#include "droploweststrategy.h"
#include "card.h"
using namespace std;

pair<char, Card> DropLowestStrategy::executeStrategy(vector<Card> legalPlays, vector<Card> hand) {
        if(legalPlays.size() > 0) {
                return {'p', legalPlays[0]};
        }

	int idx = 0;
	int minRank = hand[idx].getNumberRank();
	for(size_t i = 0; i < hand.size(); ++i) {
		if(hand[i].getNumberRank() < minRank) {
			idx = i;
			minRank = hand[idx].getNumberRank();
		}
	}
	return {'d', hand[idx]};
}
