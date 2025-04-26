#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "players.h"
#include "cards.h"
#include "colors.h"


void Player::addCard(std::vector<Card>* deck)
{
	// get a random card from the deck and remove it from the deck itself
	srand((unsigned int)time(NULL));
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
	index--; // cause the index which is given is one more (option starts from 1)
	// Remove the card and put it back to the deck
	Card card = this->Cards[index];
	deck->push_back(Card(card.getNumber(), card.getColor()));
	this->Cards.erase(this->Cards.begin() + index);
	this->CardsCount--;
}

void Player::showCards()
{
	this->sortCards(); // sort the cards before showing them
	// show the cards from 1 and also change the colors
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

bool Player::hasCertainColorCard(std::string color)
{
	for (Card c : this->Cards)
		if (c.getColor() == color)
			return true;
	return false;
}

int Player::getCertainColorCardIndex(std::string color)
{
	int index;
	for (int i = 0; i < this->Cards.size(); i++)
		if (this->Cards[i].getColor() == color)
		{
			index = i;
			break;
		}
	return index;
}

bool Player::hasCertainNumberCard(int number)
{
	for (Card c : this->Cards)
		if (c.getNumber() == number)
			return true;
	return false;
}
int Player::getCertainNumberCardIndex(int number)
{
	int index;
	for (int i = 0; i < this->Cards.size(); i++)
		if (this->Cards[i].getNumber() == number)
		{
			index = i;
			break;
		}
	return index;
}

bool Player::hasWildCard()
{
	for (Card c : this->Cards)
		if ( (c.getAction() == "wild") || (c.getAction() == "wild draw four") )
			return true;
	return false;
}

int Player::getWildCardIndex()
{
	int index;
	for (int i = 0; i < this->Cards.size(); i++)
		if ( (this->Cards[i].getAction() == "wild") || (this->Cards[i].getAction() == "wild draw four") )
		{
			index = i;
			break;
		}
	return index;
}

void Player::sortCards()
{
	std::string colors[] = {"red", "green", "blue", "yellow", "none"};
	std::vector<Card> cards;
	// the sorting should be -> red green blue yellow
	for (std::string color : colors)
		for (Card c : this->Cards)
			if (c.getColor() == color)
				cards.push_back(c);

	this->Cards = cards;
}

