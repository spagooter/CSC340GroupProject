//
// Created by donny on 5/10/23.
//
////////////////////////////
/* Card Member Functions */
//////////////////////////
#include "BlackJack.h"
Card::Card() {
  //card class has suit, symbol, and value
  suit = " ";
  symbol = " ";
  value = 0;
}

//this card constructor takes a suit and a num, other values are inferred
Card::Card(std::string suit, int num) {
  this->suit = suit;
  if (num <= 10 && num >= 2) {
    symbol = to_string(num);
    value = num;
  } else if (num == 1) {
    symbol = "A";
    value = 11;             //value can be 11 or 1
  } else if (num == 11) {
    symbol = "J";
    value = 10;
  } else if (num == 12) {
    symbol = "Q";
    value = 10;
  } else if (num == 13) {
    symbol = "K";
    value = 10;
  } else {
    cout << "Invalid card number (1-13)" << endl;
  }
}

//operator overload for equivalence operator
bool Card::operator==(Card& rhs){
  return (this->symbol == rhs.symbol && this->suit == rhs.suit);
}

///////////////////////////
/* Deck Class Functions */
/////////////////////////
//this function adds a single card (for cheating)
void Deck::addCard(Card card) {
  this->Cards->addNode(card);
}

//this function shuffles the deck
/*void Deck::shuffle() {
  int newDeckSize = this->Cards->size();
  int randIndex;
  Deck* newDeck = new Deck();
  auto iter = this->Cards->begin();
  for (int i = 0; i < newDeckSize; ++i) {
    randIndex = rand() % this->Cards->size() + 1;
    for (int j = 0; j < randIndex; ++j) {
      iter = iter->getNextNode();
    }
    newDeck->Cards->addNode(iter->getVal());
    this->Cards->removeNode(iter);
  }
  *(this->Cards) = *(newDeck->Cards);
  delete newDeck;
}*/

//default deck constructor
Deck::Deck() {
  Cards = new linkedList<Card>();
}

//deck constructor that takes a string, any string, and constructs a standard deck;
Deck::Deck(string standard) {
  Cards = new linkedList<Card>();                                               //declare linked list of cards
  string suits[4] = {"Spades", "Clubs", "Diamonds", "Hearts"};  //declare an array to hold the suits
  Card *card;
  for (string suit: suits) {          //for each suit
    for (int i = 1; i <= 13; i++) {   //for each number
      card = new Card(suit, i);
      Cards->addNode(*card);     //add card to deck
    }
  }
}

//this function prints the deck
void Deck::print() {
  Node<Card> *iter = Cards->begin();
  while (iter != nullptr) {
    cout << iter->getVal().symbol << " of " << iter->getVal().suit << " " << endl;
    iter = iter->getNextNode();
  }
  cout << Cards->size();  //display the size
}

///////////////////////////
/* Player Class Functions */
/////////////////////////

Player::Player() {
    playerName = "";
    numCards = 0;
    cardsValue = 0;
    Hand = nullptr;
}

string Player::getPlayerName() { return this->playerName; }
int Player::getNumCards() { return this->numCards; }
int Player::getCardsValue() { return this->cardsValue; }
int Player::getCashRemaining() { return this->cashRemaining; }

void Player::setPlayerName(int i) {
    cout << "Enter Player" << i << "'s name: " << endl;
    string str;
    cin >> str;
    this->playerName = str;
}
void Player::setPlayerName(string name) { this->playerName = name; }
void Player::setNumCards(int num) { this->numCards = num; }
void Player::setCardsValue(int num) { this->cardsValue = this->cardsValue + num; }
void Player::setCashRemaining(int num) { this->cashRemaining = num; }
void Player::setCashRemaining() {
    cout << "Buy in amount: " << endl;
    int bet;
    cin >> bet;
    this->cashRemaining = bet;
}

///////////////////////////
/* Game Class Functions */
/////////////////////////
Game::Game(){
    PlayerList = nullptr;
}

void Game::startingPlayerNum() {
    PlayerList = new linkedList<Player>();
    int num;
    cout << endl << "Enter number of players: (max 5)" << endl;
    cin >> num;
    cout << "Number of players: " << PlayerList->size() << endl;
    addDealer();
    addPlayer();
}

void Game::addDealer(){
    Player *person = new Player;
    person->setPlayerName("Dealer");
    person->setCashRemaining(10000000);     //ten million dollars
    cout <<  "\nDealer: Hello my name is Bob. Welcome to my table.\n\nWhat are your names? \n" << endl;
    //cout << "Dealer: " << person->getPlayerName() << " cash remaining: " << person->getCashRemaining() << endl;
    PlayerList->addNode(*person);
}

void Game::addPlayer(){
    Player *person = new Player;
    for(int i = 1; i <= PlayerList->size(); i++){

        char correct = false;
        while(correct != true) {                    //allows user to correct name and buy in amount
            person->setPlayerName(i);
            person->setCashRemaining();
            cout << "Player name: " << person->getPlayerName() << " Player bet: " << person->getCashRemaining() << endl;
            cout << "Is this correct? Y/N" << endl;
            cin >> correct;
            if (correct == 'Y' || correct == 'y') {
                PlayerList->addNode(*person);
                correct = true;
            } else {
                cout << "Please enter the correct info." << endl;
            }
        }//end while
    }//end for loop
}// end addPlayer

void Game::printPlayer(){
    Node<Player>* curr;
    curr = PlayerList->begin()->getNextNode();      //bypass dealer
    for(int i = 0; i < PlayerList->size(); i++) {
        cout << "Player Name: " << curr->getVal().getPlayerName()<< endl;
        cout << "Player Bet:  " << curr->getVal().getCashRemaining() << endl;
        curr = curr->getNextNode();
    }
    cout << "Dealer: Buy in complete. Good Luck." << endl;
}//end printPlayer()

///////////////////////////
/* Dealer Class Functions */
/////////////////////////
void Dealer::addMoney(string name, int num) {
    Node<Player>* curr;
    curr = PlayerList->begin();      //bypass dealer
    for(int i = 0; i < PlayerList->size(); i++) {
        if(curr->getVal().getPlayerName() == name){
            curr->getVal().setCashRemaining(curr->getVal().getCashRemaining()+num);
        }
        curr = curr->getNextNode();
    }
}
void Dealer::subMoney(string name, int num) {
    Node<Player>* curr;
    curr = PlayerList->begin();      //bypass dealer
    for(int i = 0; i < PlayerList->size(); i++) {
        if(curr->getVal().getPlayerName() == name){
            curr->getVal().setCashRemaining(curr->getVal().getCashRemaining()-num);
        }
        curr = curr->getNextNode();
    }
}