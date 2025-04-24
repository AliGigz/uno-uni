#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "cards.h"
#include "players.h"
#include "colors.h"
using namespace std;



static string winner = "";
void setWinner(Player players[])
{
	for (int i = 0; i < 4; i++)
		if (!players[i].hasCards())
			winner = i;
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

	// prepare cards and players
	for (int i = 1; i <= 14; i++) deck.push_back(Card(i, "red"));
	for (int i = 1; i <= 14; i++) deck.push_back(Card(i, "blue"));
	for (int i = 1; i <= 14; i++) deck.push_back(Card(i, "green"));
	for (int i = 1; i <= 14; i++) deck.push_back(Card(i, "yellow"));
	for (int i = 0; i < 7; i++) players[0].addCard(&deck);
	for (int i = 0; i < 7; i++) players[1].addCard(&deck);
	for (int i = 0; i < 7; i++) players[2].addCard(&deck);
	for (int i = 0; i < 7; i++) players[3].addCard(&deck);

	int option;
	int index = rand() % deck.size();
	currentCardOnTable = deck[index];
	deck.erase(deck.begin() + index);
	do
	{
		players[turn].showCards();
		string text = "";
		if (currentCardOnTable.getNumber() >= 10)
			text += currentCardOnTable.getAction();
		else
			text += to_string(currentCardOnTable.getNumber());
		changeTextColor(text, currentCardOnTable.getColor());
		cout << "current card on the table: " + text;
		do
		{
			cout << endl << "choose a card: ";
			cin >> option;
			if ( (option > players[turn].getCardsCount()) || (players[turn].getCard(option).getColor() != currentCardOnTable.getColor()) )
				cout << "\033[31mnot a valid option...\033[0m";
		} while ( (option > players[turn].getCardsCount()) || (players[turn].getCard(option).getColor() != currentCardOnTable.getColor()) );
		currentCardOnTable = players[turn].getCard(option);
		players[turn].removeCard(option, &deck);
		if (order == 0)
			turn++;
		else
			turn--;
		if ( (turn == 4) || (turn == -1) )
			turn = 0;
	} while (winner == "");
	return 0;
}

