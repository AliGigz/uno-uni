#include <string>
#include "cards.h"


Card::Card() { }
Card::Card(int number, std::string color)
{
	this->setNumber(number);
	this->setColor(color);
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
			break;
		case 14:
			this->Action = "wild draw four";
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

