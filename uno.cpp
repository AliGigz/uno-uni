#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "cards.h"
#include "players.h"
#include "colors.h"
using namespace std;



static string winner = "";
static string colors[] = {"red", "green", "blue", "yellow"};
void setWinner(Player players[])
{
	for (int i = 0; i < 4; i++)
		if (!players[i].hasCards())
			winner = i;
}
bool isColorIn(string color)
{
	for (string c : colors)
		if (c == color)
			return true;
	return false;
}
bool isCardValid(Card trownCard, Card currentCardOnTable, string tableColor)
{
	if (trownCard.getColor() == "none")
		return true;
	if (trownCard.getColor() == tableColor)
		return true;
	if (trownCard.getNumber() == currentCardOnTable.getNumber())
		return true;
	return false;
}

int main()
{
	/*
	 * deck -> the deck of cards on the table
	 * players -> all the players
	 * turn -> player's turn
	 * order -> clockwise 0 and anticlockwise 1
	*/
	vector<Card> deck;
	Player players[4] = {Player(), Player(), Player(), Player()};
	int turn = 0, order = 0;
	Card currentCardOnTable;
	string tableColor;

	// prepare cards and players
	fillDeck(&deck);
	for (int i = 0; i < 7; i++) players[0].addCard(&deck);
	for (int i = 0; i < 7; i++) players[1].addCard(&deck);
	for (int i = 0; i < 7; i++) players[2].addCard(&deck);
	for (int i = 0; i < 7; i++) players[3].addCard(&deck);

	int option;
	int index = rand() % deck.size();
	currentCardOnTable = deck[index];
	deck.erase(deck.begin() + index);
	tableColor = currentCardOnTable.getColor();
	do
	{
		players[turn].showCards();
		string text = "";
		if (currentCardOnTable.getNumber() >= 10)
			text += currentCardOnTable.getAction();
		else
			text += to_string(currentCardOnTable.getNumber());
		changeTextColor(text, tableColor);
		cout << "current card on the table: " + text;

		do
		{
			cout << endl << "player " << (turn + 1) << " -> " << "choose a card (0 to pick a card): ";
			cin >> option;
			if (option == 0)
			{
				players[turn].addCard(&deck);
				break;
			}
			if (option > players[turn].getCardsCount())
				cout << "\033[31mnot a valid option!\033[0m" << endl;
			else if (!isCardValid(players[turn].getCard(option), currentCardOnTable, tableColor))
				cout << "\033[31card must have the same color as the card on the table!\033[0m" << endl;
		} while ( (option > players[turn].getCardsCount()) || (!isCardValid(players[turn].getCard(option), currentCardOnTable, tableColor)));

		if (option != 0)
		{
			currentCardOnTable = players[turn].getCard(option);
			tableColor = currentCardOnTable.getColor();
			players[turn].removeCard(option, &deck);

			if (currentCardOnTable.getAction() == "reverse")
				if (order == 0)
					order = 1;
				else
					order = 0;
			else if (currentCardOnTable.getAction() == "skip")
			{
				if (order == 0)
					turn++;
				else
					turn--;
			}
			else if (currentCardOnTable.getAction() == "draw two")
			{
				if (order == 0)
				{
					players[turn+1].addCard(&deck);
					players[turn+1].addCard(&deck);
				}
				else
				{
					players[turn-1].addCard(&deck);
					players[turn-1].addCard(&deck);
				}
			}
			else if ( (currentCardOnTable.getAction() == "wild") || (currentCardOnTable.getAction() == "wild draw four"))
			{
				do
				{
					cout << "choose a color (red | green | yellow | blue): ";
					cin >> tableColor;
					if (!isColorIn(tableColor))
						cout << "\033[31mnot a valid color!\033[0m" << endl;
				}while (!isColorIn(tableColor));
				if (currentCardOnTable.getAction() == "wild draw four")
				{
					if (order == 0)
					{
						players[turn+1].addCard(&deck);
						players[turn+1].addCard(&deck);
						players[turn+1].addCard(&deck);
						players[turn+1].addCard(&deck);
					}
					else
					{
						players[turn-1].addCard(&deck);
						players[turn-1].addCard(&deck);
						players[turn-1].addCard(&deck);
						players[turn-1].addCard(&deck);
					}
				}
			}
		}
		setWinner(players);
		if (order == 0)
		{
			turn++;
			if (turn == 4)
				turn = 0;
		}
		else
		{
			turn--;
			if (turn == -1)
				turn = 3;
		}
	} while (winner == "");
	cout << "winner is " << (turn + 1) << endl;
	return 0;
}

