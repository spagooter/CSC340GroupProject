//
// Created by donny on 5/5/23.
//

#ifndef CSC340GROUPPROJECT_BLACKJACK_H
#define CSC340GROUPPROJECT_BLACKJACK_H
#include "classes.h"

class Card{
    friend class Deck;
private:
    string suit;
    string symbol;
    int value;
public:
    Card(){
      suit = " ";
      symbol = " ";
      value = 0;
    }

    Card(string suit, int num){
      this->suit = suit;
      if (num <= 10 && num >= 2){
        symbol = to_string(num);
        value = num;
      }
      else if (num == 1){
        symbol = "A";
        value = 11;
      }
      else if (num == 11){
        symbol = "J";
        value = 10;
      }
      else if (num == 12){
        symbol = "Q";
        value = 10;
      }
      else if (num == 13){
        symbol = "K";
        value = 10;
      }
      else{
        cout << "Invalid card number (1-13)" << endl;
      }
    }
};

class Deck {
private:
    int count;
    linkedList<Card>* Cards;
public:
    Deck(){
      count = 0;
      Cards = nullptr;
    }

    Deck(string standard){
      Cards = new linkedList<Card>();
      count = 52;
      string suits[4] = {"Spades","Clubs", "Diamonds", "Hearts"};
      Card* card;
      for (string suit : suits){
        for (int i = 0; i <= 13; i++){
          card = new Card(suit, i);
          Cards->addNode(*card);
        }
      }
    }

    void print(){
      Node<Card>* iter = Cards->begin();
      while (iter != nullptr){
        cout << iter->getVal().value << " ";
        iter = iter->getNextNode();
      }
    }
};

#endif //CSC340GROUPPROJECT_BLACKJACK_H
