//
// Created by jimmi on 5/5/2023.
//

#ifndef CSC340GROUPPROJECT_PLAYER_H
#define CSC340GROUPPROJECT_PLAYER_H

#include "classes.h"


class Player{
private:
    string playerName;
    int numCards;
    int cardsValue;
    int numPlayers;
    int cashRemaining;
    //hand
    linkedList<Player> Players;

public:

    Player(){
        playerName = "";
        numCards = 0;
        cardsValue = 0;
        numPlayers = 0;
    }

    string getPlayerName(){return this->playerName;}
    int getNumCards(){return this->numCards;}
    int getCardsValue(){return this->cardsValue;}
    int getPlayerNum(){return this->numPlayers;}
    int getCashRemaining(){return this->cashRemaining;}

    void setPlayerName(string name){this->playerName = name;}
    void setNumCards(int num){this->numCards = num;}
    void setCardsValue(int num){this->cardsValue = this->cardsValue + num;}
    void setNumPlayers(int num){this->numPlayers = num;}

    void hit();
    void stand();

    void startingPlayerNum(){
        int num;
        cout << "Enter number of players: (max 5)" << endl;
        cin >> num;
        setNumPlayers(num);
        cout << "Number of players: " << getPlayerNum() << endl;
        addPlayer();
    }

    void addPlayer(){
        Players = *new linkedList<Player>();
        Player* person = new Player;
        for(int i = 1; i <= numPlayers; i++){

            cout << "Enter player" << i << "'s name:" << endl;
            getline(cin, person->playerName);

            cout << "Buy in amount: " << endl;
            cin >> person->cashRemaining;

            Players.addNode(*person);
        }//end for loop
    }// end addPlayer

    void printPlayer(){
        Node<Player>* curr;
        curr = Players.begin();
        for(int i = 0; i < numPlayers; i++) {
            cout << "Player: " << curr->getPlayerName() << endl;
            curr = curr->getNextNode();
        }
    }


}; //end Player class


#endif //CSC340GROUPPROJECT_PLAYER_H
