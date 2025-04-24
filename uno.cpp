#include <cstdlib>
#include <iostream>
#include <vector>
#include "cards.h"
#include "players.h"
using namespace std;


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

	// prepare cards and players
	for (int i = 1; i <= 14; i++) deck.push_back(Card(i, "red"));
	for (int i = 1; i <= 14; i++) deck.push_back(Card(i, "blue"));
	for (int i = 1; i <= 14; i++) deck.push_back(Card(i, "green"));
	for (int i = 1; i <= 14; i++) deck.push_back(Card(i, "yellow"));
	for (int i = 0; i < 7; i++) players[0].addCard(&deck);
	for (int i = 0; i < 7; i++) players[1].addCard(&deck);
	for (int i = 0; i < 7; i++) players[2].addCard(&deck);
	for (int i = 0; i < 7; i++) players[3].addCard(&deck);

	players[0].showCards();
	cout << endl;
	players[1].showCards();
	cout << endl;
	players[2].showCards();
	cout << endl;
	players[3].showCards();
	cout << endl;

	return 0;
}

