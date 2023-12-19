#ifndef DECK_H
#define DECK_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class CardNode {
    public:

    CardNode(): 
    next(nullptr), prev(nullptr), cardSuit(0), cardValue(0), cardTag(0) {};    // default constructor
                                                     
    CardNode(const int suit, const int value, const int tag): 
    next(nullptr), prev(nullptr), cardSuit(suit), cardValue(value), cardTag(tag) {};   // constructor                                              

    unsigned int cardSuit;
    unsigned int cardValue;
    unsigned int cardTag;

    CardNode *next, *prev;
};

class Deck {
    public:

    Deck() : head(nullptr), tail(nullptr), iterator(head), white_heart ("\u2665"), white_diamond ("\u2666"), 
    white_spade ("\u2660"), white_club ("\u2663"), tagListArray(){};
    
    ~Deck();

    //TODO copy constructor, assignment operator

    bool initializeDeck(int suit, int value, int tag); // recursive function updated to initialize a Deck of 52 playing cards
    void setDeck (int suit, int value, int tag);       // general function called to set a given card
    bool removeCard(int tag);                          // once a card is dealt - it will need to be removed from the list, one shoe Deck atm 
    void getCard(int* handPointer);                               // retireve a card from the Deck - set data in a vector, return the vector                       

    bool checkCardTags(const int tagVal);

    bool printDeck() const;                            // check to make sure the Deck is properly aligned 
    bool hasMore() const;
    void resetIterator() const;    

    private:

    const string white_heart;
    const string white_diamond;
    const string white_spade; 
    const string white_club;

    CardNode *head, *tail;
    mutable CardNode *iterator;

    int tagListArray[52];
};

#endif