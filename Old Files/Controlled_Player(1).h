#ifndef CONTROLLED_PLAYER_H
#define CONTROLLED_PLAYER_H

#include "Statistics_Manager(1).h"
#include "Statistics_Manager(1).cpp"

#include <iostream>

using namespace std;

    // a linked list hand for holding the card data - and the ability to create another one if the case of spliting.

class Player{
    public:

    class PlayerCard{
        public:

        PlayerCard() : next(nullptr), prev(nullptr), cardSuit(0), cardValue(0), cardSuitCharacter("") {};
            
        PlayerCard(const int suit, const int value);

        unsigned int cardSuit, cardValue;
        string cardSuitCharacter; 
        PlayerCard *next, *prev;
    };
    
    Player() : head(nullptr), tail(nullptr), iterator(head), handTotal(), handSize(0) {};
    
    ~Player();

    Player(const Player& copy_Player);

    Player& operator = (const Player& left_Player); 

    void addToHand(const int suit, const int value);

    bool removeFromHand();
    
    bool displayPlayerHand();

    void updateHandTotal();

    int gameOptionsCheck() const;

    bool bustChecker() const;

    bool splitCheck() const;

    bool doubleDownCheck() const; 

    bool hitStandCheck() const;
    
    bool naturalsCheck() const;

    bool continuePlayingResponce() const;

    bool gameOptionsErrorCheck(int calledVal) const;

    // function for splits

    void resetIterator() const;
    bool hasMore() const;
    PlayerCard& next() const;
    void testConnections() const;
    
    StatsManager statsInstance;

    private:

    int handSize;
    int handTotal[2]; 
    PlayerCard *head, *tail;
    mutable PlayerCard *iterator;
};

#endif