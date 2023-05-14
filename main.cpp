#include "BlackJack.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
  Deck deck1("standard");
  deck1.shuffle();
  deck1.print();
}
