#include "game.h"
#include "player.h"
#include "humanplayer.h"
#include "computerplayer.h"
#include "display.h"
#include "consoledisplay.h"
#include <cmath> 
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;


int Game::getStartPlayerId() {
	const Card startCard{'7', 'S'};
	for(int i = 0; i < 4; ++i) {
		for(Card &c : players[i]->hand) {
			if(c == startCard) {
				return (i + 1);
			}
		}
	}
	return 1;
}


bool Game::ranOutOfCards() {
	for(int i = 0; i < 4; ++i) {
		if(players[i]->hand.size() > 0) {
			return false;
		}
	}
	return true;
}


Game::Game(unsigned seed) : seed{seed}, dist{make_shared<ConsoleDisplay>()} {
	// initialize deck
	const char suite[4] = {'C', 'D', 'H', 'S'};
	for(int i = 0; i < 4; ++i) {
		for(int j = 1; j < 10; ++j) {
			deck.emplace_back(j + '0', suite[i]);
			if(j == 9) {
				deck.emplace_back('T', suite[i]);
				deck.emplace_back('J', suite[i]);
				deck.emplace_back('Q', suite[i]);
				deck.emplace_back('K', suite[i]);
			}
		}
	}
}

void Game::executeGame(bool changeStrat, bool loadingMode, std::vector<Card> loadedTable, std::vector<std::vector<Card>> loadedHands, std::vector<std::vector<Card>> loadedDiscards, std::vector<int> loadedScores, int loadedStartingPlayerId) {
	// if in loadingMode, must make them Human Player's so we can input commands in the .in files (ex: LOADEDSTATE1.in)
	if(loadingMode) {
		for(int i = 0; i < 4; ++i) {
			vector<Card> emptyHand;
			shared_ptr<Player> curr = make_shared<HumanPlayer>(i + 1, emptyHand);
			players.push_back(curr);
		}
	} 
	// else, prompt for human or computer
	else {
		int i = 0;
		while(i < 4) {
			dist->displayHorCPrompt(i + 1);
			char t;
			cin >> t;
			shared_ptr<Player> curr;
			vector<Card> emptyHand;
			if(t == 'h' || t == 'c') {
				// create HumanPlayer if h
				if(t == 'h') {
					curr = make_shared<HumanPlayer>(i + 1, emptyHand);
				} 
				// create ComputerPlayer if c
				else {
					// if changeStrat true, display prompt to change strategy
					int strat = 1;
					if(changeStrat) {
						dist->displayStratPrompt();
						cin >> strat;
					}
					curr = make_shared<ComputerPlayer>(i + 1, emptyHand, strat);
				}
				players.push_back(curr);
				++i;
			} else {
				dist->displayInvalidHOrC();
			}
	
		}
	}

	vector<int> winners;
	while(true) {
		bool quit = executeRound(loadingMode, loadedTable, loadedHands, loadedDiscards, loadedScores, loadedStartingPlayerId);
		// only start round from loaded state once
		if(loadingMode) loadingMode = false;
		// if someone entered the quit command, executeRound immediately return true to tell us to quit game
		if(quit) return;
		int minScore = players[0]->score;
		bool shouldEnd = false;
		for(int i = 0; i < 4; ++i) {
			minScore = min(minScore, players[i]->score);
			if(players[i]->score >= 80) {
				shouldEnd = true;
			}
		}
		if(shouldEnd) {
			for(int i = 0; i < 4; ++i) {
				if(players[i]->score == minScore) {
					winners.push_back(i + 1);
				}
			}
			break;
		}
	}
	for(int id : winners) {
		dist->displayWinner(id);
	}
}


bool Game::executeRound(bool loadingMode, std::vector<Card> loadedTable, std::vector<std::vector<Card>> loadedHands, std::vector<std::vector<Card>> loadedDiscards, std::vector<int> loadedScores, int loadedStartingPlayerId) {
	// if not in loadingMode, shuffle deck
	if(!loadingMode) {
		default_random_engine rng{seed};
		shuffle(deck.begin(), deck.end(), rng);
	}
	
	// if in loadingMode, set player's hands and scores to loaded values, set table to loadedTable
	if(loadingMode) {
		table = loadedTable;
		for(int i = 0; i < 4; ++i) {
			players[i]->hand = loadedHands[i];
			players[i]->score = loadedScores[i];
			// load the score of this player gained during this round
			int scoreGainedDuringRound = 0;
			for(Card &c : loadedDiscards[i]) {
				scoreGainedDuringRound += c.getNumberRank();
			}
			players[i]->newScore = scoreGainedDuringRound;
		}
	} 
	// else, deal cards regularily
	else {
		for(int i = 0; i < 4; ++i) {
			vector<Card> hand(deck.begin() + (i * 13), deck.begin() + (i * 13) + 13);
			players[i]->hand = hand;
		}
	}
	
	// get startingPlayerId. If in loadingMode, must start at loadedStartingPlayerId
	int startPlayerId = loadingMode ? loadedStartingPlayerId : getStartPlayerId();
	dist->displayBegOfRoundMsg(startPlayerId);
	bool firstTurn = true;

	// while no one ran out of cards
	while(!ranOutOfCards()) {
		// for each player
		int i = firstTurn ? startPlayerId - 1 : 0;
		while(i < 4 && !ranOutOfCards()) {
			vector<Card> legalPlays = getLegalPlays(players[i]);
			dist->displayInformationForTurn(table, players[i], legalPlays);
			// while they haven't played or discarded, keep prompting for action
			bool playedOrDiscarded = false;
			while(!playedOrDiscarded) {
				pair<char, Card> action = players[i]->getAction(legalPlays);
				if(action.first == 'q') {
					return true;
				} else {
					handleAction(action.first, action.second, legalPlays, i + 1, playedOrDiscarded);
				}
			}
			++i;
		}
		firstTurn = false;
	}

	// must come before score updates
	dist->displayEndOfRoundMsg(players);

	// for each player, update score
	for(int i = 0; i < 4; ++i) {
		players[i]->score += players[i]->newScore;
		players[i]->newScore = 0;
	}

	// clear table
	table.clear();
	return false;
}
