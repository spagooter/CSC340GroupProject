//
// Created by donny on 5/5/23.
//

#ifndef CSC340GROUPPROJECT_BLACKJACK_H
#define CSC340GROUPPROJECT_BLACKJACK_H

#include "classes.h"
/////////////////
/* Card Class */
///////////////
class Card {
    friend class Deck;  //deck is a friend class, so it can access class members

private:
    //cards have a suit (ace), symbol (spade), and value (11)
    string suit;
    string symbol;
    int value;
public:
    //default constructor
    Card() {
      suit = " ";
      symbol = " ";
      value = 0;
    }

    //this constructor takes a suit and a num, other attributes are inferred
    Card(string suit, int num) {
      this->suit = suit;
      if (num <= 10 && num >= 2) {
        symbol = to_string(num);
        value = num;
      } else if (num == 1) {
        symbol = "A";
        value = 11;
      } else if (num == 11) {
        symbol = "J";
        value = 10;
      } else if (num == 12) {
        symbol = "Q";
        value = 10;
      } else if (num == 13) {
        symbol = "K";
        value = 10;
      } else {
        cout << "Invalid card number (1-13)" << endl;
      }
    }
};
/////////////////
/* Deck Class */
///////////////
class Deck {
private:
    linkedList<Card> *Cards;  //deck has a linked list of cards
public:
    //default constructor
    Deck() {
      Cards = nullptr;
    }

    //this constructor takes a string and initializes a stardard deck.
    Deck(string standard) {
      Cards = new linkedList<Card>();
      string suits[4] = {"Spades", "Clubs", "Diamonds", "Hearts"};
      Card *card;
      for (string suit: suits) {          //for each suit
        for (int i = 1; i <= 13; i++) {   //for each number
          card = new Card(suit, i);
          Cards->addNode(*card);     //add card to deck
        }
      }
    }

    //this function prints the deck in the form of "ace of spades, 2 of spades,..."
    void print() {
      Node<Card> *iter = Cards->begin();
      while (iter != nullptr) {
        cout << iter->getVal().symbol << " of " << iter->getVal().suit << " ";
      }
      cout << Cards->size();  //display the size
    }
};

#endif //CSC340GROUPPROJECT_BLACKJACK_H
