#include "consoledisplay.h"
#include "card.h"
#include "player.h"
#include <iostream>


using namespace std;

void ConsoleDisplay::displayTypeOfCard(std::vector<Card> vec, char suite) {
	switch(suite) {
		case 'C':
			cout << "Clubs:";
			break;
		case 'D':
			cout << "Diamonds:";
			break;
		case 'H':
			cout << "Hearts:";
			break;
		case 'S':
			cout << "Spades:";
			break;
	}

	for(Card &c : vec) {
		if(c.suite == suite) {
			cout << " " << c.rank;
		}
	}
	cout << endl;
}

void ConsoleDisplay::displayHorCPrompt(int id) {
	cout << "Is Player" << id << " a human (h) or a computer (c)?" << endl;
}

void ConsoleDisplay::displayStratPrompt() {
	cout << "What type of strategy should this Computer Player use?" << endl;
	cout << "1 = Normal Strategy (play first legal play in hand, if there are no legal plays, discard first card in hand)" << endl;
	cout << "2 = Drop Lowest Strategy (play first legal play in hand, if there are no legal plays, discard card in hand with the lowest rank)" << endl;
}

void ConsoleDisplay::displayInvalidHOrC() {
	cout << "Invalid command. Player must be human (h) or computer (c)" << endl;
}

void ConsoleDisplay::displayBegOfRoundMsg(int id) {
	cout << "A new round begins. It's Player" << id << "'s turn to play" << endl;
}

void ConsoleDisplay::displayInformationForTurn(vector<Card> table, shared_ptr<Player> p, vector<Card> legalPlays) {
	cout << "================================PLAYER" << p->id << "'S TURN:================================" << endl;
	cout << "Cards on the table:" << endl;
	vector<Card> clubs;
	vector<Card> diamonds;
	vector<Card> hearts;
	vector<Card> spades;
	for(Card &c: table) {
		if(c.suite == 'C') {
			clubs.push_back(c);
		} else if(c.suite == 'D') {
			diamonds.push_back(c);
		} else if(c.suite == 'H') {
			hearts.push_back(c);
		} else {
			spades.push_back(c);
		}
	}

	// Print cards on table by type
	displayTypeOfCard(clubs, 'C');
	displayTypeOfCard(diamonds, 'D');
	displayTypeOfCard(hearts, 'H');
	displayTypeOfCard(spades, 'S');

	cout << "Your hand:" << endl;
	for(Card &c : p->hand) {
		cout << " " << c.rank << c.suite << endl;
	}

	cout << "Legal plays:" << endl;
	for(Card &c : legalPlays) {
		cout << " " << c.rank << c.suite << endl;
	}
}

void ConsoleDisplay::displayPlayCard(int id, Card c) {
	cout << "Player" << id << " plays " << c.rank << c.suite << endl;
}

void ConsoleDisplay::displayPlayNotLegal() {
	cout << "This is not a legal play." << endl;
}

void ConsoleDisplay::displayDiscardNotLegal() {
	cout << "This is not a legal discard." << endl;
}

void ConsoleDisplay::displayDiscardWithLegalPlays() {
	cout << "You have a legal play. You may not discard." << endl;
}

void ConsoleDisplay::displayDiscardCard(int id, Card c) {
	cout << "Player" << id << " discards " << c.rank << c.suite << endl;
}

void ConsoleDisplay::displayDeck(vector<Card> deck) {
	int idx = 0;
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < 13; ++j) {
			cout << deck[idx].rank << deck[idx].suite << " ";
			++idx;
		}
		cout << endl;
	}
}

void ConsoleDisplay::displayRageQuit(int id) {
	cout << "Player " << id << " ragequits. A computer will now take over" << endl;
}

void ConsoleDisplay::displayInvalidMsg() {
	cout << "Invalid command. Please enter a valid command." << endl;
}

void ConsoleDisplay::displayEndOfRoundMsg(vector<shared_ptr<Player>> players) {
	for(int i = 0; i < 4; ++i) {
		cout << "Player " << players[i]->id << "'s discards:";
		for(Card &c : players[i]->discards) {
			cout << " " << c.rank << c.suite;
		}
		cout << endl;
		cout << "Player " << players[i]->id << "'s score:" << players[i]->score << " + " << players[i]->newScore << " = " << (players[i]->score + players[i]->newScore) << endl;
	}
}

void ConsoleDisplay::displayWinner(int id) {
	cout << "Player " << id << " wins!" << endl;
}
