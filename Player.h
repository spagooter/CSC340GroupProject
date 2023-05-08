//
// Created by jimmi on 5/5/2023.
//

#ifndef CSC340GROUPPROJECT_PLAYER_H
#define CSC340GROUPPROJECT_PLAYER_H

#include <iostream>
#include <string>
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

    void setPlayerName(){
        cout << "Enter player's name: " << endl;
        string str;
        cin >> str;
        cout << "str: " << str << endl;
        //cout << "input name: " << str << endl;
        this->playerName = str;
    }
    void setPlayerName(string name){this->playerName = name;}
    void setNumCards(int num){this->numCards = num;}
    void setCardsValue(int num){this->cardsValue = this->cardsValue + num;}
    void setNumPlayers(int num){this->numPlayers = num;}
    void setCashRemaining(int num){this->cashRemaining = num;}
    void setCashRemaining(){
        cout << "Buy in amount: " << endl;
        int bet;
        cin >> bet;
        this->cashRemaining = bet;
    }

    //void hit();
    //void stand();

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
            cout << "for loop: " << i << endl;
            //cout << "Enter player" << i << "'s name:" << endl;
            //string name;
            //getline(cin, name);
            person->setPlayerName();

            //cout << "Buy in amount: " << endl;
            //int bet;
            //cin >> bet;
            person->setCashRemaining();

            Players.addNode(*person);
        }//end for loop
    }// end addPlayer

    void printPlayer(){
        Node<Player>* curr;
        curr = Players.begin();
        for(int i = 0; i < numPlayers; i++) {
            cout << "Player name: " << curr->getVal().getPlayerName() << endl;
            cout << "Player bet: " << curr->getVal().getCashRemaining() << endl;
            curr = curr->getNextNode();
        }
    }


}; //end Player class


#endif //CSC340GROUPPROJECT_PLAYER_H
