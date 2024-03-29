#ifndef DEALER_H
#define DEALER_H

#include <iostream>

using namespace std;

class Dealer{
    public:

    class DealerCard{   // similar class as PlayerCardCard as both 'hands' are doubly linked lists - eventually make a 'virtual' / abstract class 
        public:

        DealerCard() : next(nullptr), prev(nullptr), cardSuit(0), cardValue(0), cardSuitCharacter("")  {}; // default constructor
        DealerCard(const int cardSuit, const int cardValue);
        //copy constructor & assignment operator
        
        unsigned int cardSuit;
        unsigned int cardValue;
        string cardSuitCharacter;

        DealerCard *next, *prev;
    };
    
    Dealer() : head(nullptr), tail(nullptr), iterator(head), handTotal(), handSize(0) {};
    
    ~Dealer();

    bool addToHand(const int cardSuit, const int cardValue); 

    bool removeFromHand();  

    void printCard() const;
    
    bool displayHand();

    void updateHandTotal(); 

    bool naturalsCheck() const;

    bool bustChecker() const;

    bool continueHit() const;

    void resetIterator() const;
    bool hasMore() const;
    DealerCard& next() const;
    void testConnections() const;
                                                    
    private:

    int handSize;
    int handTotal[2];
    DealerCard *head, *tail;
    mutable DealerCard *iterator;
};

#endif