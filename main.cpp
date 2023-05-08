#include "BlackJack.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

 void startGame(){
     cout << "Welcome to our BlackJack table." << endl;
     Deck *deckPtr = new Deck("standard");
     Player* player1 = new Player;

     //deckPtr->print();
     player1->startingPlayerNum();
     player1->printPlayer();
 }

int main() {

     startGame();
  //Deck *deckPtr = new Deck("standard");
  //deckPtr->print();


  //Player* player1 = new Player;
  //player1->startingPlayerNum();
  //player1->printPlayer();
  return 0;
}
