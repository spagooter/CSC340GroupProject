//
// Created by jimmi on 5/5/2023.
//

#ifndef CSC340GROUPPROJECT_PLAYER_H
#define CSC340GROUPPROJECT_PLAYER_H

#include "classes.h"


class Player{
private:
    string playerName;
    int numOfCards;
    int cardsValue;
    int numOfPlayers;
    int cashRemaining;
    //hand
    linkedList<Player> Players;

public:

    Player(){
        playerName = "";
        numOfCards = 0;
        cardsValue = 0;
        numOfPlayers = 0;
    }

    void hit();
    void stand();

    void getPlayerNum(){
        int numPlayers;
        cout << "Enter number of players: (max 5)" << endl;
        cin >> numPlayers;
        numOfPlayers = numPlayers;
        //add player names?

    }
    void addPlayer(){
        Player* person = new Player;
        for(int i = 1; i <= numOfPlayers; i++){
            cout << "Enter player" << i << "'s name:" << endl;
            getline(cin, person->playerName);

            cout << "Buy in amount: " << endl;
            cin >> person->cashRemaining;

            Players.addNode(*person);

        }

    }


};






#endif //CSC340GROUPPROJECT_PLAYER_H
