//Programmer: Travis Gopaul
//Date: 12/7/20
//BlackJack.h
//Header file for BlackJack game

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "Card.h"

class BlackJack:public Card
{
	private:
		//BlackJack hand will be handled dynamically
		//Similar to vector, it can be resized if player hits

		int dHandSize;			//dealer hand size; will be resized as dealer hits
                int pHandSize;			//player hand size; will be resized as player hits
		Acard *dealerHand;		//pointer to array of cards for dealer
		Acard *playerHand;		//pointer to array of cards for player
		static float seedMoney;		//player bank
		float bet;			//player bet; max bet = seedMoney
		float insurance;		//insurance = 50% of bet
		float reward;			//payout rate for winning hand = 1.5x bet
		float winnings;			//reward * bet
		bool isBlackJackHand;

		void dealCards();		//deals cards to player and dealer
		Acard* hit(Acard*, int&);			//deals another card; calls resize to make more space
		Acard* resizeHand(Acard*, int&);	//resizes hand array with dynamic memory allocation when hit() is called
		bool isBlackJack(Acard*);	//determines if hand is black jack
		int handValue(Acard*, int);	//calculates hand value
		void printBank();		//function to print seed money, winnings and updated seed money 
		void resetHand();		//reset hands to a 2 card array
	public:
		BlackJack();			//constructor
		~BlackJack();			//destructor to handle memory deallocation
		void playGame();		//function to run BlackJack Game
		//NEED TO DECIDE WHERE TO PUT WINNING HAND INFO

};

#endif
