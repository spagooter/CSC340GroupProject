//
// Created by donny on 5/10/23.
//
////////////////////////////
/* Card Member Functions */
//////////////////////////
#include "BlackJack.h"
Card::Card() {
  suit = " ";
  symbol = " ";
  value = 0;
}

Card::Card(std::string suit, int num) {
  this->suit = suit;
  if (num <= 10 && num >= 2) {
    symbol = to_string(num);
    value = num;
  } else if (num == 1) {
    symbol = "A";
    value = 11;             //value can be 11 or 1
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

///////////////////////////
/* Deck Class Functions */
/////////////////////////
Deck::Deck() {
  Cards = nullptr;
}

Deck::Deck(string standard) {
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

void Deck::print() {
  Node<Card> *iter = Cards->begin();
  while (iter != nullptr) {
    cout << iter->getVal().symbol << " of " << iter->getVal().suit << " " << endl;
    iter = iter->getNextNode();
  }
  cout << Cards->size();  //display the size
}