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
    Card& operator=(const Card& rhs);
    void print();
};

/////////////////
/* Deck Class */
///////////////
class Deck {
private:
    const string suits[4] = {"Spades", "Clubs", "Diamonds", "Hearts"};  //declare an array to hold the suits
    linkedList<Card> *Cards = nullptr;  //deck has a linked list of cards
public:
    Deck();                   //default constructor
    Deck(string standard);    //this constructor takes a string and initializes a standard deck.
    void print();             //this function prints the deck in the form of "ace of spades, 2 of spades,..."
    void shuffle();
    void addCard(Card card);
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
protected:
    linkedList<Card> *Hand; //linked list of cards
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
class Game: Deck{                               //inherits from deck class
protected:
    linkedList<Player> *PlayerList;             //linked list of cards
    int numPlayers;                             //needed for forloop to add players while LL size is 0.
public:
    Game();                                     //default constructor
    void loadGame();
    void addDealer();
    void addPlayer();
    void printPlayer();
    void optionsMenu();
//    void setNumPlayers(int num);
};//end Player class

/////////////////
/* Dealer Class */
///////////////
class Dealer: Game, Player{
private:
    void addMoney(string name, int num);
    void subMoney(string name, int num);
    void dealCard(/* card from top of deck*/);
public:

};




#endif //CSC340GROUPPROJECT_BLACKJACK_H
