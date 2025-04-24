#pragma once
#include <vector>
#include "cards.h"


class Player
{
	std::vector<Card> Cards;
	int CardsCount = 0;
	public:
		void addCard(std::vector<Card>*);
		void removeCard(int, std::vector<Card>*);
		void showCards();
		bool hasCards();
		int getCardsCount();
		Card getCard(int);
		bool hasCertainColorCard(std::string);
		int getCertainColorCardIndex(std::string);
		bool hasCertainNumberCard(int);
		int getCertainNumberCardIndex(int);
		bool hasWildCard();
		int getWildCardIndex();
};

