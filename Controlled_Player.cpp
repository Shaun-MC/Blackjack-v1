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

    updateHandTotal();

    if (handTotal[0] == 0){
        cout << "ERROR in display_PlayerHand(): HAND IS EMPTY!" << endl;
    } else {

        cout << "Current Hand Total:  " << handTotal[0];

        if (handTotal[1] <= 21 && handTotal[1] != 0){
            
            cout << " OR " << handTotal[1];
        }
    }

    cout << endl;

    unsigned int counter = 0;
    
    resetIterator();

    while (hasMore()){
        
        cout << setw(2);

        if (counter == 5) {
            
            cout << endl;
            counter = 0;
        }

        switch(iterator->cardValue){
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
            cout << iterator->cardValue;
        }

        cout << iterator->cardSuitCharacter << "  ";

        iterator = iterator->next;
        ++counter;
    }
    cout << endl;

    return true;
}
void Player::updateHandTotal(){ // using handTotal and reseting it every call seems lame

    int aceCounter = 0;

    handTotal[0] = 0;
    handTotal[1] = 0;

    resetIterator();

    if (head == nullptr) { 
        
        cout << "ERROR IN updateHandTotal(): EMPTY HAND, CAN'T EVALUATE!";
    }
    while(hasMore()){
        if (iterator->cardValue >= 10 && iterator->cardValue < 14){
            
            handTotal[0] += 10;
        } 
        
        else if (iterator->cardValue == 1){
            
            ++aceCounter;
        } 
        
        else{
        
            handTotal[0] += iterator->cardValue;
        } 
        
        iterator = iterator->next;
    }

    switch(aceCounter){
        case 0:
        break;
        case 1:

        if ((handTotal[0] + 11) > 22 ) {   // if adding the 11 to the hand busts it, treat the ace as a 1
        
            handTotal[0] += aceCounter;
        } else {                                    // else, treat it as a 1 and 11 
            
            handTotal[0] += aceCounter;
            handTotal[1] = handTotal[0] + 10;
        }

        break;
        case 2:
        case 3:
        case 4:
        
        if ((handTotal[0] + 11) > 22 ) {
            
            handTotal[0] += aceCounter;
        } else {
            
            handTotal[0] += aceCounter;
            handTotal[1] = handTotal[0] + (11 - (--aceCounter));
        }

        break;
        default:
        cout << "TOO MANY ACES IN countHandTotal()!" << endl;
    }
    
} 
bool Player::gameOptionsErrorCheck(int calledVal) const{ 

    resetIterator();

    bool error = false;

    if (head == nullptr){
        cout << "ERROR in Player::gameOptionsErrorCheck(): empty hand" << endl;
        error = true;
    }
    else if (iterator->next == nullptr){
        cout << "ERROR in Player::gameOptionsErrorCheck(): only 1 card" << endl;
        error = true;
    }

    if(error){
        switch (calledVal){
            case 0:
            cout << "Called from spiltCheck()" << endl;
            break;
            case 1:
            cout << "INCOMPLETE" << endl;
            break;
            case 2:
            cout << "Called from doubleDownCheck()" << endl;
            break;
            default:
            cout << "UNKNOWN gameOptionsErrorCheck() call" << endl;
        }

        return false;
    }

    return true;
}
int Player::gameOptionsCheck() const{

    char responce;

    if (naturalsCheck()) {
        
        return 0;
    } else if (splitCheck()) {
    
        return 1; 
    } 
    
    cout << "Dealer: Would you like to Double Down, Hit or Stand? (D for D.D, H for Hit, S for Stand, capitalization matters)" << endl;
    cin >> responce;

    while (responce != 'D' && responce != 'H' && responce != 'S'){ // same output per digit 'glitch'

        cout << "Dealer: Invalid Input, please Try Again. (D for D.D, H for Hit, S for Stand, capitalization matters)" << endl;
        cin >> responce;
    }

    if (responce == 'D'){

        return 2;
    } else if (responce == 'H'){ // hit sequence

        return 3;
    } else if (responce == 'S'){ // stand

        return 4;
    } else {

        cout << "ERROR in Player::check_game_options(): unknown gameplay option!" << endl;
    }

    return 0;
}

bool Player::bustChecker() const{

    // will have to be called afterH is called to eval the correct data at the proper time
    
    // return true if busted - false if not

    // dont have to check handTotal[1], as that index will only have data if it's < = 21
   
    if(handTotal[0] >= 22){

        return false;
    }

    return true;
}

bool Player::naturalsCheck() const{

    gameOptionsErrorCheck(0);
    
    if (handTotal[1] == 21){

        return true;
    }

    return false;
}

bool Player::splitCheck() const{

    gameOptionsErrorCheck(1);

    resetIterator();

    if (iterator->cardValue == iterator->next->cardValue){

        cout << "TEST PASSED" << endl;
        return true;
    }

    return false;
}
bool Player::doubleDownCheck() const {
    
    gameOptionsErrorCheck(2);

    char responce;
    

    if (handTotal[0] >= 8 && handTotal[0] <= 11) {
        cout << "Dealer: Care to Double Down? Y/N, captilization matters)" << endl;
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

    cout << "Dealer: Would you like to HIT or STAND? (H/S), capitalization matters" << endl;
    cin >> responce;
    
    while (responce != 'H' && responce != 'S'){
        cout << "Dealer: Huh? So HIT or STAND? (Y/N)" << endl;
        cin >> responce;
    }

    if (responce == 'H') {

        return true;
    } 

    return false;
}

bool Player::continuePlayingResponce() const{

    char responce;

    cout << "Dealer: Would you like to play another hand? (Y/N)" << endl;
    cin >> responce;
    
    while (responce != 'Y' && responce != 'N'){ 
        cout << "Dealer: Huh? So are you playing or not? (Y/N), capitalization matters" << endl;
        cin >> responce;
    }

    if (responce == 'Y'){
        
        return true;
    } else{

        cout << "Dealer: Have a great rest of your evening!" << endl;
        return false;
    }
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

 