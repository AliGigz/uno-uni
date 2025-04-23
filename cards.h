#pragma once
#include <string>


/*
 * action cards are also used with Card class but with this order:
 * * 10: reverse
 * * 11: skip
 * * 12: draw two
 * * 13: wild
 * * 14: wild draw four
*/
class Card
{
	int Number;
	std::string Color;
	std::string Action;
	public:
		Card();
		Card(int, std::string);
		void setNumber(int);
		int getNumber();
		void setColor(std::string);
		std::string getColor();
		std::string getAction();
};

