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

Card Deck::getTopCard() {
    Card top;
    Node<Card> *curr = Cards->begin();
    top = curr->getVal();
    //top = Cards->begin();
    return top;
}

Card Deck::pop() {
  return this->Cards->pop();
}

void Deck::join(Deck& other) {
  this->Cards->join(this->Cards->begin(), *other.Cards);
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
    playerBet = 0;
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
//int Player::getBet(){return this->playerBet;}

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
    int buyIn;
    cin >> buyIn;
    this->cashRemaining = buyIn;
}

//void Player::setBet(int num) {this->playerBet = num;}

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
  updateCardsValue();
  cout << " " << endl;
  cout << "\tValue: " << cardsValue;
  if(cardsValue > 21){
      cout << " Bust!: You Lose." << endl;
  }else if(cardsValue == 21){
      cout << " You Win." << endl;
  }
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

void Game::loadGame() {
    int num;
    cout << "Welcome to our BlackJack table." << endl;
    cout << endl << "Enter number of players: (max 5)" << endl;
    cin >> num;
    addPlayer(num);
}

void Game::addPlayer(int num){
    Player *person = new Player;
    for(int i = 1; i <= num; i++){

        char correct = false;                       //checks if input is correct
        while(correct != true) {                    //allows user to correct name and buy in amount
            person->setPlayerName(i);
            person->setCashRemaining();
            cout << "Player name: " << person->getPlayerName() << " Player buy in: " << person->getCashRemaining() << endl;
            cout << "Is this correct? Y/N" << endl;
            cin >> correct;
            if (correct == 'Y' || correct == 'y') {
                PlayerList->addNode(*person);   //adds person object to playerlist
                correct = true;
            } else {
                cout << "Please enter the correct info." << endl;
            }
        }//end while
    }//end for loop
    printPlayer();
}// end addPlayer

void Game::printPlayer(){       //prints the players after player names, buy in amount and bet amount.
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

int Game::getTurn(int playerNum){
    return this->turn[playerNum];
}
void Game::setTurn(int arr, int num){
    this->turn[arr] = num;
}
int Game::getBet(int num){return this->bet[num];}
void Game::setBet(int arr, int num){this->bet[arr] = num;}


void Game::optionsMenu() {
    bool endGame = false;               //ends while loop
    bool betsPlaced = false;            //
    bool cardsDealt = false;            //
    //bool playersTurn = true;
    bool playerStay = false;            //if player stays, dealers turn
    bool dealersTurn = false;
    int num;                            //input for options menu
    int playerTurn = 0;
    int currCardIndex = 0;              //keeps track of next card not yet dealt
    do{
        if(cardsDealt == false){        //bets must be placed before dealing cards
            placeBets();                //takes in bet
            betsPlaced = true;
        }
        if(cardsDealt == true) {        //show cards once cards are dealt
            printCards();               //prints hand of player
            checkCardValues();          //checks the value of players hand, if >21 sub bet from buy in
        }
        printPlayer();                  //shows players name, buy in and bet
        if(betsPlaced == true && cardsDealt == true){
            if(playerStay == false) {
                Node<Player> *curr = PlayerList->begin();
                //for (auto curr = PlayerList->begin(); curr != nullptr; curr = curr->getNextNode()){
                for (int i = 0; i <= playerTurn; i++) {
//                    cout << "***************************************************" << endl;
//                    cout << "Player: " << curr->getVal().getPlayerName() << "'s Turn. Please select (2)Hit or (3)Stay"
//                         << endl;
//                    cout << "***************************************************" << endl;
                    if (i < PlayerList->size() - 1) {
                        curr = curr->getNextNode();
                    }
                    cout << "***************************************************" << endl;
                    cout << "Player: " << curr->getVal().getPlayerName() << "'s Turn. Please select (2)Hit or (3)Stay"
                         << endl;
                    cout << "***************************************************" << endl;
                }//end for
            }//end if
            if(playerStay == true){
                cout << "***************************************************" << endl;
                cout << "Player: Dealer's Turn. (Must hit until value >= 17)"
                     << endl;
                cout << "***************************************************" << endl;
            }
        }//end if
        cout << "Please choose an option from the game menu: " << endl;
        cout << "Option 0: End the Game" << endl;
        cout << "Option 1: Deal the cards" << endl;
        cout << "Option 2: Hit" << endl;
        cout << "Option 3: Stay" << endl;
        cout << "Option 4: New game" << endl;
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
                    dealInitialCards();                 //gives two cards to dealer and player (deal 4 cards)
                    currCardIndex = currCardIndex + 4;  //keeps track of what card is next in Deck (index + 4)
                    cardsDealt = true;
                }else{
                    cout << "Cards have already been dealt" << endl;
                }
                break;
            case 2:
                cout << "Hit" << endl;      //hit
                hit(currCardIndex, playerStay);                 //sends card index to hit function (deal 1 card)
                currCardIndex = currCardIndex + 1;  //Deck index + 1 for next card
                break;
            case 3:
                cout << "Stay" << endl;      //stay
                cout << "playerTurn: " << playerTurn << endl;
                    if(playerTurn == PlayerList->size()-1){
                        playerStay = true;                      //all players stay
                    }
                    cout << "playerTurn after stay: " << playerTurn << " size: " << PlayerList->size() << " playerStay: " << playerStay << endl;
                    playerTurn = playerTurn + 1;
                    if(playerTurn == PlayerList->size()-1 && playerStay == true){
                        dealersTurn = true;
                    }
                if(dealersTurn = true){
                    //checkCardValues();
                }

                break;
            case 4:
                cout << "New game" << endl;
                clearTable();
                cardsDealt = false;
                playerStay = false;
                betsPlaced = false;
                playerTurn = 0;
                break;
        }// end switch
    }while(endGame != true);
}// end optionsMenu

void Game::checkCardValues() {
    for (auto iter = PlayerList->begin(); iter != nullptr; iter = iter->getNextNode()){
        if(iter->getVal().getCardsValue() > 21){
            //subMoney(iter->getVal().getPlayerName(), iter->getVal().getBet());
        }

        //iter->getVal().addCardToHand(shoe->pop());
    }
}

void Game::printCards() {
    Node<Player> *curr = PlayerList->begin();
    cout << " " << endl;
    cout << "***************************************************" << endl;
    cout << "\t Dealer's Cards: " << endl;
    cout << "\t"; dealer->printHand(); cout << endl;
    cout << "***************************************************" << endl;
    for (auto curr = PlayerList->begin(); curr != nullptr; curr = curr->getNextNode()){
    //for(int i = 0; i <PlayerList->size();i++){
        cout << "***************************************************" << endl;
        cout << "\t Player: " << curr->getVal().getPlayerName() << "'s Cards:" << endl;
        cout << "\t"; curr->getVal().printHand();  cout << endl;
        cout << "***************************************************" << endl;
    }
}

void Game::placeBets() {        //takes in bet.
    Node<Player> *curr = PlayerList->begin();
    int bet = 0;
    for(int i = 0; i <PlayerList->size();i++){
        cout << "Player: " << curr->getVal().getPlayerName() << " bet: " << endl;
        cin >> bet;
        setBet(i, bet);
        //curr->setVal();     //stores bet in protected player data member: playerBet
        //cout << "current bet: " <<  curr->getVal().getBet() << endl;
        //setBet(i, bet);
        if(i < PlayerList->size()-1){       //stops for loop from going out of range
            curr = curr->getNextNode();
        }
    }
}

void Game::addMoney(string name, int num) {
  Node<Player>* curr;
  curr = PlayerList->begin();      //bypass dealer
  for(int i = 0; i < PlayerList->size(); i++) {
    if(curr->getVal().getPlayerName() == name){
      curr->getVal().setCashRemaining(curr->getVal().getCashRemaining()+num);
    }
    if(i < PlayerList->size()-1){   //stops for loop from going out of range
        curr = curr->getNextNode();
    }
  }
}
void Game::subMoney(string name, int num) {
  Node<Player>* curr;
  curr = PlayerList->begin();      //bypass dealer
  for(int i = 0; i < PlayerList->size(); i++) {
    if(curr->getVal().getPlayerName() == name){
      curr->getVal().setCashRemaining(curr->getVal().getCashRemaining()-num);
    }
    if(i < PlayerList->size()-1){   //stops for loop from going out of range
        curr = curr->getNextNode();
    }
  }
}

void Game::hit(int currCardIndex, bool playerPass){
    if(playerPass == false) {                               //player is hitting
        Node<Player> *curr = PlayerList->begin();
        Node<Card> *cardCurr = shoe->Cards->begin();
        for (int i = 0; i < currCardIndex; i++) {            //loops through deck to current index(card not dealt)
            cardCurr = cardCurr->getNextNode();
        }
        Card tempCard;
        tempCard = cardCurr->getVal();
        for (int i = 0; i < PlayerList->size(); i++) {
            curr->getVal().addCardToHand(tempCard);     //adds next card to hand
            if (i < PlayerList->size() - 1) {
                curr = curr->getNextNode();
            }
        }//end for
    }
    if(playerPass == true){                                 //dealer hitting
        Node<Card> *cardCurr = shoe->Cards->begin();
        for (int i = 0; i < currCardIndex; i++) {            //loops through deck to current index(card not dealt)
            cardCurr = cardCurr->getNextNode();
        }
        Card tempCard;
        tempCard = cardCurr->getVal();
        dealer->addCardToHand(tempCard);
    }
}//end hit

void Game::dealInitialCards(){
  for (int i = 0; i < 2; ++i) {
    dealer->addCardToHand(shoe->pop());
    for (auto iter = PlayerList->begin(); iter != nullptr; iter = iter->getNextNode()){
      iter->getVal().addCardToHand(shoe->pop());
    }
  }
}

void Game::clearTable(){
  shoe2->Cards->join(shoe2->Cards->begin(), *this->dealer->Hand->Cards);
  for (auto iter = PlayerList->begin(); iter != nullptr; iter = iter->getNextNode()){
    shoe2->Cards->join(shoe2->Cards->begin(), *iter->getVal().Hand->Cards);
  }
}

///////////////////////////
/* Dealer Class Functions */
/////////////////////////

Dealer::Dealer(string name, int cashRemaining) {
  this->playerName = name;
  this->cashRemaining = cashRemaining;
}
