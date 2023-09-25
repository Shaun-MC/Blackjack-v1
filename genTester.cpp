#include <iostream>

#include "Dealer.h"
#include "Dealer.cpp"

#include "Deck.h"
#include "Deck.cpp"

using namespace std;

int main() {
    
    Dealer dealerInstance;
    Deck deckInstance;

    deckInstance.initializeDeck(0,0,0);

    int handArr[2];

    for (int i = 0; i < 3; i++){
            
            deckInstance.getCard(&handArr[0]);
            dealerInstance.addToHand(handArr[0], handArr[1]);
    }

    cout << "DEALER UP CARD: ";

    dealerInstance.printCard();

    dealerInstance.displayHand();

    return 0;
}