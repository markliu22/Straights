#include "normalgame.h"
#include "player.h"
#include "humanplayer.h"
#include "computerplayer.h"
#include "card.h"
#include "display.h"
#include "consoledisplay.h"
#include <cmath> 
using namespace std;

vector<Card> NormalGame::getLegalPlays(shared_ptr<Player> p) {
	vector<Card> legalPlays;
	Card startCard{'7', 'S'};

	for(Card &h : p->hand) {
		if(h == startCard) {
			legalPlays.clear();
			legalPlays.push_back(startCard);
			return legalPlays;
		} else if(h.rank == '7') {
			legalPlays.push_back(h);
		} else {
			for(Card &t : table) {
				if(h.suite == t.suite && abs(h.getNumberRank() - t.getNumberRank()) == 1) {
					legalPlays.push_back(h);
				}
			}
		}
	}
	return legalPlays;
}


NormalGame::NormalGame(unsigned seed) : Game(seed) {};


void NormalGame::handleAction(char action, Card c, vector<Card> legalPlays, int id, bool &playedOrDiscarded) {
	shared_ptr<Player> replacement;
	switch(action) {
		case 'p': {
				  // if card is in player's hand: proceed with play
				  if(find(legalPlays.begin(), legalPlays.end(), c) != legalPlays.end()) {
					  // add to table
					  table.push_back(c);
					  // remove from hand
					  players[id - 1]->hand.erase(remove(players[id - 1]->hand.begin(), players[id - 1]->hand.end(), c), players[id - 1]->hand.end());
					  dist->displayPlayCard(id, c);
					  playedOrDiscarded = true; // can move to next player
				  } else {
					  dist->displayPlayNotLegal();
				  }
			  }
			  break;
		case 'd': {
				  // if card is in player's hand and they have no legal plays: proceed with discard
				  if(legalPlays.size() == 0 && find(players[id - 1]->hand.begin(), players[id - 1]->hand.end(), c) != players[id - 1]->hand.end()) {
					  // add to play discards
					  players[id - 1]->discards.push_back(c);
					  // remove from hand
					  players[id - 1]->hand.erase(remove(players[id - 1]->hand.begin(), players[id - 1]->hand.end(), c), players[id - 1]->hand.end());
					  players[id - 1]->newScore += c.getNumberRank();
					  dist->displayDiscardCard(id, c);
					  playedOrDiscarded = true; // can move to next player
				  } 
				  // if player tries discarding a card they don't have
				  else if(find(players[id - 1]->hand.begin(), players[id - 1]->hand.end(), c) == players[id - 1]->hand.end()) {
					  dist->displayDiscardNotLegal();
				  } 
				  // if player tries discarding a card when they have legal moves
				  else {
					  dist->displayDiscardWithLegalPlays();
				  }
			  }
			  break;
		case 'k': {
				  dist->displayDeck(deck);
			  }
			  break;
		case 'r': {
				  // TODO: should call copy constructor/copy assignment operator here?
				  replacement = make_shared<ComputerPlayer>(id, players[id - 1]->hand);
				  // replacement->oldScore = players[id - 1]->oldScore;
				  replacement->newScore = players[id - 1]->newScore;
				  replacement->score = players[id - 1]->score;
				  replacement->discards = players[id - 1]->discards;
				  players[id - 1] = replacement;
				  dist->displayRageQuit(id);
			  } 
			  break;
		case 'i': {
				  dist->displayInvalidMsg();
			  }
			  break;
	}
}
