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

#endif //CSC340GROUPPROJECT_BLACKJACK_H
