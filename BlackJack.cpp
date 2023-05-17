//
// Created by donny on 5/10/23.
//
////////////////////////////
/* Card Member Functions */
//////////////////////////
#include "BlackJack.h"
#include <cstdlib>
#include <ctime>

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

Card& Card::operator=(const Card& rhs){
  this->suit = rhs.suit;
  this->symbol = rhs.symbol;
  this->value = rhs.value;
  return *this;
}

void Card::print() {
  cout << symbol << " of " << suit << endl;
}

///////////////////////////
/* Deck Class Functions */
/////////////////////////
//this function adds a single card (for cheating)
void Deck::addCard(Card card) {
  this->Cards->addNode(card);
}

//this function shuffles the deck
void Deck::shuffle() {
  int outerLoop = this->Cards->size();  //outer loop loops for every card in the deck
  int innerLoop = outerLoop - 1; //inner loop is a dummy variable that keeps track of the size of the unshuffled portion
  auto iter1 = this->Cards->begin();  //iter1 is the current card to be swapped
  int randIndex;  //a random index within the unshuffled portion
  Node<Card>* iter2;  //iter2 is incremented randIndex number of times, within the current unshuffled portion
  srand(time(0));

  for (int i = 0; i < outerLoop; ++i) {   //for every card in the deck,
    if (iter1 == this->Cards->end()) {  //when iter reaches the end, deck is shuffled
      //cout << "Shuffled!" << endl;
      return;
    }
    randIndex = rand() % innerLoop;
    iter2 = iter1->getNextNode();
    for (int j = 0; j < randIndex; ++j) {
      if (iter2 == nullptr) {
        cout << "out of bounds";
        return;
      }
      else
        iter2 = iter2->getNextNode();
    }
    this->Cards->swap(iter1, iter2);
    iter1 = iter1->getNextNode();
    --innerLoop;
  }
}

//default deck constructor
Deck::Deck() {
  Cards = new linkedList<Card>();
}

//deck constructor that takes a string, any string, and constructs a standard deck;
Deck::Deck(string standard) {                                             //declare linked list of cards
  Card *card;
  for (string suit: suits) {          //for each suit
    for (int i = 1; i <= 13; i++) {   //for each number
      card = new Card(suit, i);
      Cards->addNode(*card);     //add card to deck
    }
  }
}

//deck constructor that inintializes a shoe with multiple decks
Deck::Deck(string shoe, int numOfDecks) {
  Card* card;
  for (int i = 0; i < numOfDecks; i++) {
    for (string suit : suits) {
      for (int i = 1; i <= 13; i++) {   //for each number
        card = new Card(suit, i);
        Cards->addNode(*card);     //add card to deck
      }
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
  cout << "size: " << this->Cards->size();
}

Card Deck::getTopCard(){
    Card top;
    Node<Card> *curr = Cards->begin();
    top = curr->getVal();
    //top = Cards->begin();
    return top;
}

///////////////////////////
/* Player Class Functions */
/////////////////////////

Player::Player(string name, int cashRemaining) {
  this->playerName = name;
  this->cashRemaining = cashRemaining;
  this->Hand = new Deck();
}

Player::Player() {
    playerName = "";
    cardsValue = 0;
    Hand = new Deck();
}

string Player::getPlayerName() { return this->playerName; }
int Player::getNumCards() { return this->Hand->size(); }
int Player::getCardsValue() {
  if (this->Hand->size() == 0)
    this->cardsValue = 0;

  return this->cardsValue;
}
int Player::getCashRemaining() { return this->cashRemaining; }

void Player::setPlayerName(int i) {
    cout << "Enter Player" << i << "'s name: ";
    string str;
    cin >> str;
    this->playerName = str;
}
void Player::setPlayerName(string name) { this->playerName = name; }
void Player::setCashRemaining(int num) { this->cashRemaining = num; }
void Player::setCashRemaining() {
    cout << "Buy in amount: ";
    int bet;
    cin >> bet;
    this->cashRemaining = bet;
}
void Player::updateCardsValue() {
  int sum = 0;
  auto iter = this->Hand->Cards->begin();
  while (iter != nullptr) {
    sum += iter->getVal().getValue();
    iter = iter->getNextNode();
  }
  if (this->Hand->Cards->end()->getVal().getSymbol() == "A" && sum > 21) {
    this->Hand->Cards->end()->getVal().setValue(1);
    sum -= 10;
  }
  this->cardsValue = sum;
}

void Player::print() {
  cout << "Name: " << this->playerName << ", Cash Remaining: $" << this->cashRemaining << endl;
}

///////////////////////////
/* Game Class Functions */
/////////////////////////
Game::Game(){
    dealer = new Dealer("Dealer", 999999);
    PlayerList = new linkedList<Player>;

}

void Game::loadGame() {
    //Deck *deckPtr = new Deck("standard");
    //deckPtr->shuffle();
    //deckPtr->print();
    PlayerList = new linkedList<Player>();
    int num;
    cout << "Welcome to our BlackJack table." << endl;
    cout << endl << "Enter number of players: (max 5)" << endl;
    cin >> num;
    numPlayers = num;
    cout << "Number of players: " << numPlayers << endl;
    addDealer();
    addPlayer();
}

void Game::addDealer(){
    Player *person = new Player;
    person->setPlayerName("Dealer");
    person->setCashRemaining(10000000);     //ten million dollars
    cout <<  "\nDealer: Hello my name is Bob. Welcome to my table.\n\nWhat are your names?" << endl;
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
    printPlayer();
}// end addPlayer

void Game::printPlayer(){
    Node<Player>* curr;
    curr = PlayerList->begin()->getNextNode();      //bypass dealer
    cout << "***************************************************" << endl;
    for(int i = 0; i < PlayerList->size()-1; i++) {
        cout << "Player Name: " << curr->getVal().getPlayerName();
        cout << " Bet:  " << curr->getVal().getCashRemaining() << endl;
        curr = curr->getNextNode();
    }
    cout << "Dealer: Buy in complete. Good Luck." << endl;

    cout << "***************************************************\n" << endl;

}//end printPlayer()

void Game::optionsMenu() {
    bool endGame = false;
    bool cardsDealt = false;
    Dealer *Bob = new Dealer("bob", 999999);
    int num;
    do{
        cout << "Please choose an option from the game menu: " << endl;
        cout << "Option 0: End the Game" << endl;
        cout << "Option 1: Deal the cards" << endl;
        cout << "Option 2: Hit" << endl;
        cout << "Option 3: Stay" << endl;
        cin >> num;
        switch(num){
            case 0:
                cout << "End game. Thank you for playing." << endl;
                endGame = true;
                break;
            case 1:
                cout << "Dealing cards...\n" << endl;
                if(cardsDealt == false){
                    //Bob->dealCard();          //card object from top of deck
                    cardsDealt = true;
                }else{
                    cout << "Cards have already been dealt" << endl;
                }
                break;
            case 2:
                cout << "Hit\n" << endl;      //hit
                break;
            case 3:
                cout << "Stay\n" << endl;      //stay
                break;
        }// end switch
    }while(endGame != true);
}// end optionsMenu

//void Game::setNumPlayers(int num) {
//    this->numPlayers = num;
//}
void Game::addMoney(string name, int num) {
  Node<Player>* curr;
  curr = PlayerList->begin();      //bypass dealer
  for(int i = 0; i < PlayerList->size(); i++) {
    if(curr->getVal().getPlayerName() == name){
      curr->getVal().setCashRemaining(curr->getVal().getCashRemaining()+num);
    }
    curr = curr->getNextNode();
  }
}
void Game::subMoney(string name, int num) {
  Node<Player>* curr;
  curr = PlayerList->begin();      //bypass dealer
  for(int i = 0; i < PlayerList->size(); i++) {
    if(curr->getVal().getPlayerName() == name){
      curr->getVal().setCashRemaining(curr->getVal().getCashRemaining()-num);
    }
    curr = curr->getNextNode();
  }
}
void Game::dealCard() {                                   //deals one card to each person first then again for a total of two.
  Node<Card> *topOfDeck = shoe->Cards->begin();                 //pointer to top of deck
  for(int i = 0; i < 2; i++){
    auto curr = PlayerList->begin();           //pointer to dealer and player
    Node<Card> *hand = shoe->Cards->begin();                   //pointer to a players hand
    for(int j = 0; i <PlayerList->size(); i++){
      cout << "top of Deck: " << topOfDeck->getVal().getSuit() << " " << topOfDeck->getVal().getSymbol() << " " << topOfDeck->getVal().getValue() << endl;

      //Hand->addNode(reference to card??);
      curr = curr->getNextNode();                     //next player
      topOfDeck = topOfDeck->getNextNode();           //next card
    }
  }
}

///////////////////////////
/* Dealer Class Functions */
/////////////////////////

Dealer::Dealer(string name, int cashRemaining) {
  this->playerName = name;
  this->cashRemaining = cashRemaining;
}