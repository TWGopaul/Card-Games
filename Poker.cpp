//Programmer: Travis Gopaul
//Date: 12/4/20
//Poker.cpp
//Member definitions for Poker class

#include "Poker.h"
#include "Card.h"
#include <iostream>

using namespace std;

//***************** Public Members ********************

Poker::Poker()	//poker constructor; a deck of cards is created upon instantiaton of poker class
{
	system("clear");

	bet = 0.0;					//set initial bet value to 0

	cout << "Welcome to the Poker table!" << endl;
	cout << "Enter your bank roll amount: $" ;	//get seedMoney from user input
	cin >> seedMoney;

}//end poker constructor

void Poker::playGame()		//function handles game simulation
{
	int winnings;
	char play;              //variable for user input if they want to play
	do                                              //keep playing until user decides to stop
        {

        	cout << "Would you like to play 5 card draw poker? (Y/N)";
                	cin >> play;
                	while(play != 'y' && play != 'Y' && play != 'n' && play != 'N') //input validation
                	{
                        	cout << "Please make valid selection (Y/N) : ";
                        	cin >> play;
                	}//end while

		system("clear");

                	if(play == 'y' || play == 'Y')                  //if user wants to play. else program exits
                	{
				system("clear");
                        	cout << "Enter amount to bet: $";
                        	cin >> bet;
                        	while(bet > seedMoney)                  //bet amount verification; cannot bet more than seed money
                        	{
                                	cout << "Insufficient funds! Seed money: $" << seedMoney << endl;
                                	cout << "Please enter bet amount not exceeding seed money: $";
                               		cin  >> bet;
                        	}//end while
				
				system("clear");

                        	seedMoney -= bet;                       //subtract bet amount from seed money;

                        	shuffleCard();                          //function from Card class; shuffles deck of cards
                        	dealCards();                            //function to deal cards

                        	cout << "Your hand" << endl;
                        	cout << "=========" << endl << endl;

                        	printCards(hand, handSize);             //function from Card class; display hand
                        	redraw();                               //function gives option to redraw cards
				sortHand();				//function sorts hand in order to determine value

				winnings = bet * handRank();		//calculate winnings
				cout << "Your initial balance was: $" << seedMoney << endl;
				cout << "You won: $" << winnings << endl;
				seedMoney += winnings;			//add winnings to balance	
			       	cout << "Your current balance is: $" << seedMoney << endl;
				resetDeck();				//function from Card class; reset nextCard to 0;	
                	}//end if

                	if(seedMoney <= 0)                              //if no money left display message and quit
                	{
                        	cout << "Sorry, you've lost all your money! The house always wins!" << endl;
                        	break;
                	}//end if
        	}
        	while (play != 'n' && play != 'N');             //keep playing until user decides to stop

}//end playGame()

//***************** Private Members *******************

float Poker::seedMoney = 0.0;

void Poker::dealCards()				//function defines Acard hand[] array elements using for loop calling getCard()
{
	for(int i = 0; i < handSize; i++)
	{
		hand[i] = getCard();		//getCard() is from Card class and returns Acard from the Card::deck[] member
	}//end for
}//end dealCards()

void Poker::redraw()		//function to redraw cards
{
	int redraw;		//variable to store user selection

	char num[handSize];
        for(int i = 0; i < handSize; i++)       //create an array for face cards and numerical symbols based off a card's number, ie Ace = 14
        {                                       //used to print face card values
        if(hand[i].num == 14)						
                num[i] = 'A';
        else if(hand[i].num == 11)
                num[i] = 'J';
        else if(hand[i].num == 12)
                num[i] = 'Q';
        else  if(hand[i].num == 13)
                num[i] = 'K';
        else
                num[i] = hand[i].num;
        }

	for(int i = 0; i < handSize; i++)		//for each card in hand display option to redraw
	{
		if(num[i] > 64)
			cout << num[i] << hand[i].pic << ": HOLD(1) or REDRAW(0)? : ";		//conditional for face card display
		else
			cout << static_cast<int>(num[i]) << hand[i].pic << ": HOLD(1) or REDRAW(0)? : ";	//conditional for numerical display
		cin >> redraw;
		cout << endl;

		if(redraw == 0)			//if 1, assign that card to a new card obtained with getCard()
			hand[i] = getCard();		//else do nothing
	}//end for

	printCards(hand, handSize);			//display new hand
}//end redraw()


void Poker::sortHand()		//function sorts hand of cards by num value using insertion sort
{
	Acard key;
	int i;
	for(int j = 1; j < handSize; j++)
	{
		key = hand[j];		//examine 2nd element
		i = j - 1;		//examine 1st element

		while(i >= 0 && hand[i].num > key.num)	//while i > 0 and the preceeding element is greater than the next
		{
			hand[i + 1] = hand[i];		//set the next element to the preceeding position
			i = i - 1;			//move iterator back one position
		}//end while
		hand[i + 1] = key;			//place the lowest element in the correct position
	}//end for
}//end sortHand()


int Poker::handRank()			//function returns a value that will be the multiplier to calculate winnings
{
	int handValue = 0, match1 = 0, match2 = 0, token = 0;	//variable to handValue, counters to determine pair, 3 card, 4 card and full house
	bool rf = false, sf = true, straight = true, flush = true;	//variables to determine royal flush, straight flush, straight and flush
	bool jackOrBetter = false;				//variable if 1 pair is jack or better
	int i = 0;
	
	while((i + 1 < handSize) && sf)	//STRAIGHT FLUSH
	{
		if((hand[i].pic == hand[i + 1].pic) && (hand[i].num +1 == hand[i + 1].num))	//if card[i] suit matches card[i+1] suit and card[i].num +1 = card[i+1].num
		{
			sf = true;
			if(sf &&  ((hand[i].pic == hand[i + 1].pic) && (hand[i].num == 5 && hand[i + 1].num == 14)))	//logic if Ace low straight, when hand is sorted A(14) will be last (2 3 4 5 A)
				sf = true;
		}//end if
		else
			sf = false;

		i++;
	}//end while

	if(sf)		//ROYAL FLUSH - if there is a straight flush, check if a royal flush
	{
		if(hand[0].num == 10 && hand[4].num == 14)         //if first card is a jack and the last card is an ace
		{
			rf = true;				//straight is a royal flush
			sf = false;				//mark sf as false to calculate proper payout
		}//end if
	}//end if

	if (!rf)	//STRAIGHT - if not a straight flush or royal flush check for straight
	{
		int j = 0;
		while((j + 1 < handSize) && straight)
		{
			if (hand[j].num + 1 == hand[j + 1].num)					//if the next card num is larger by 1, straight possibility
			{
				straight = true;
				if(straight &&  (hand[3].num == 5 && hand[4].num == 14))		//logic if Ace low straight, when hand is sorted A(14) will be last (2 3 4 5 A)
                               		sf = true;
			}//end if
			else
				straight = false;
			j++;
		}//end while

		if(!straight)	//FLUSH - if not a straight check for flush
		{
			int k = 0;
			while((k + 1 < handSize) && flush)
			{
				flush = ((hand[k].pic == hand[k + 1].pic) ? true: false); //if the suits match, flush possibility
				k++;
			}//end while
		}//end if
	}//end else if

	if(!flush) //logic for matching hands - 4 & 3 kind, full house, two pair, pair
	{
		int l = 1, pairPos = 0;

		while (l < handSize)			//first while loop can catch a pair, 3 kind, 4 kind
		{
			if (hand[token].num == hand[l].num)	//if the first card number matches the next
			{	
				match1++;			//increase match1; continue to look for match with token
				jackOrBetter = (hand[token].num > 10) ?  true : false;
				pairPos = token;
			}//end if
			else if(match1 == 0) 
				token = l;			//if the cards don't match move the token to the next card and look for matches

			l++;					//increase iterator
		}//end while

		if(match1 == 1 || match1 == 2)			//if there is one pair or 3 of a kind, check for another pair / full house
		{
			token = pairPos + match1 + 1;			//move token to position 1 place after the last matching card
			l = token + 1;					//reset iterator
			while(l < handSize && token < handSize)			
			{
				if(hand[token].num == hand[l].num)	//search array for matches to the new token
						match2++;	//increase match2

				l++;				//increase iterator
			}//end while
		}//end if
	}//end else if

	if(rf)								//ROYAL FLUSH
		handValue = 10000;
	else if (sf)							//STRAIGHT FLUSH
		handValue = 1000;
	else if (straight)						//STRAIGHT
		handValue = 6;
	else if (flush)							//FLUSH
		handValue = 8;
	else if(match1 == 3)                                            //4 OF A KIND
                handValue = 20;
        else if((match1 == 2 && match2 == 1) || (match1 == 1 && match2 == 2))	//FULL HOUSE
                handValue = 10;
        else if((match1 == 2 && match2 == 0) || (match2 == 2 && match1 == 0))	//3 OF A KIND
                handValue = 4;
        else if(match1 == 1 && match2 == 1)					//2 PAIR
                handValue = 2;
        else if(((match1 == 1 && match2 == 0) || (match2 == 1 && match1 == 0)) && jackOrBetter == true)    //1 PAIR, jack or better
                handValue = 1;
        else
               handValue = 0;						//LOSING HAND
	
	return handValue;	//Return handValue as multiplier for winnings
}//end handValue()
