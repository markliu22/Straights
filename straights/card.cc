#include "card.h"

Card::Card(char rank, char suite) : rank{rank}, suite{suite} {}

int Card::getNumberRank() {
	switch(rank) {
		case 'T':
			return 10;
		case 'J':
			return 11;
		case 'Q':
			return 12;
		case 'K':
			return 13;
		default:
			return rank - '0';
	}
}

bool Card::operator==(const Card &other) const {
	return (rank == other.rank) && (suite == other.suite);
}
