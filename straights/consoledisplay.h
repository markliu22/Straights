#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H
#include "display.h"
#include <vector>
#include <memory>

class Card;
class Player;

class ConsoleDisplay : public Display {
	virtual void displayTypeOfCard(std::vector<Card> vec, char suite) override;
public:
	virtual void displayHorCPrompt(int id) override;
	virtual void displayInvalidHOrC() override;
	virtual void displayStratPrompt() override;
	virtual void displayBegOfRoundMsg(int id) override;
	virtual void displayInformationForTurn(std::vector<Card> table, std::shared_ptr<Player> p, std::vector<Card> legalPlays) override;
	virtual void displayPlayCard(int id, Card c) override;
	virtual void displayPlayNotLegal() override;
	virtual void displayDiscardCard(int id, Card c) override;
	virtual void displayDiscardNotLegal() override;
	virtual void displayDiscardWithLegalPlays() override;
	virtual void displayDeck(std::vector<Card> deck) override;
	virtual void displayRageQuit(int id) override;
	virtual void displayInvalidMsg() override;
	virtual void displayEndOfRoundMsg(std::vector<std::shared_ptr<Player>> players) override;
	virtual void displayWinner(int id) override;
};

#endif
