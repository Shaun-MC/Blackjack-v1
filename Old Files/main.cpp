#include "Deck.h"
#include "Deck.cpp"

#include "Controlled_Player.h"
#include "Controlled_Player.cpp"

#include "Dealer.h"
#include "Dealer.cpp"

#include <unistd.h>

int main(){

    Deck deckInstance;
    Player playerInstance;
    Dealer dealerInstance;

    int handArr[2];
    const int gameResult[5] = {0,1,2,3,4};

    int gameOptions = 0;  
    
    deckInstance.initializeDeck(0, 0, 0);

    //playerInstance.statsInstance.setBeginningBalance();
    
    handArr[0] = 2;
    handArr[1] = 5;

    playerInstance.addToHand(handArr[0], handArr[1]);

    handArr[0] = 1;
    handArr[1] = 5;

    playerInstance.addToHand(handArr[0], handArr[1]);

    do {

        playerInstance.statsInstance.setBet();

        for (int i = 0; i < 2; i++){
            
            deckInstance.getCard(&handArr[0]);
            playerInstance.addToHand(handArr[0], handArr[1]);
        }

        handArr[0] = handArr[1] = 0;
        
        for (int i = 0; i < 2; i++){
            
            deckInstance.getCard(&handArr[0]);
            dealerInstance.addToHand(handArr[0], handArr[1]);
        }

        playerInstance.displayPlayerHand();

        cout << "DEALER UP CARD: ";
        dealerInstance.printCard();

        if (dealerInstance.naturalsCheck()){
            
            dealerInstance.displayHand();
            cout << "Dealer: Looks like I hit a natural." << endl;
            playerInstance.statsInstance.updateBalance(gameResult[4]);

        } else {
            
            gameOptions = playerInstance.gameOptionsCheck();

            switch(gameOptions){ 
        
                case 0:

                usleep(1000000); 

                cout << "Dealer: Wow, nice! Here's your payout" << endl;

                cout << "+" << playerInstance.statsInstance.naturalsPayout();

                playerInstance.statsInstance.updateBalance(gameOptions);

                cout << "Total Balance: " << playerInstance.statsInstance.printCurrentBalance() << endl;

                break;
                case 1:     // [ split ]

                // create a new player hand
                // add the last card of the old hand to the new hand
                // remove the last card of the old hand
                // ask to hit or stand on the first hand                            
                // ask to hit or stand on the second hand                           
                // repeated prev 2 steps until both hands have stand or busted
                // jump out of switch statement
                break;
                case 2:     // [ double down ]
  

                // have the player double their bet
                // give the player 1 card
                // jump out of switch statement
            
                break;
                case 3:   // [ hit - stand sequence ]

                // give player additional card
                // check bust
                // ask to hit or stand                                              
                // repeat prev step until player has stand or busted
                // jump out of switch statement
            
                break;
                case 4:  // stand
            
                // print dealer's 'face' card
                // dealer naturals check
                // jump out of switch statements
            
                default:

                break;
                //error checking
            }  
        }
    }while (playerInstance.continuePlayingResponce());

    playerInstance.statsInstance.updateFinalStatistics();
    playerInstance.statsInstance.printGameStats();

    return 0;
}