#include <cstdlib>
#include <iostream>
#include <vector>
#include "players.h"
#include "cards.h"


void Player::addCard(std::vector<Card>* deck)
{
	int index = rand() % deck->size();
	this->Cards.push_back((*deck)[index]);
	deck->erase(deck->begin() + index);
	this->CardCount++;
}
void Player::removeCard(Card* card, std::vector<Card>* deck)
{
	for (int i = 0; i < this->CardCount; i++)
		if ( (this->Cards[i].getNumber() == card->getNumber()) && (this->Cards[i].getColor() == card->getColor()) )
		{
			this->Cards.erase(this->Cards.begin() + i);
			deck->push_back(Card(card->getNumber(), card->getColor()));
		}
	this->CardCount--;
}

void Player::showCards()
{
	for (Card c : this->Cards)
	{
		std::cout << c.getColor() << " ";
		if (c.getNumber() >= 10)
			std::cout << c.getAction();
		else
			std::cout << c.getNumber();
		std::cout << std::endl;
	}
}

