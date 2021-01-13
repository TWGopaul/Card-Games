//Programmer: Travis Gopaul
//Date: 12/7/20
//BlackJack.cpp
//Member definitions for BlackJack class

#include "BlackJack.h"
#include "Card.h"
#include <iostream>
using namespace std;

//***************** Private Members ******************
float BlackJack::seedMoney = 0.0;       //player bank

void BlackJack::dealCards()             //deals cards to player and dealer
{
	dealerHand[0] = getCard();
	dealerHand[1] = getCard();
	playerHand[0] = getCard();
	playerHand[1] = getCard();

}//end dealCards()


Acard* BlackJack::hit(Acard* hand, int &size)	//deals another card; calls resize to make more space
{
	hand = resizeHand(hand, size);		//call resizeHand to add space in array for another card
	hand[size-1] = getCard();		//get another card from the deck and assign it to the new space made in array
	return hand;				//return pointer to new hand
}//end hit()


Acard* BlackJack::resizeHand(Acard* hand, int &size)      //resizes hand array when hit() is called
{
	Acard *temp;				//pointer to hold location of original array

	Acard *copy;				//copy array to store new array
	copy = new Acard[size + 1];		//temp array has 1 more space to hold another card

	for(int i = 0; i < size; i++)		//copy original array onto copy array
	{
		copy[i] = hand[i];
	}//end for

	temp = hand;				//temp hold adress of hand	
	hand = copy;				//set hand adress to the new array

	size += 1;				//increase size of array by 1 to allow for another card to be drawn
	delete[] temp;				//delete the temp pointer(old adress)
	temp = nullptr;

	return hand;                            //return hand w/ new address

}//end resizeHand()


bool BlackJack::isBlackJack(Acard* hand)
{
	if(((hand[0].num == 14) && (hand[1].num > 9 && hand[1].num != 14)) || ((hand[0].num > 9 && hand[0].num != 14) && (hand[1].num == 14)))    //if player has Black Jack
                {       
			isBlackJackHand = true;			
                }//end if
	else
		isBlackJackHand = false;
	return isBlackJackHand;		//return true if black jack, false if not 
}//end isBlackJack

int BlackJack::handValue(Acard* hand, int size)     //calculates hand value
{
	int total = 0, totalIfAce = 0;		//one variable for if ace = 11 and one for ace = 1
	int value = 0;				//variable to return

	for(int i = 0; i < size; i++)		//iterate through hand values
	{
		if(hand[i].num == 11 || hand[i].num == 12 || hand[i].num == 13)	//if a face card
		{
			total += 10;		//add 10
			totalIfAce += 10;	//add 10
		}//end if
		else if(hand[i].num == 14)		//if ace
		{	
			total += 11;		//add 11		
			totalIfAce += 1;	//add 1
		}//end else if
		else if(hand[i].num <= 10)				//if any other card
		{
			total += hand[i].num;		//add card value
			totalIfAce += hand[i].num;	//add card value
		}//end else
	}//end for
	
	if(total <= 21)			//if total using ace = 11 is < 21 return total
		value = total;
	else if(total > 21 && totalIfAce <= 21)	//if total using ace = 11 bust, return totalIfAce = 1
		value = totalIfAce;
	else if(total > 21 && totalIfAce > 21)
		value = total;

	return total;
}//end handValue()


void BlackJack::printBank()			//display bank info
{
	cout << "Your balance was: $" << seedMoney << endl;
	cout << "You won: $" << winnings << endl;
	seedMoney += winnings;			//add winnings to balance
	cout << "Your current balance is: $" << seedMoney << endl;
}//end printBank


void BlackJack::resetHand()			//reset hands to 2 card arrays
{
	pHandSize = 2;			//reset hand size
	dHandSize = 2;			

	Acard *tempP;			//temp pointers for player and dealer
	Acard *tempD;
	
	Acard* copyP;			//pointers to hold old adress of hands
	Acard* copyD;

	tempP = new Acard[pHandSize];	//set to point to neww 2 card arrays
	tempD = new Acard[dHandSize];

	copyP = playerHand;		//set copies to point to old adresses
	copyD = dealerHand;

	playerHand = tempP;		//set hands to new adresses
	dealerHand = tempD;

	delete copyP;			//delete old adresses
	delete copyD;
	copyP = nullptr;		//set variables to nullptr
	copyD = nullptr;
}//end resetHand()
//**************** Public Members *******************

BlackJack::BlackJack()	//constructor
{
	reward = 1.5;           //1.5x bet amount if player wins

	dHandSize = 2;		//set initial dealer hand size
	pHandSize = 2;		//set initial player hand size

	dealerHand = new Acard[dHandSize];	//create dynamic array of Acard's for dealer
	playerHand = new Acard[pHandSize];	//create dynamic array of Acard's for player
}//end BlackJack()


BlackJack::~BlackJack()		//destructor
{
	delete[] playerHand;	//delete player hand
	delete[] dealerHand;	//delete dealer hand
}//end destructor
void BlackJack::playGame()	//function to run BlackJack game
{
	system("clear");

	char play, hitMe, ins;		//variables for menu selections
	bool hasIns;			//bool variable for insurance

	cout << "Welcome to the Black Jack table!" << endl;
	cout << "Enter your bank roll amount: $" ;	//get seedMoney from user input
	cin >> seedMoney;
do                                      //keep playing until user decides to stop
{
	bet = 0.0;                      //set initial values for beginning of each hand
	insurance = 0.0;
	winnings = 0.0;
	isBlackJackHand = false;        //initialize variable to false; used in isBlackJack() to determine if hand is black jack
	hasIns = false;

        cout << "Would you like to play? (Y/N): ";
        cin >> play;
        while(play != 'y' && play != 'Y' && play != 'n' && play != 'N') //input validation
        {
                 cout << "Please make valid selection (Y/N) : ";
                 cin >> play;
        }//end while

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
		seedMoney -= bet;                       //subtract bet amount from seed money;

		shuffleCard();                          //function from Card class; shuffles deck of cards
		dealCards();				//call dealCards() to deal cards to player and dealer
		
		cout << "Dealer showing: " << endl;
		cout << "============== " << endl;
		printCards(dealerHand, 1);		//show 1 card from the dealer
		cout << "Player showing: " << endl;
		cout << "============== " << endl;
		printCards(playerHand, 2);		//show both player cards

		if(isBlackJack(playerHand))    //if player has Black Jack
                {       
			cout << "Dealer showing: " << endl;
	                cout << "============== " << endl;
			printCards(dealerHand,dHandSize);	//show dealer hand
			
			if(isBlackJack(dealerHand))		//if dealer has black jack also
			{
				cout << "Dealer showing Black Jack as well. Stand off!" << endl;
				winnings = bet;		//player gets money back
			}//end if
			else					//if dealer does not have black jack, player wins
			{
				cout << "Black Jack!!! Congrats, you win!" << endl;
				winnings = bet * reward;	//calculate winnings	
			}//end else
		}//end if

		else				//if player does not have black jack
		{
			if(dealerHand[0].num == 14)		//if dealer showing ace
			{
				cout << "Dealer is showing an ace, would you like insurance? (Y/N): " << endl;
				cin >> ins;
				if(ins == 'y' || ins == 'Y')
				{
					insurance = (.5 * bet);
					
					if(insurance > seedMoney)		//check if enough funds for insurance
						cout << "Not enough money for insurance!" << endl;
					else					//if there is
					{	
					seedMoney -= insurance;			//take insurance out of seed Money
					hasIns = true;				//set hasIns to true
					}
				}//end if
			}//end if
			
			while((handValue(playerHand, pHandSize) < 21))	//while hand value is < 21, ask player if they want to hit
			{
				cout << "Would you like to hit or stay? (H/S) : ";
				cin >> hitMe;
				if(hitMe == 'h' || hitMe == 'H')
				{
					playerHand = hit(playerHand, pHandSize);
					printCards(playerHand, pHandSize);
				}//end if
				else if(hitMe == 's' || hitMe == 'S')
					break;
			}//end while

			if(handValue(playerHand, pHandSize) > 21)			//if player goes over 21 they bust
			{
				cout << "Sorry, you bust!" << endl;
			}
			else
			{
				cout << "Dealer showing: " << endl;
                		cout << "============== " << endl;

				printCards(dealerHand, dHandSize);			//show dealer hand
			
				if(isBlackJack(dealerHand))             //if dealer has black jack; player does not - already checked on line 171
                		{
                			if(hasIns)			//if player bought insurance
					{
						cout << "Your insurance pays: $" << bet << endl;
						winnings = bet;	//add insurance back to seedMoney
					}//end if

					else				//else display dealer wins
					cout << "Dealer wins!" << endl;
				}//end if
				
				while((handValue(dealerHand, dHandSize) < 16) && (handValue(dealerHand, dHandSize) <= 21))	//while dealer has less than 16 they must hit
				{
					dealerHand = hit(dealerHand, dHandSize);	//dealer hits
					printCards(dealerHand, dHandSize);		//show dealer hand
					int dealer = handValue(dealerHand, dHandSize);
					cout << "Dealer has: " << dealer << endl;

				}//end while

				if(handValue(dealerHand, dHandSize) > 21)		//if dealer busts
				{
					cout << "Dealer bust! You win!" << endl;
					winnings = bet * reward;	//calculate winnings
				}//end if
				else if(handValue(playerHand, pHandSize) > handValue(dealerHand, dHandSize))
				{
					cout << "You win!" << endl;
					winnings = bet * reward;	//calculate winnings
				}//end else if
				else if(handValue(dealerHand, dHandSize) > handValue(playerHand, pHandSize))	//if dealer hand is higher value than player hand
					cout << "Dealer wins!" << endl;
				else if(handValue(playerHand, pHandSize) == handValue(dealerHand, dHandSize))	//if hands are equal value
				{
					cout << "Stand off!" << endl;
					winnings = bet;	//player gets money back
				}//end else if				

			}//end else
				
        	}//end else
	
		printBank();                            //display seedMoney info

                if(seedMoney <= 0)                      //if no money left display message and quit
                {
                        cout << "Sorry, you've lost all your money! The house always wins!" << endl;
                        break;
                }//end if

		resetHand();				//reset hands to new 2 card arrays
		resetDeck();				//function from Card class; reset nextCard to 0;
	}//end if
}//end do
while (play != 'n' && play != 'N');             //keep playing until user decides to stop

}//end playGame()

