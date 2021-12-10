#ifndef DISPLAY_H
#define DISPLAY_H
#include "player.h"
#include <iostream>
#include <vector>
#include <memory>

class Display {
	virtual void displayTypeOfCard(std::vector<Card> hand, char suite) = 0;
public:
	virtual void displayHorCPrompt(int id) = 0;
	virtual void displayInvalidHOrC() = 0;
	virtual void displayStratPrompt() = 0;
	virtual void displayBegOfRoundMsg(int id) = 0;
	virtual void displayInformationForTurn(std::vector<Card> table, std::shared_ptr<Player> p, std::vector<Card> legalPlays) = 0;
	virtual void displayPlayCard(int id, Card c) = 0;
	virtual void displayPlayNotLegal() = 0;
	virtual void displayDiscardCard(int id, Card c) = 0;
	virtual void displayDiscardNotLegal() = 0;
	virtual void displayDiscardWithLegalPlays() = 0;
	virtual void displayDeck(std::vector<Card> deck) = 0;
	virtual void displayRageQuit(int id) = 0;
	virtual void displayInvalidMsg() = 0;
	virtual void displayEndOfRoundMsg(std::vector<std::shared_ptr<Player>> players) = 0;
	virtual void displayWinner(int id) = 0;
};

#endif
