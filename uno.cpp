#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "cards.h"
#include "players.h"
#include "colors.h"
using namespace std;


static int winner = -1;
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
void changeTableColor(string &tableColor)
{
	do
	{
		cout << "choose a color (red | green | blue | yellow): ";
		cin >> tableColor;
		if (!isColorIn(tableColor))
			cout << createColoredText("not a valid color!", "red") << endl;
	} while (!isColorIn(tableColor));
}

int main()
{
	/*
	 * deck -> the deck of cards on the table
	 * players -> all the players
	 * turn -> player's turn
	 * order -> clockwise 0 and anticlockwise 1
	*/
	srand((unsigned int)time(NULL));
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
	if ( (currentCardOnTable.getAction() == "wild") || currentCardOnTable.getAction() == "wild draw four" )
		changeTableColor(tableColor);
	do
	{
		if (turn == 0)
		{
			cout << endl;
			players[turn].showCards();
			
			// show current card
			string text = "";
			if (currentCardOnTable.getNumber() >= 10)
				text += currentCardOnTable.getAction();
			else
				text += to_string(currentCardOnTable.getNumber());
			changeTextColor(text, tableColor);
			cout << "current card on the table: " << text << endl;

			// show players cards
			for (int i = 1; i < 4; i++)
				cout << "player " << i + 1 <<  " : " << players[i].getCardsCount() << "\t"; 
			cout << endl;

			do
			{
				cout << "choose an option (0 to pick a card): ";
				cin >> option;

				if (option == 0)
					break;
				if (option > players[turn].getCardsCount())
					cout << createColoredText("not a valid option", "red") << endl;
				else if (!isCardValid(players[turn].getCard(option), currentCardOnTable, tableColor))
					cout << createColoredText("card must have the same color or number as the card on the table", "red") << endl;
			} while(!isCardValid(players[turn].getCard(option), currentCardOnTable, tableColor));
			cout << endl;
		}
		else
		{
			if (players[turn].hasCertainColorCard(tableColor))
				option = players[turn].getCertainColorCardIndex(tableColor) + 1;
			else if (players[turn].hasCertainNumberCard(currentCardOnTable.getNumber()))
				option = players[turn].getCertainNumberCardIndex(currentCardOnTable.getNumber()) + 1;
			else if (players[turn].hasWildCard())
				option = players[turn].getWildCardIndex() + 1;
			else
				option = 0;

			// show the card that the player has played
			if (option != 0)
			{
				string played = "";
				Card playedCard = players[turn].getCard(option);
				if (playedCard.getNumber() >= 10)
					played += playedCard.getAction();
				else
					played += to_string(playedCard.getNumber());
				changeTextColor(played, playedCard.getColor());

				cout << "player " << turn + 1 << " played " << played << endl;
			}
			else
				cout << "player " << turn + 1 << " picked a card " << endl;
		}
		if (option == 0)
			players[turn].addCard(&deck);
		else
		{
			currentCardOnTable = players[turn].getCard(option);
			tableColor = currentCardOnTable.getColor();
			players[turn].removeCard(option, &deck);
			if (currentCardOnTable.getAction() == "reverse")
			{
				if (order == 0)
					order = 1;
				else
					order = 0;
			}
			else if (currentCardOnTable.getAction() == "skip")
			{
				if (order == 0)
					turn++;
				else
					turn--;
			}
			else if (currentCardOnTable.getAction() == "draw two")
			{
				int next = 0;
				if (order == 0)
				{
					next = turn + 1;
					if (next >= 4)
						next = 0, turn = 0;
					else
						turn++;
					for (int i = 0; i < 2; i++)
						players[next].addCard(&deck);
				}
				else
				{
					next = turn - 1;
					if (next <= -1)
						next = 3, turn = 3;
					else
						turn--;
					for (int i = 0; i < 2; i++)
						players[next].addCard(&deck);
				}
				cout << "player " << next + 1 << " lost it's turn" << endl;
			}
			else if ( (currentCardOnTable.getAction() == "wild") || (currentCardOnTable.getAction() == "wild draw four") ) 
			{
				if (turn == 0)
				{
					changeTableColor(tableColor);
					cout << endl;
				}
				else
				{
					if (players[turn].hasCertainColorCard("red")) tableColor = "red";
					else if (players[turn].hasCertainColorCard("blue")) tableColor = "blue";
					else if (players[turn].hasCertainColorCard("green")) tableColor = "green";
					else if (players[turn].hasCertainColorCard("yellow")) tableColor = "yellow";

					string txt = tableColor;
					changeTextColor(txt, tableColor);
					cout << "player " << turn + 1 << " changed table color to " << txt << endl;
				}
				if (currentCardOnTable.getAction() == "wild draw four")
				{
					int next = 0;
					if (order == 0)
					{
						next = turn + 1;
						if (next >= 4)
							next = 0, turn = 0;
						else
							turn++;
						for (int i = 0; i < 4; i++)
							players[next].addCard(&deck);
					}
					else
					{
						next = turn - 1;
						if (next <= -1)
							next = 3, turn = 3;
						else
							turn--;
						for (int i = 0; i < 4; i++)
							players[next].addCard(&deck);
					}
					cout << "player " << next + 1 << " lost it's turn" << endl;
				}
			}
		}
		setWinner(players);
		if (winner != -1)
			break;
		if (order == 0)
		{
			turn++;
			if (turn >= 4)
				turn = 0;
		}
		else
		{
			turn--;
			if (turn <= -1)
				turn = 3;
		}
		sleep(1); // take one second for player to see whats happening
	} while (winner == -1);

	cout << "winner is " << winner + 1 << endl;
	return 0;
}

