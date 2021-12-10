#include "computerplayer.h"
#include "card.h"
// TODO rm
#include <iostream>
using namespace std;

ComputerPlayer::ComputerPlayer(int id, vector<Card> hand, int strat) : Player(id, hand), strat{strat} {
	cout << "COMPUTERPLAYER CONSRUCTOR: " << strat << endl;
}

pair<char, Card> ComputerPlayer::getAction(vector<Card> legalPlays) {
	// 1 = Normal Strategy (play first legal play in hand, if there are no legal plays, discard first card in hand)
	// 2 = Drop Lowest Strategy (play first legal play in hand, if there are no legal plays, discard card in hand with the lowest rank)
	if(strat == 1) {
		return Nstrat.executeStrategy(legalPlays, hand);
	} else {
		return DLstrat.executeStrategy(legalPlays, hand);
	}
}
