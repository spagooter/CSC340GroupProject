#include "BlackJack.h"
#include "Player.h"
#include <string>
#include <iostream>

using namespace std;

 void startGame(){
     bool endGame = false;
     int num;
     cout << "Welcome to our BlackJack table." << endl;
     Deck *deckPtr = new Deck("standard");
     Player* player1 = new Player;

     //deckPtr->print();
     player1->startingPlayerNum();
     player1->printPlayer();
     cout << "Please choose an option from the game menu: " << endl;
     cout << "Game Menu:" << endl;
     cout << "Option 0: case 0" << endl;
     cout << "Option 1: case 1" << endl;
     cout << "Option 2: case 2" << endl;
     cout << "Option 3: case 3" << endl;
     cin >> num;
     while(endGame != true){
         cout << "Game Menu:" << endl;
         cout << "Option 0: case 0" << endl;
         cout << "Option 1: case 1" << endl;
         cout << "Option 2: case 2" << endl;
         cout << "Option 3: case 3" << endl;

         switch(num){
             case 0:
                 cout << "case 0" << endl;      //deal cards
                 break;
             case 1:
                 cout << "case 1" << endl;      //hit
                 break;
             case 2:
                 cout << "case 2" << endl;      //stand
                 break;
             case 3:
                 cout << "End game. Thank you for playing." << endl;
                 endGame = true;
                 break;
         }

     }
 }
 int getRandomNum(){               //generates a random num from 1-52

     int num = rand() % 52 + 1;
     return num;

 }

int main() {
    //cout << getRandomNum() << endl;
     startGame();
  //Deck *deckPtr = new Deck("standard");
  //deckPtr->print();


  //Player* player1 = new Player;
  //player1->startingPlayerNum();
  //player1->printPlayer();
  return 0;
}
