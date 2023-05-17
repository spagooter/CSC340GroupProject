#include "BlackJack.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
  Player* player1 = new Player("bob", 1337);
  Card* card1 = new Card("Spades", 1);
  Card* card2 = new Card("Diamonds", 10);
  player1->print();
  player1->Hand->addCard(*card1);
  player1->Hand->addCard(*card2);
  player1->Hand->Cards->remove(*card1);
  player1->updateCardsValue();
  cout << player1->getCardsValue();
}
