//Programmer: Travis Gopaul
//Date: 12/4/20
//Poker.h
//Header file for Poker class

#ifndef POKER_H
#define POKER_H

#include "Card.h"

class Poker:public Card
{
	private:
		static float seedMoney;	//starting funds
		float bet;		//bet amount
		static const int handSize = 5;	//hand size; 5 cards for poker
		
		Acard hand[handSize];	//array of cards for player's hand 
		void dealCards();       //function to deal cards to player
                void redraw();          //function to redraw a card
                void sortHand();        //function sorts hand in ascending order to help determine hand rank
                int handRank(); 	//determines hand rank
                float payout(int);      //determines pay out on winning hands
	public:
		Poker();		//constructor - will initiate variables and call playGame() to run game
		void playGame();	//function to run game 
};

#endif
