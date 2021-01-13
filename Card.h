//Programmer: Travis Gopaul
//Date: 01/13/21
//Card.h
//Header file for Card class

#ifndef CARD_H
#define CARD_H

struct Acard		//card struct
{
	int num;	//variable to store card value
	const char *pic;	//variable to store suit picture
};

class Card		//Card class members
{
	private:
		static int nextCard;	 //index for the next available card
		const char spade[4] = "\xe2\x99\xa0";
	        const char club[4] = "\xe2\x99\xa3";
	        const char heart[4] = "\xe2\x99\xa5";
	        const char diamond[4] = "\xe2\x99\xa6";
		const char *suits[4] = {spade, club, heart, diamond};	//array of char pointers pointing to suits; used for assigning suit in deck constructor
		Acard Deck[52];                 //array of cards; will be populated in constructor

	public:
		Card();				//constructor
		void shuffleCard();		//function to shuffle cards
		Acard getCard();		//function to return next available card info
		void printCards(Acard[], int);	//function displays cards; array of cards and array size passed as parameter
		void resetDeck();		//function resets nextCard to 0 for next play through
};

#endif
