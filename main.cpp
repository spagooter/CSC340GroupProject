#include "BlackJack.h"
#include <iostream>

using namespace std;

int main() {
  Deck *deckPtr = new Deck("standard");
  deckPtr->print();

  return 0;
}
