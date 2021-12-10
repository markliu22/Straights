#include "humanplayer.h"
#include "card.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

HumanPlayer::HumanPlayer(int id, vector<Card> hand) : Player(id, hand) {}

pair<char, Card> HumanPlayer::getAction(vector<Card> legalPlays) {
	Card c{'0', '0'};
	string action = "";
	while(true) {
		getline(cin, action);
		if(action.size() > 0) break;
	}
	string tmp = "";
	stringstream ss(action);
	vector<string> splits;
	while(ss >> tmp) {
		splits.push_back(tmp);
	}
	// must return action that is one of:
	// p=play, d=discard, k=deck, q=quit, r=ragequit, o=other/invalid 
	if(splits[0] == "play") {
		if(splits.size() != 2) return {'i', c};
		Card chosen{splits[1].at(0), splits[1].at(1)};
		return {'p', chosen};
	} else if(splits[0] == "discard") {
		if(splits.size() != 2) return {'i', c};
		Card chosen{splits[1].at(0), splits[1].at(1)};
		return {'d', chosen};
	} else if(splits[0] == "deck") {
		return {'k', c};
	} else if(splits[0] == "quit") {
		return {'q', c};
	} else if(splits[0] == "ragequit") {
		return {'r', c};
	} else {
		return {'i', c};
	}
}
