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

ostream& operator<<(ostream& os, const Card& card) {
  return (os << card.symbol << " of " << card.suit);
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
  srand(time(0));   //seed the rand() function with the current time for a good random shuffle

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
Deck::Deck(string standard) {//declare linked list of cards
  Cards = new linkedList<Card>();
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
  Cards = new linkedList<Card>();
  Card* card;
  for (int i = 0; i < numOfDecks; i++) {
    for (string suit : suits) {
      for (int j = 1; j <= 13; j++) {   //for each number
        card = new Card(suit, j);
        Cards->addNode(*card);     //add card to deck
      }
    }
  }
}

//this function prints the deck
void Deck::deckPrint() {
  Node<Card> *iter = Cards->begin();
  while (iter != nullptr) {
    cout << "[" << iter->getVal().symbol << " of " << iter->getVal().suit << "]";
    iter = iter->getNextNode();
  }
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
    //bet = 0;
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
//int Player::getBet(){return this->bet;}

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

void Player::printHand() {
    this->Hand->deckPrint();
  //updateCardsValue();
  //cout << "Value: " << cardsValue << endl;
}

void Player::addCardToHand(Card card) {
  this->Hand->addCard(card);
}

///////////////////////////
/* Game Class Functions */
/////////////////////////
Game::Game(){
    dealer = new Dealer("Dealer", 999999);
    PlayerList = new linkedList<Player>();
    shoe = new Deck("shoe", 6);
    shoe->shuffle();
    shoe2 = new Deck();

}

int Game::getBet(int arrNum) {return this->bet[arrNum];}
void Game::setBet(int arrNum, int bet) {this->bet[arrNum] = bet;}

void Game::loadGame() {
    //Deck *deckPtr = new Deck("standard");
    //deckPtr->shuffle();
    //deckPtr->print();
    //PlayerList = new linkedList<Player>();
    int num;
    cout << "Welcome to our BlackJack table." << endl;
    cout << endl << "Enter number of players: (max 5)" << endl;
    cin >> num;
    addPlayer(num);
}

//void Game::addDealer(){
//    Player *person = new Player;
//    person->setPlayerName("Dealer");
//    person->setCashRemaining(10000000);     //ten million dollars
//    cout <<  "\nDealer: Hello my name is Bob. Welcome to my table.\n\nWhat are your names?" << endl;
//    //cout << "Dealer: " << person->getPlayerName() << " cash remaining: " << person->getCashRemaining() << endl;
//    PlayerList->addNode(*person);
//}

void Game::addPlayer(int num){
    Player *person = new Player;
    for(int i = 1; i <= num; i++){

        char correct = false;
        while(correct != true) {                    //allows user to correct name and buy in amount
            person->setPlayerName(i);
            person->setCashRemaining();
            cout << "Player name: " << person->getPlayerName() << " Player buy in: " << person->getCashRemaining() << endl;
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
    curr = PlayerList->begin();      //bypass dealer
    cout << "***************************************************" << endl;
    for(int i = 0; i < PlayerList->size(); i++) {
        cout << "Player Name: " << curr->getVal().getPlayerName();
        cout << "\t Buy in: " << curr->getVal().getCashRemaining();
        cout << "\t Bet: " << getBet(i) << endl;
        if(i < PlayerList->size()-1){
            //cout << "curr->next" << endl;
            curr = curr->getNextNode();

        }

    }
    cout << "Dealer: Buy in complete. Good Luck." << endl;

    cout << "***************************************************" << endl;

}//end printPlayer()

void Game::optionsMenu() {
    bool endGame = false;
    bool betsPlaced = false;
    bool cardsDealt = false;
    Game *Bob2 = new Game();
    Dealer *Bob = new Dealer("bob", 999999);
    int num;
    do{
        if(cardsDealt == false){
            placeBets();
            betsPlaced = true;
        }
        //printPlayer();
        if(cardsDealt == true) {
            printCards(cardsDealt);
        }
        printPlayer();
        if(betsPlaced == true && cardsDealt == true){
            Node<Player> *curr = PlayerList->begin();
            for(int i = 0; i < PlayerList->size();i++){
                cout << "***************************************************" << endl;
                cout << "Player: " << curr->getVal().getPlayerName() << "'s Turn. Please select (2)Hit or (3)Stay" << endl;
                cout << "***************************************************" << endl;
                if(i < PlayerList->size()-1){
                    curr = curr->getNextNode();
                }
            }
        }
        cout << "Please choose an option from the game menu: " << endl;
        cout << "Option 0: End the Game" << endl;
        cout << "Option 1: Deal the cards" << endl;
        cout << "Option 2: Hit" << endl;
        cout << "Option 3: Stay" << endl;
        cout << " " << endl;
        cin >> num;
        switch(num){
            case 0:
                cout << "End game. Thank you for playing." << endl;
                endGame = true;
                break;
            case 1:
                cout << "Dealing cards..." << endl;
                if(cardsDealt == false){
                    dealCard();          //card object from top of deck
                    cardsDealt = true;
                }else{
                    cout << "Cards have already been dealt" << endl;
                }
                break;
            case 2:
                cout << "Hit" << endl;      //hit
                break;
            case 3:
                cout << "Stay" << endl;      //stay
                break;
        }// end switch
    }while(endGame != true);
}// end optionsMenu

void Game::printCards(bool cardsDealt) {
    cout << "in printCards()" << endl;
    bool dealt = cardsDealt;
//    cout << "dealt printCards: " << dealt << endl;
    Node<Player> *curr = PlayerList->begin();
//    Node<Card> *cardCurr = shoe->Cards->begin();
//    Card tempCard;
//    tempCard = cardCurr->getVal();
    cout << " " << endl;
    cout << "***************************************************" << endl;
    cout << "\t Dealer's Cards: " << endl;
    cout << "\t"; dealer->printHand(); cout << endl;
    cout << "***************************************************" << endl;
    //cout << "PlayerLIst size(): " << PlayerList->size() << endl;
    for(int i = 0; i <PlayerList->size();i++){
        cout << "***************************************************" << endl;
        cout << "\t Player: " << curr->getVal().getPlayerName() << "'s Cards:" << endl;
        //curr->getVal().addCardToHand(shoe->getTopCard());
//        if(dealt == true){
//            curr->getVal().addCardToHand(tempCard);
//            //shoe->deckPrint();
//            cardCurr = cardCurr->getNextNode();
//            tempCard = cardCurr->getVal();
//            curr->getVal().addCardToHand(tempCard);
//            dealt = false;
//            cout << "dealt: " << dealt << endl;
//        }

        cout << "\t"; curr->getVal().printHand();  cout << endl;
        //shoe2->addCard(shoe->pop());

        //cout << " [ "; curr->getVal().printHand();  cout << "]" << endl;
        cout << "***************************************************" << endl;

    }
}

void Game::placeBets() {
    Node<Player> *curr = PlayerList->begin();
    int bet = 0;
    for(int i = 0; i <PlayerList->size();i++){
        cout << "Player: " << curr->getVal().getPlayerName() << " bet: " << endl;
        cin >> bet;
        setBet(i, bet);
        if(i < PlayerList->size()-1){
            curr = curr->getNextNode();
        }
    }
}

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
    cout << "in dealCard" << endl;
    Node<Player> *curr = PlayerList->begin();
    Node<Card> *cardCurr = shoe->Cards->begin();
    Card tempCard;
    tempCard = cardCurr->getVal();
    dealer->addCardToHand(tempCard);
    cardCurr = cardCurr->getNextNode();
    tempCard = cardCurr->getVal();
    dealer->addCardToHand(tempCard);
    cardCurr = cardCurr->getNextNode();
    tempCard = cardCurr->getVal();
    for(int i = 0; i <PlayerList->size();i++) {
        curr->getVal().addCardToHand(tempCard);
        cardCurr = cardCurr->getNextNode();
        tempCard = cardCurr->getVal();
        curr->getVal().addCardToHand(tempCard);
        //cout << "\t"; curr->getVal().printHand();  cout << endl;

        if(i < PlayerList->size()-1){
            curr = curr->getNextNode();
        }
    }
}//end dealCard

///////////////////////////
/* Dealer Class Functions */
/////////////////////////

Dealer::Dealer(string name, int cashRemaining) {
  this->playerName = name;
  this->cashRemaining = cashRemaining;
}

void Dealer::addCardToHand(Card card) {
    this->Hand->addCard(card);
}
void Dealer::printHand() {
    this->Hand->deckPrint();
    //updateCardsValue();
    //cout << "Value: " << cardsValue << endl;
}
