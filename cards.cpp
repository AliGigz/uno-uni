#include <string>
#include "cards.h"


Card::Card() { }
Card::Card(int number, std::string color)
{
	this->setColor(color);
	this->setNumber(number);
}
void Card::setNumber(int number)
{
	this->Number = number;
	switch (number) {
		case 10:
			this->Action = "reverse";
			break;
		case 11:
			this->Action = "skip";
			break;
		case 12:
			this->Action = "draw two";
			break;
		case 13:
			this->Action = "wild";
			this->Color = "none";
			break;
		case 14:
			this->Action = "wild draw four";
			this->Color = "none";
			break;
	}
}
int Card::getNumber()
{
	return this->Number;
}
void Card::setColor(std::string color)
{
	this->Color = color;
}
std::string Card::getColor()
{
	return this->Color;
}

std::string Card::getAction()
{
	return this->Action;
}

void fillDeck(std::vector<Card> *deck)
{
	for (int i = 1; i <= 14; i++) deck->push_back(Card(i, "red"));
	for (int i = 1; i <= 14; i++) deck->push_back(Card(i, "blue"));
	for (int i = 1; i <= 14; i++) deck->push_back(Card(i, "green"));
	for (int i = 1; i <= 14; i++) deck->push_back(Card(i, "yellow"));
}

