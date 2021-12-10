#include "normalstrategy.h"
#include "card.h"
using namespace std;

pair<char, Card> NormalStrategy::executeStrategy(vector<Card> legalPlays, vector<Card> hand) {
        if(legalPlays.size() > 0) {
                return {'p', legalPlays[0]};
        }
        return {'d', hand[0]};
}
