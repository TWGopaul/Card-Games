//Programmer: Travis Gopaul
//Date: 11/17/20
//Card.cpp
//Member definitions for Card header file


#include "Card.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;
//******************* Private Members *************************

int Card::nextCard = 0;		//set nextCard to 0, the first card in the deck

//******************* Public Members **************************


Card::Card()			//card class constructor
{
	int count = 0;		//index for cards in deck
	for(int j = 0; j < 4; j++)			//for each suit
	{
		for(int k = 2; k < 15; k++)		//assign a card a value 1-13 and a suit
		{
			Deck[count].pic = suits[j];
		       	Deck[count].num = k;
			count++;				//increase index for deck
		}//end for
	}//end for
}//end constructor

void Card::shuffleCard()
{
	int rnum;			//variable to hold random number

	for (int i = 0; i < 52; i++)		//for each card in the deck
	{
		rnum = rand()% 52;              //generate random number between 0-51
		swap(Deck[i], Deck[rnum]);	//swap the current card with a random position's card
	}//end for

	nextCard = 0;

}//end ShuffleCard()

Acard Card::getCard()
{
	Acard next = Deck[nextCard];	//temp card to return; set equal to the next card in the deck
	nextCard++;			//increase next card to next card in the deck
	return next;			//return the nextCard		
}//end getCard()

void Card::printCards(Acard cards[], int numCards)	//function to print cards
{
	char num[numCards];

	for(int i = 0; i < numCards; i++)	//create an array for face cards and numerical symbols based off a card's number, ie Ace = 1
	{					//used to print face card values
        if(cards[i].num == 14)
                num[i] = 'A';
	else if(cards[i].num == 11)
                num[i] = 'J';
	else if(cards[i].num == 12)
                num[i] = 'Q';
	else  if(cards[i].num == 13)
                num[i] = 'K';
	else
		num[i] = cards[i].num;
	}

	for(int i = 0; i < numCards; i++)	//top border
		cout << "_________ ";
	cout << endl;

	//Cards are printed line by line
	//Depending on the value, symbols and numbers are printed 
        for(int i = 0; i < numCards; i++)	//line 1
	{	
		if(num[i] == 65)
		       cout << "|" << num[i] <<setw(8) << "| ";
		else if(num[i] == 10)
                        cout << "|" << static_cast<int>(num[i]) << setw(7) << "| ";
		else if( num[i] == 74 || num[i] == 81 || num[i] == 75)
			cout << "|" <<cards[i].pic << num[i]  << setw(7) << "| ";
		else
			cout << "|" << static_cast<int>(num[i]) <<setw(8) << "| ";
	}

	cout << endl;
        for(int i = 0; i < numCards; i++)	//line 2
	{
		if(num[i] == 3)
			cout << "|" << setw(6)<< cards[i].pic << setw(5) << "| ";
		else if(num[i] == 4 ||num[i] == 5 ||num[i] == 6 ||num[i] == 7 ||num[i] == 8 ||num[i] == 9 ||num[i] == 10)
			cout << "| " << cards[i].pic << setw(6) << cards[i].pic << " | "; 
		else
			cout <<"|"<<setw(9)<<"| ";
	}

	cout << endl;
        for(int i = 0; i < numCards; i++)	//line 3
	{
		if(num[i] == 2 || num[i] == 7 || num[i] == 8 || num[i] == 9 || num[i] == 10)
			cout << "|" << setw(6) << cards[i].pic <<setw(5) << "| ";
		else
			cout <<"|"<<setw(9)<<"| ";
	}

	cout << endl;
        for(int i = 0; i < numCards; i++)	//line 4
	{
		if(num[i] == 9 || num[i] == 10)
			 cout << "| " << cards[i].pic << setw(6) << cards[i].pic << " | ";
		else
			cout <<"|"<<setw(9)<<"| ";
	}
	cout << endl;

        for(int i = 0; i < numCards; i++)	//line 5
	{
		if(num[i] == 65 || num[i] == 3 || num[i] == 5)
			cout << "|" << setw(6) << cards[i].pic <<setw(5) << "| ";
		else if(num[i] == 6 || num[i] == 7 || num[i] == 8)
			 cout << "| " << cards[i].pic << setw(6) << cards[i].pic << " | ";
		else 
			cout <<"|"<<setw(9)<<"| ";	
	}
	cout << endl;

        for(int i = 0; i < numCards; i++)	//line 6
	{
		if(num[i] ==9 || num[i] == 10)
			cout << "| " << cards[i].pic << setw(6) << cards[i].pic << " | ";
		else
			cout <<"|"<<setw(9)<<"| ";
	}
	cout << endl;

        for(int i = 0; i < numCards; i++)	//line 7
	{
		if(num[i] == 2 || num[i] == 8 || num[i] == 10)
			cout << "|" << setw(6) << cards[i].pic <<setw(5) << "| ";
		else
			cout <<"|"<<setw(9)<<"| ";
	}
	cout << endl;

	for(int i = 0; i < numCards; i++)	//line 8
	{
		if(num[i] == 3)
			cout << "|" << setw(6) << cards[i].pic <<setw(5) << "| ";
		else if(num[i] == 4 || num[i] == 5 || num[i] == 6 || num[i] == 7 || num[i] == 8 || num[i] == 9 || num[i] == 10)
			cout << "| " << cards[i].pic << setw(6) << cards[i].pic << " | ";
		else
			cout <<"|"<<setw(9)<<"| ";
	}
	cout << endl;

	for(int i = 0; i < numCards; i++)       //line 9
	{
		if(num[i] == 65)
                       cout << "|" << setw(7) << num[i] << "| ";
		else if(num[i] == 10)
			cout << "|" << setw(7) << static_cast<int>(num[i]) << "| "; 
                else if( num[i] == 74 || num[i] == 81 || num[i] == 75)
                        cout << "|" << setw(6) <<  num[i] << cards[i].pic << "| ";
                else
                        cout << "|" << setw(7) << static_cast<int>(num[i]) << "| ";

	}

	cout << endl;
        for(int i = 0; i < numCards; i++)	//bottom border
		cout << "_________ ";

	cout << endl;
}//end printCard()

void Card::resetDeck()		//function resets nextCard to 0 for next play through
{
	nextCard = 0;
}//end resetDeck()
