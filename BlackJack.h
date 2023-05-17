//
// Created by donny on 5/5/23.
//

#ifndef CSC340GROUPPROJECT_BLACKJACK_H
#define CSC340GROUPPROJECT_BLACKJACK_H

#include "LinkedList.h"



/////////////////
/* Card Class */
///////////////
class Card {
    friend class Deck;            //deck is a friend class, so it can access class members
    friend class Game;
    friend class Dealer;
    friend class Player;

private:
    //cards have a suit (ace), symbol (spade), and value (11)
    string suit;
    string symbol;
    int value;
public:
    Card();                       //default constructor
    Card(string suit, int num);   //this constructor takes a suit and a num, other attributes are inferred
    bool operator==(Card& rhs);
    Card& operator=(const Card& rhs);
    friend ostream& operator<<(ostream &os, const Card& card);
    void print();
    string getSuit(){return this->suit;}
    string getSymbol(){return this->symbol;}
    int getValue(){return this->value;}

    void setSuit(string suit){ this->suit = suit;}
    void setSymbol(string symbol){this->symbol = symbol;}
    void setValue(int newVal) {this->value = newVal;}
};

/////////////////
/* Deck Class */
///////////////
class Deck {
    friend class Player;
    friend class Dealer;
    friend class Game;
private:
    const string suits[4] = {"Spades", "Clubs", "Diamonds", "Hearts"};  //declare an array to hold the suits
protected:
    linkedList<Card> *Cards;  //deck has a linked list of cards
public:
    Deck();                   //default constructor
    Deck(string standard);    //this constructor takes a string and initializes a standard deck.
    Deck(string shoe, int numOfDecks);
    void print();             //this function prints the deck in the form of "ace of spades, 2 of spades,..."
    void shuffle();
    void addCard(Card card);
    Card getTopCard();
    int size() { return this->Cards->size(); }

};

/////////////////
/* Player Class */
///////////////
class Player {
    friend class Deck;
protected:
    string playerName;      //player name
    int cardsValue;         //total value of cards in hand
    int cashRemaining;      //amount of money the player has
    Deck *Hand; //linked list of cards
public:
    /* constructors */
    Player();
    Player(string name, int cashRemaining);
    //************************** getters *********************************
    string getPlayerName();
    int getNumCards();
    int getCardsValue();
    int getCashRemaining();

    //************************** setters *********************************
    void setPlayerName(int i);
    void setPlayerName(string name);
    void setNumCards(int num);
    void setCashRemaining(int num);
    void setCashRemaining();
    void updateCardsValue();
    void print();
    void printHand();
    void addCardToHand(Card card);

    //void hit();
    //void stand();
};

/////////////////
/* Dealer Class */
///////////////
class Dealer: protected Player{           //need access to PlayerList LL and Deck LL??
private:
public:
    Dealer(string name, int cashRemaining);
};

/////////////////
/* Game Class */
///////////////
class Game{                               //inherits from deck class
    friend class Dealer;
protected:
    Dealer* dealer = nullptr;                       //this will be the dealer for the game
    linkedList<Player> *PlayerList = nullptr;       //linked list of cards                      //needed for forloop to add players while LL size is 0.
    Deck* shoe = nullptr;                           //this is where we draw cards from
    Deck* shoe2 = nullptr;                          //this is where the cards go to
public:
    Game();                               //default constructor
    void loadGame();
    void addDealer();
    void addPlayer();
    void printPlayer();
    void optionsMenu();
    void addMoney(string name, int num);
    void subMoney(string name, int num);
    void dealCard();
//    void setNumPlayers(int num);
};//end Player class





#endif //CSC340GROUPPROJECT_BLACKJACK_H
