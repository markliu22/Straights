#include "normalgame.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <chrono>
using namespace std;

bool isBlankLine(string& line) {
	string word;
	stringstream ss(line, stringstream::in);
	if(!(ss >> word)) {
		return true;
	} 
	// if we actually read in a word
	return false;
}

int main(int argc, char * argv[]) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	if(argc > 1) {
		try {
			seed = stoi(string{argv[1]});
		} catch(invalid_argument &e) {
			cerr << e.what() << endl;
			return 1;
		} catch(out_of_range &e) {
			cerr << e.what() << endl;
			return -1;
		}
	}
	bool loadingMode = false;
	bool changeStrat = false;

	vector<Card> loadedTable;
	vector<int> loadedScores;
	vector<vector<Card>> loadedHands(4, vector<Card>(0));
	vector<vector<Card>> loadedDiscards(4, vector<Card>(0));
	int loadedStartingPlayerId = 1;

	if(argc > 2) {
		// index 2 should be 1 or 0, 1 means loadMode, 0 means regular game
		string arg = string{argv[2]};
		if(arg == "loadMode") {
			loadingMode = true;
		} else if(arg == "changeStrat") {
			changeStrat = true;
		}
	}

	if(loadingMode) {
		string line = "";
		getline(cin, line);
		string word = "";
		stringstream ss(line, stringstream::in);
		while(ss >> word) {
			// read in each card on table, add to loadedTable
			Card c{word.at(0), word.at(1)};
			loadedTable.push_back(c);
		}
		// read in each score and add to loadedScores
		for(int i = 0; i < 4; ++i) {
			int score;
			cin >> score;
			loadedScores.push_back(score);
		}
		int i = 0;
		while(i < 4) {
			getline(cin, line);
			if(isBlankLine(line)) continue;
			ss.clear();
			ss.str(line);
			while(ss >> word) {
				Card c{word.at(0), word.at(1)};
				loadedHands[i].push_back(c);
			}
			++i;
		}
		// for each player, read in cards in their discards
		i = 0;
		while(i < 4) {
			getline(cin, line);
			if(isBlankLine(line)) continue;
			ss.clear();
			ss.str(line);
			while(ss >> word) {
				Card c{word.at(0), word.at(1)};
				loadedDiscards[i].push_back(c);
			}
			++i;
		}
		// read in startingPlayerId
		cin >> loadedStartingPlayerId;
	}

	NormalGame g{seed};
	g.executeGame(changeStrat, loadingMode, loadedTable, loadedHands, loadedDiscards, loadedScores, loadedStartingPlayerId);
}
