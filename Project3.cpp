//Programmer: Travis Gopaul
//Date: 12/7/20
//Project3.cpp
//Executable program file for Casino Game Program

#include "Poker.h"
#include "BlackJack.h"

#include <iostream>

using namespace std;

int main()
{
	srand((unsigned)time( NULL ));	//set seed for rng in Card::shuffleCard() function
	char gameSelection;

	cout << "Welcome to the Diamond Casino!" << endl;
	cout << "Would you like to play Poker or Black Jack>" << endl;
	cout << "Poker (P)	Black Jack (B)" << endl;
	cin >> gameSelection;

	while(gameSelection != 'p' && gameSelection != 'P' && gameSelection != 'b' && gameSelection != 'B')
	{
		cout << "Please make valid selection (P/B): " << endl;
		cin >> gameSelection;
	}//end while

	if(gameSelection == 'p' || gameSelection == 'P')	//if poker is selected
	{
		Poker game;		//create poker object
		game.playGame();	//call playGame to run game program
	}//end if
	else if(gameSelection == 'b' || gameSelection == 'B')	//if black jack is selected
	{
		BlackJack game;		//create black jack object
		game.playGame();	//call playGame to run game program
	}//end if


	return 0;
}//end main
