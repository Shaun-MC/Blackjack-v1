#include "Deck.h"

#include <iomanip>
#include <random>

Deck::~Deck(){

    resetIterator();

    CardNode* deleteNode;

    while (hasMore()){
        deleteNode = iterator;
        delete deleteNode;
        iterator = iterator->next;
    }
}

bool Deck::initializeDeck(int suit, int value, int tag){

// Suits: 1 - Hearts, 2 - Diamonds, 3 - Clubs, 4 - Spades
// Card Values: 1 - Aces...11 - Jack, 12 - Queen, 13 - King
// Tag - Incrementing +1 until all cards are in the Deck - used in seaching for a card to deal / remove from shoe 

//Change the suits of the cards based on the tag counter

    if (tag == 52) {
        
        return false;
    }                                       
    else if (tag == 0){
    
        setDeck(suit + 1, value + 1, tag + 1);
        initializeDeck(suit + 1, value + 1, tag + 1); 
        return true;
    } else if (tag == 13 || tag == 26 || tag == 39) {

        setDeck(suit + 1, value = 1, tag + 1);
        initializeDeck(suit + 1, value = 1, tag + 1);
        return true;
        }
    else {

        setDeck(suit, value + 1, tag + 1);
        initializeDeck(suit, value + 1, tag + 1);
        return true;
    }
}

void Deck::setDeck(int suit, int value, int tag){

    //always pushing  

    CardNode *tempNode = new CardNode(suit, value, tag);

    if (head == nullptr){       // empty list

        head = tail = tempNode;
        iterator = head;
    } else {                    // anything else
        
        tail->next = tempNode;
        tempNode->prev = tail;
        tail = tempNode;
    }
}

bool Deck::removeCard(const int tag){    

    resetIterator();

    CardNode *tempNode = new CardNode();

    if (tag <= 0 && tag > 52){          // error checking
        cout << "Error in removeCard(): INVALID TAG FOR REMOVAL" << endl;
        exit(1);
    }

    if (tag == head->cardTag){        // removal at head
        tempNode = iterator;
        head = head->next;
        iterator = iterator->next;
        tempNode->next = nullptr;
        head->prev = nullptr;
        delete tempNode;
        return true;
    } 

    if (tag == tail->cardTag){        // removal at the end of the Deck
        tempNode = tail;
        tail = tail->prev;
        tempNode->prev = nullptr;
        tail->next = nullptr;
        delete tempNode;
        return true;
    }

    while(hasMore()){                  // removal somewhere in the middle
        if (tag == iterator->cardTag){
            tempNode = iterator;
            iterator->next->prev = tempNode->prev;
            iterator->prev->next = tempNode->next;
            tempNode->next = nullptr;
            tempNode->prev = nullptr;
            delete tempNode;                             
            return true;
        } else {
            iterator = iterator->next;
        }
    }

    return false;
}
bool Deck::checkCardTags(const int tagVal) {
    
    //TODO possible optimizations - ???

    // true : tagVal has already been added to the hand - find a new one, find another card to hand to the hand
    // false: tagVal hasn't been added to the hand, it's ok to proceed w/ the current tagVal

    unsigned int index = 0; 

    while (tagListArray[index] != 0 && tagListArray[index] != tagVal){

        ++index;
    }
    
    if (tagListArray[index] == 0){

        tagListArray[index] = tagVal;
        return false;
    }

    return true;            // if the tagListArray[index] == tagVal case hits, this will return true - meaning to grap another one
}

void Deck::getCard(int* handPointer) { //TODO see if there's a way to get rid of warnings

    // have dist(mt) generate a possible card tag
    // check the list if it's availible
        // if yes - retrieve card, remove it from the list, return card
        // if no - generate new tag and retest it

    //TODO: look into https://en.cppreference.com/w/cpp/algorithm/binary_search // Later Editions

    this->resetIterator();

    int randomTag = 0;
    
    int lesserBound = iterator->cardTag;
    int greaterBound = tail->cardTag;
    int middleBound = 0;

    //int returnArray[2] = {0,0}; 

    bool flag = true;
    
    random_device rd;
    mt19937 mt(rd());                                   
    uniform_int_distribution<int> dist(1, 52);

    if (head == nullptr){
        cout << "SHOE IS EMPTY" << endl;      // Dealer Text Line Use Case
        exit(1);                              // eventual reshuffleDeck() use case
    }

    randomTag = dist(mt);

    while (this->checkCardTags(randomTag)) {
            
        randomTag = dist(mt); // if we've already used that tag, get a new one
    }

    do {

        while ((greaterBound - lesserBound) >= 1){ 

            middleBound = (lesserBound + greaterBound) / 2;

            if (randomTag == lesserBound || randomTag == greaterBound || randomTag == middleBound){
            
            while (iterator->cardTag != randomTag) {    // linear search - figure out better way to do this
                
                iterator = iterator->next;
            }
            
            handPointer[0] = iterator->cardSuit;
            handPointer[1] = iterator->cardValue;
            
            removeCard(randomTag);

            return;
            
            flag = false;
            }

            else if (middleBound < randomTag) {
                
                lesserBound = middleBound + 1;
            }
            else if (middleBound > randomTag) {
                
                greaterBound = middleBound;
            }
        }                              
    } while (flag);
    
    return;
}


bool Deck::printDeck()const { 

    resetIterator();

    cout << "CHECKING DECK" << endl;

    while (hasMore()){
        
        switch(iterator->cardSuit){
            case 1:
            cout << iterator->cardSuit << white_heart;
            break;
            case 2:
            cout << iterator->cardSuit << white_diamond;
            break;
            case 3: 
            cout << iterator->cardSuit << white_club;
            break;
            case 4:
            cout << iterator->cardSuit << white_spade;
            break;
            default:
            cout << "ERROR in Deck::print_Deck(): INVALID iterator->cardSuit data!" << endl;
            break;
        }
        
        cout << setw(6) << iterator->cardValue << setw(6) << iterator->cardTag << endl;

        iterator = iterator->next;
    }

    return true;
}
bool Deck::hasMore() const{

    if (iterator != nullptr){
        return true;
    }

    return false;
}
void Deck::resetIterator() const{

    iterator = head;
}