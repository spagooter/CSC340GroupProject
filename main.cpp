#include "BlackJack.h"
#include <string>
#include <iostream>

using namespace std;


// int getRandomNum(){               //generates a random num from 1-52
//
//     int num = rand() % 52 + 1;
//     return num;
//
// }

int main() {

  Game *startGame = new Game();
  startGame->loadGame();
  startGame->optionsMenu();
  //startGame->printPlayer();
  //Player* player1 = new Player;
  //player1->startingPlayerNum();
  //player1->printPlayer();
  //Deck deck("standard");
  //deck.shuffle();
  //Deck deck1("standard");
  //deck1.shuffle();
  //deck1.print();
//  cout << "hello world" << endl;
//  auto list1 = new linkedList<int>();
//  auto list2 = new linkedList<int>();
//  list1->addNode(1);
//  list1->addNode(2);
//  list1->addNode(3);
//  cout << "list1" << endl;
//  list1->print();
//  list2 = list1;
//  cout << "list2" << endl;
//  list2->print();
  return 0;
}
