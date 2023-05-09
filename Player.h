//
// Created by jimmi on 5/5/2023.
//

#ifndef CSC340GROUPPROJECT_PLAYER_H
#define CSC340GROUPPROJECT_PLAYER_H

#include "classes.h"

class Person{
    friend class Player;
private:
    string playerName;
    int numCards;
    int cardsValue;
    int numPlayers;
    int cashRemaining;

    linkedList<Card> *Hand;             //linked list of cards
public:


    Person(){
        playerName = "";
        numCards = 0;
        cardsValue = 0;
        numPlayers = 0;
        Hand = nullptr;
    }
    //************************** getters *********************************
    string getPlayerName(){return this->playerName;}
    int getNumCards(){return this->numCards;}
    int getCardsValue(){return this->cardsValue;}
    int getPlayerNum(){return this->numPlayers;}
    int getCashRemaining(){return this->cashRemaining;}

    //************************** setters *********************************
    void setPlayerName(int i){
        cout << "Enter Player" << i << "'s name: " << endl;
        string str;
        cin >> str;
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
    //****************************** add money (win) ***************************************
    void addMoney(int num){
        int addCash = this->getCashRemaining() + num;
        this->setCashRemaining(addCash);
    }

    //****************************** subtract money (lose) *********************************
    void subMoney(int num){
        int subMoney = this->getCashRemaining() - num;
        this->setCashRemaining(subMoney);
    }

    //void hit();
    //void stand();

    //****************************** get number of players****************************
    void startingPlayerNum(){
        int num;
        cout << endl << "Enter number of players: (max 5)" << endl;
        cin >> num;
        setNumPlayers(num);
        cout << "Number of players: " << getPlayerNum() << endl;
        //addDealer();
        //addPlayer();
    }


class Player{
private:
    linkedList<Person> *PlayerList;             //linked list of cards

public:
    Player() {
    PlayerList = nullptr;
    }

    //***************************** add dealer to linked list**************************
    void addDealer(){
        PlayerList = new linkedList<Person>();
        Player* person = new Player;
        //person->setPlayerName("Dealer");
        //person->setCashRemaining(10000000);     //ten million dollars
        cout <<  "\nDealer: Hello my name is Bob. Welcome to my table.\n\nWhat are your names? \n" << endl;
        //cout << "Dealer: " << person->getPlayerName() << " cash remaining: " << person->getCashRemaining() << endl;
        PlayerList->addNode(*person);
    }

    //***************************** add player to linked list **************************
    void addPlayer(){
        PlayerList = *new linkedList<Player>();
        Player* person = new Player;

        for(int i = 1; i <= numPlayers; i++){

            char correct = false;
            while(correct != true) {                    //allows user to correct name and buy in amount
                person->setPlayerName(i);
                person->setCashRemaining();
                cout << "Player name: " << person->getPlayerName() << " Player bet: " << person->getCashRemaining() << endl;
                cout << "Is this correct? Y/N" << endl;
                cin >> correct;
                if (correct == 'Y' || correct == 'y') {
                    Players.addNode(*person);
                    correct = true;
                } else {
                    cout << "Please enter the correct info." << endl;
                }
            }//end while
        }//end for loop
    }// end addPlayer

    //******************************* print players *******************************
    void printPlayer(){

        Node<Player>* curr;
        curr = PlayerList.begin();
        for(int i = 0; i < numPlayers; i++) {
            cout << "Player Name: " << curr->getVal().getPlayerName()<< endl;
            cout << "Player Bet:  " << curr->getVal().getCashRemaining() << endl;
            curr = curr->getNextNode();
        }
        cout << "Dealer: Buy in complete. Dealing cards. Good Luck." << endl;
    }//end printPlayer()
};
    //end Player class


#endif //CSC340GROUPPROJECT_PLAYER_H
