#ifndef DEALER_H
#define DEALER_H

#include <iostream>

using namespace std;

class Dealer{
    public:

    class DealerCard{   // same thing as PlayerCardCard as both 'hands' are doubly linked lists - make a 'virtual' / abstract class to avoid code reuse ????
        public:

        DealerCard() : next(nullptr), prev(nullptr), cardSuit(0), card_value(0), cardSuitCharacter("")  {}; // default constructor
        DealerCard(const int cardSuit, const int card_value);
        
        unsigned int cardSuit;
        unsigned int card_value;
        string cardSuitCharacter;

        DealerCard *next, *prev;
    };
    
    Dealer() : head(nullptr), tail(nullptr), iterator(head), handTotal(), handSize(0) {};
    
    ~Dealer();

    bool addToHand(const int cardSuit, const int card_value); 

    bool removeFromHand();                 
    
    bool naturalsCheck(int foo) const; 
    
    bool displayHand();

    void updateHandTotal(); 

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