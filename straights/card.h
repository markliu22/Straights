#ifndef CARD_H
#define CARD_H

class Card {
public:
	char rank;
	char suite;
	Card(char rank = '0', char suite = '0');
	int getNumberRank();
	bool operator==(const Card &other) const;
};

#endif
