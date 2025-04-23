#pragma once
#include <vector>
#include "cards.h"


class Player
{
	std::vector<Card> Cards;
	int CardCount = 0;
	public:
		void addCard(std::vector<Card>*);
		void removeCard(Card*, std::vector<Card>*);
		void showCards();
};

