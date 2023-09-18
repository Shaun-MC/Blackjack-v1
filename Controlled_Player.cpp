#include "Controlled_Player.h"

#include <iomanip>

Player::PlayerCard::PlayerCard(const int suit, const int value){

    next = prev = nullptr;
    cardSuit = suit;
    cardValue = value;

    switch(suit){
        case 1: 
        cardSuitCharacter = "\u2665";   // heart
        break;
        case 2:
        cardSuitCharacter = "\u2666";   // diamond
        break;
        case 3:
        cardSuitCharacter = "\u2663";   // club
        break;
        case 4:
        cardSuitCharacter = "\u2660";   // spade
        break;
        default:
        cout << "ERROR IN PlayerCard Constructor: INVALID SUIT VALUE!" << endl;
    }
}

Player::~Player(){

    iterator = tail;

    PlayerCard* deleteNode = new PlayerCard();

    while (this->hasMore()){
        deleteNode = iterator;
        iterator = iterator->prev;
        delete deleteNode;
    }
}
Player::Player(const Player& copyPlayer){

    this->handTotal[0] = copyPlayer.handTotal[0];
    this->handTotal[1] = copyPlayer.handTotal[1];

    this->head = this->tail = nullptr;
    
    this->resetIterator();
    copyPlayer.resetIterator();

    while (copyPlayer.hasMore()){
        this->addToHand(copyPlayer.iterator->cardSuit, copyPlayer.iterator->cardValue);
        copyPlayer.iterator = copyPlayer.iterator->next;
    }

}
Player& Player::operator = (const Player& leftPlayer){

    this->handTotal[0] = leftPlayer.handTotal[0];
    this->handTotal[1] = leftPlayer.handTotal[1];

    this->head = this->tail = nullptr;
    
    this->resetIterator();
    leftPlayer.resetIterator();

    while (leftPlayer.hasMore()){
        this->addToHand(leftPlayer.iterator->cardSuit, leftPlayer.iterator->cardValue);
        leftPlayer.iterator = leftPlayer.iterator->next;
    }

    return *this;

}
void Player::addToHand(const int suit, const int value){ 

    PlayerCard *insertNode = new PlayerCard(suit, value);

    if (head == nullptr){   // 0 nodes
        
        head = tail = insertNode; 
    } else {                // 1 & many nodes
        insertNode->prev = tail;
        tail->next = insertNode;
        tail = insertNode;
        ++handSize;
    }

    resetIterator();
    return;
}
bool Player::removeFromHand(){

    PlayerCard *deleteNode = new PlayerCard();

    if (head == nullptr){   // 0 nodes
        cout << "ERROR in removeFromHand(): REMOVING FROM EMPTY LIST!" << endl;
    } else if (head == tail){   // 1 node

        deleteNode = tail;
        head = tail = nullptr;
        --handSize;
        delete deleteNode;
        return true;
    }
    //many nodes
    deleteNode = tail;
    tail = tail->prev;
    --handSize;
    delete deleteNode;
    return true;
}
bool Player::displayPlayerHand() { 

    this->updateHandTotal();

    if (this->handTotal[0] == 0){
        cout << "ERROR in display_PlayerHand(): HAND IS EMPTY!" << endl;
    } else {

        cout << "Current Hand Total:  " << this->handTotal[0];

        if (this->handTotal[1] <= 21 && this->handTotal[1] != 0){
            
            cout << " OR " << this->handTotal[1];
        }
    }

    cout << endl;

    unsigned int counter = 0;
    
    this->resetIterator();

    while (this->hasMore()){
        
        cout << setw(2);

        if (counter == 5) {
            
            cout << endl;
            counter = 0;
        }

        switch(this->iterator->cardValue){
            case 1:
            cout << 'A';
            break;
            case 11:
            cout << 'J';
            break;
            case 12:
            cout << 'Q';
            break;
            case 13: 
            cout << 'K';
            break;
            default:
            cout << this->iterator->cardValue;
        }

        cout << this->iterator->cardSuitCharacter << "  ";

        this->iterator = this->iterator->next;
        ++counter;
    }
    cout << endl;

    return true;
}
void Player::updateHandTotal(){ // using handTotal and reseting it every call seems lame

    int aceCounter = 0;

    this->handTotal[0] = 0;
    this->handTotal[1] = 0;

    this->resetIterator();

    if (head == nullptr) { //TODO feels improper, throw error?
        
        cout << "ERROR INH(): EMPTY HAND, CAN'T EVALUATE!";
    }
    while(this->hasMore()){
        if (this->iterator->cardValue >= 10 && this->iterator->cardValue < 14){
            
            this->handTotal[0] += 10;
        } 
        
        else if (iterator->cardValue == 1){
            
            ++aceCounter;
        } 
        
        else{
        
            this->handTotal[0] += this->iterator->cardValue;
        } 
        
        this->iterator = this->iterator->next;
    }

    switch(aceCounter){
        case 0:
        break;
        case 1:

        if ((this->handTotal[0] + 11) > 22 ) {   // if adding the 11 to the hand busts it, treat the ace as a 1
        
            this->handTotal[0] += aceCounter;
        } else {                                    // else, treat it as a 1 and 11 
            
            this->handTotal[0] += aceCounter;
            this->handTotal[1] = this->handTotal[0] + 10;
        }

        break;
        case 2:
        case 3:
        case 4:
        
        if ((this->handTotal[0] + 11) > 22 ) {
            
            this->handTotal[0] += aceCounter;
        } else {
            
            this->handTotal[0] += aceCounter;
            this->handTotal[1] = this->handTotal[0] + (11 - (--aceCounter));
        }

        break;
        default:
        cout << "TOO MANY ACES IN countHandTotal()!" << endl;
    }
    
    return;
} 
void Player::gameOptionsErrorCheck(int calledVal) const{ // doesnt say where it got called

    resetIterator();

    if (head == nullptr){
        cout << "ERROR in Player::gameOptionsErrorCheck(): empty list" << endl;
    }
    else if (iterator->next == nullptr){
        cout << "ERROR in Player::gameOptionsErrorCheck(): only 1 node" << endl;
    } else if (handSize >= 3){
        cout << "ERROR in Player::gameOptionsErrorCheck(): invaild logic check, more than 2 cards" << endl;
    }

    switch (calledVal){
        case 0:
        cout << "Called from spiltCheck()" << endl;
        break;
        case 1:
        cout << "Called from spiltCheck()" << endl;
        break;
        case 2:
        cout << "Called from spiltCheck()" << endl;
        break;
        default:
        cout << "UNKNOWN gameOptionsErrorCheck() call" << endl;
    }
    if (iterator->cardValue == iterator->next->cardValue){

        cout << "TEST PASSED" << endl;
        return;
    }
}
int Player::gameOptionsCheck() const{

    if (naturalsCheck()){

        return 0;
    }
    else if (splitCheck()){
        
        return 1; 
    } else if (doubleDownCheck()){

        return 2;
    } else if (hitStandCheck()){ // hit

        return 3;
    } else if (!hitStandCheck()){ // stand

        return 4;
    } else {

        cout << "ERROR in Player::check_game_options(): out of bounds check!" << endl;
    }

    return 0;
}
bool Player::bustChecker() const{

    // will have to be called afterH is called to eval the correct data at the proper time
    
    // return true if busted - false if not

    // dont have to check handTotal[1], as that index will only have data if it's < = 21
   
    if(this->handTotal[0] >= 22){

        return false;
    }

    return true;
}
bool Player::splitCheck() const{

    gameOptionsErrorCheck(0);

    resetIterator();

    if (iterator->cardValue == iterator->next->cardValue){

        cout << "TEST PASSED" << endl;
        return true;
    }

    return false;
}
bool Player::doubleDownCheck() const {
    
    gameOptionsErrorCheck(1);

    char responce;

    if (handTotal[0] >= 8 && handTotal[0] <= 11) {
        cout << "Dealer: Care to Double Down? (y/n, captilization matters)" << endl;
        cin >> responce;
    } else {
    
        return false;
    }

    while (responce != 'y' && responce != 'n'){
        cout << "Dealer: INVALID input, try again." << endl;
        cin >> responce;
    }

    if (responce == 'y'){

        cout << "Dealer:: Double Down it is." << endl;
        return true;
    }

    cout << "Dealer: No Doubling Down. Let's carry on." << endl;
    return false;
}
bool Player::hitStandCheck() const{

    char responce;

    cout << "Dealer: Would you like to HIT or STAND? (y/n, capitalization matters)" << endl;
    cin >> responce;
    
    while (responce != 'y' && responce != 'n'){
        cout << "Dealer: INVALID input, try again." << endl;
        cin >> responce;
    }

    if (responce == 'y') {

        return true;
    } 

    return false;
}
bool Player::naturalsCheck() const{

    gameOptionsErrorCheck(2);
    
    if (handTotal[1] == 21){

        return true;
    }

    return false;
}

void Player::resetIterator() const{

    iterator = head;
}
bool Player::hasMore() const{

    if (iterator != nullptr){
        return true;
    }

    return false;
}
Player::PlayerCard& Player::next() const{

    PlayerCard *tempNode = new PlayerCard();
    
    if (iterator == nullptr){
        cout << "ERROR IN next(): CANNOT RETRIEVE VALUE FROM AN EMPTY LIST\n";
    } else {
        tempNode = iterator;
        iterator = iterator->next;
    }
    
    return *tempNode;
}
void Player::testConnections() const{

    resetIterator();

    if (head == nullptr){
        cout << "Empty List!" << endl;

    } else if (head->prev != nullptr){
        cout << "ERROR IN test_connections(): head->prev != nullptr!" << endl;

    } else if (tail->next != nullptr){
        cout << "ERROR IN test_connections(): tail-> " << endl;
   } 

    while (iterator != tail){
        if (iterator != iterator->next->prev){
            cout << "Bad Connection at " << iterator->cardValue << iterator->cardSuitCharacter << endl;
            return;
        }
        iterator = iterator->next;
    }

    cout << "TESTING CONNECTIONS PASSED\n" << endl;
} 

 