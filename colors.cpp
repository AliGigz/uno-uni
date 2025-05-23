#include <string>
#include "colors.h"


void changeTextColor(std::string &txt, std::string color)
{
	if (color == "red") txt = "\033[31m" + txt;
	else if (color == "green") txt = "\033[32m" + txt;
	else if (color == "yellow") txt = "\033[33m" + txt;
	else if (color == "blue") txt = "\033[34m" + txt;
	else if (color == "none") txt = "\033[37m" + txt;
	txt += "\033[0m";
}

std::string createColoredText(std::string text, std::string color)
{
	std::string result = text;
	changeTextColor(result, color);
	return result;
}

