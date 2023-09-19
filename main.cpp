#include "Deck.h"
#include "Deck.cpp"

#include "Controlled_Player.h"
#include "Controlled_Player.cpp"

#include "Dealer.h"
#include "Dealer.cpp"

int main(){

    Deck deckInstance;
    Player playerInstance;
    Dealer dealerInstance;

    int gameOptions = 0;

    int handArr[2]; 
    
    deckInstance.initializeDeck(0, 0, 0);

    playerInstance.statsInstance.setBeginningBalance();

    playerInstance.statsInstance.setBet();

    for (int i = 0; i < 2; i++){
            
        deckInstance.getCard(&handArr[0]);
        playerInstance.addToHand(handArr[0], handArr[1]);
    }

    playerInstance.displayPlayerHand();

    gameOptions = playerInstance.gameOptionsCheck();

    switch(gameOptions){ // exiting switch statement will then begin the dealer playing his hand / or not
        
        case 0: //[ naturals hit ]
        cout << "Dealer: Wow, nice! Here's your payout" << endl;
        cout << "+" << playerInstance.statsInstance.naturalsPayout() << endl;
       
        playerInstance.statsInstance.updateBalance(gameOptions);
        break;
        case 1:
        // [ split sequence ]
        dealerInstance.displayHand();
        // dealer naturals check
        // create a new player hand
        // add the last card of the old hand to the new hand
        // remove the last card of the old hand
        // ask to hit or stand on the first hand                            
        // ask to hit or stand on the second hand                           
        // repeated prev 2 steps until both hands have stand or busted
        // jump out of switch statement

        case 2:
        // [ double down sequence ]
        // print dealer's face card
        // dealer naturals check
        // have the player double their bet
        // give the player 1 card
        // jump out of switch statement
        
        case 3:

        // [ hit ]
        // print dealer's face card
        // dealer naturals check
        // give player additional card
        // check bust
        // ask to hit or stand                                              X
        // repeat prev step until player has stand or busted
        // jump out of switch statement

        case 4:

        // [ stand ]
        // print dealer's face card
        // dealer naturals check
        // jump out of switch statements
    }  

    return 0;
}