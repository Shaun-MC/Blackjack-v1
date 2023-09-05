#include "Dealer.h"

#include <iomanip>

Dealer::DealerCard::DealerCard(const int suit, const int value){

    next = prev = nullptr;
    cardSuit = suit;
    card_value = value;

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
        cout << "ERROR IN DealerCard(const int suit, const int value): INVALID SUIT VALUE!" << endl;
        exit(1);
    }
}

Dealer::~Dealer(){

    handTotal[0] = 0;
    handTotal[1] = 1;

    DealerCard* delete_Card = new DealerCard();
    
    resetIterator();

    while(this->hasMore()){

        delete_Card = iterator;
        iterator = iterator->next;
        
        delete delete_Card;
    }

    head = nullptr;
    tail = nullptr;
}

// copy constructor - assignment operator

bool Dealer::addToHand(const int suit, const int value){

    DealerCard* insertCard = new DealerCard(suit, value);

    if (head == nullptr){            // 0 Cards;

        head = tail = insertCard;
    } else {                        // many
        insertCard->prev = tail;
        tail->next = insertCard;
        tail = tail->next;
        ++handSize;
    }

    insertCard = nullptr;
    return true;
}
bool Dealer::removeFromHand(){

    DealerCard* delete_Card = new DealerCard();

    if (head == nullptr){
        cout << "LOGIC ERROR IN removeFromHand(): Cant remove from an empty list";
        exit(1);
    } else if (head == tail){
       
        delete_Card = head;
        head = tail = nullptr;
    } else {

        delete_Card = tail;
        tail = tail->prev;
    }

    delete delete_Card;
    return true;
}
/*bool Dealer::naturalsCheck(int foo) const {

    switch(foo){
        case 1:

    

        break;
        case 2:
        
        break;
    }
}*/
bool Dealer::displayHand() {

    this->updateHandTotal();

    if (this->handTotal[0] == 0){
        cout << "ERROR in Dealer::displayHand(): HAND IS EMPTY!" << endl;
        exit(1);
    } 

    bool natFlag = false;

    cout << "Current Hand Total: ";

    if (handTotal[1] == 21 && handSize == 2){

        cout << handTotal[1] << endl;
        natFlag = true;
    } else if (handTotal[1] != 0){

        cout << handTotal[0] << " OR " << handTotal[1] << endl;
    } else {

        cout << handTotal[0] << endl;
    }

    unsigned int counter = 0;
    
    this->resetIterator();

    while (this->hasMore()){
        
        cout << setw(2);

        if (counter == 5) {
            
            cout << endl;
            counter = 0;
        }

        switch(this->iterator->card_value){
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
            cout << this->iterator->card_value;
        }

        cout << this->iterator->cardSuitCharacter << "  ";

        this->iterator = this->iterator->next;
        ++counter;
    }
    cout << endl;

    return true;
}

void Dealer::updateHandTotal(){

    int aceCounter = 0;

    this->handTotal[0] = 0;
    this->handTotal[1] = 0;

    this->resetIterator();

    if (head == nullptr) { //TODO feels improper, throw error?
        
        cout << "ERROR IN updateHandTotal(): EMPTY HAND, CAN'T EVALUATE!";
        exit(1);
    }
    while(this->hasMore()){
        if (this->iterator->card_value >= 10 && this->iterator->card_value < 14){
            
            this->handTotal[0] += 10;
        } 
        
        else if (iterator->card_value == 1){
            
            ++aceCounter;
        } 
        
        else{
        
            this->handTotal[0] += this->iterator->card_value;
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
        cout << "TOO MANY ACES IN count_hand_total()!" << endl;
        exit(1);
    }
    
    return;
}
bool Dealer::bustChecker() const{

    if (handTotal[0] >= 22){
        
        return false;
    }

    return true;
}

bool Dealer::continueHit() const{

    if (!bustChecker() && (handTotal[0] <= 17) || handTotal[1] == 17){
        
       return true;
    }

    return false;
}

void Dealer::resetIterator() const{

    iterator = head;
}
bool Dealer::hasMore() const{

    if (iterator != nullptr){
        
        return true;
    }

    return false;
}
Dealer::DealerCard& Dealer::next() const{

    DealerCard *temp_Card = new DealerCard();
    
    if (iterator == nullptr){
        cout << "ERROR IN next(): CANNOT RETRIEVE VALUE FROM AN EMPTY LIST\n";
        exit(1);
    } else {
        temp_Card = iterator;
        iterator = iterator->next;
    }
    
    return *temp_Card;
}
void Dealer::testConnections() const{

    resetIterator();

    if (head == nullptr){
        cout << "Empty List!" << endl;

    } else if (head->prev != nullptr){
        cout << "ERROR IN testConnections(): head->prev != nullptr!" << endl;

    } else if (tail->next != nullptr){
        cout << "ERROR IN testConnections(): tail-> " << endl;
   } 

    while (iterator != tail){
        if (iterator != iterator->next->prev){
            cout << "Bad Connection at " << iterator->card_value << endl;
            return;
        }
        iterator = iterator->next;
    }

    cout << "TESTING CONNECTIONS PASSED\n" << endl;
} 