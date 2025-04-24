#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "players.h"
#include "cards.h"
#include "colors.h"


void Player::addCard(std::vector<Card>* deck)
{
	int index = rand() % deck->size();
	this->Cards.push_back((*deck)[index]);
	deck->erase(deck->begin() + index);
	this->CardsCount++;
	// refill the deck if it's empty
	if (deck->size() == 0)
		fillDeck(deck);
}
void Player::removeCard(int index, std::vector<Card>* deck)
{
	index--;
	Card card = this->Cards[index];
	deck->push_back(Card(card.getNumber(), card.getColor()));
	this->Cards.erase(this->Cards.begin() + index);
	this->CardsCount--;
}

void Player::showCards()
{
	int i = 1;
	for (Card c : this->Cards)
	{
		std::cout << i << ": ";
		std::string text = "";
		if (c.getNumber() >= 10)
			text += c.getAction();
		else
			text += std::to_string(c.getNumber());
		changeTextColor(text, c.getColor());
		std::cout << text;
		std::cout << std::endl;
		i++;
	}
}

bool Player::hasCards()
{
	return (this->Cards.size() != 0);
}

int Player::getCardsCount()
{
	return this->CardsCount;
}

Card Player::getCard(int index)
{
	return this->Cards[index - 1];
}

