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
private:
    //cards have a suit (ace), symbol (spade), and value (11)
    string suit;
    string symbol;
    int value;
public:
    Card();                       //default constructor
    Card(string suit, int num);   //this constructor takes a suit and a num, other attributes are inferred
    bool operator==(Card& rhs);
};

/////////////////
/* Deck Class */
///////////////
class Deck {
private:
    linkedList<Card> *Cards;  //deck has a linked list of cards
public:
    Deck();                   //default constructor
    Deck(string standard);    //this constructor takes a string and initializes a standard deck.
    void print();             //this function prints the deck in the form of "ace of spades, 2 of spades,..."
    void shuffle();
};

/////////////////
/* Player Class */
///////////////
class Player {
private:
    string playerName;      //player name
    int numCards;           //number of cards in hand
    int cardsValue;         //total value of cards in hand
    int cashRemaining;      //amount of money the player has

    linkedList<Card> *Hand;             //linked list of cards
public:

    Player();
    //************************** getters *********************************
    string getPlayerName();
    int getNumCards();
    int getCardsValue();
    int getCashRemaining();

    //************************** setters *********************************
    void setPlayerName(int i);
    void setPlayerName(string name);
    void setNumCards(int num);
    void setCardsValue(int num);
    void setCashRemaining(int num);
    void setCashRemaining();

    //void hit();
    //void stand();
};

/////////////////
/* Game Class */
///////////////
class Game{
protected:
    linkedList<Player> *PlayerList;             //linked list of cards

public:
    Game();                                     //default constructor
    void startingPlayerNum();                   //gets number of players
    void addDealer();
    void addPlayer();
    void printPlayer();
};//end Player class

/////////////////
/* Dealer Class */
///////////////
class Dealer: Game{
private:
    void addMoney(string name, int num);

    void subMoney(string name, int num);
public:

};




#endif //CSC340GROUPPROJECT_BLACKJACK_H
