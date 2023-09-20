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

    int handArr[2];

    int gameOptions = 0;  
    
    deckInstance.initializeDeck(0, 0, 0);

    //playerInstance.statsInstance.setBeginningBalance();
    
    handArr[0] = 1;
    handArr[1] = 11;
    
    dealerInstance.addToHand(handArr[0], handArr[1]);

    handArr[0] = 1;
    handArr[1] = 1;

    dealerInstance.addToHand(handArr[0], handArr[1]);

    dealerInstance.displayHand();

    /*if (dealerInstance.naturalsCheck()){
        
        cout << "RETURNED TRUE!" << endl;
    }else {

        cout << "RETURNED FALSE" << endl;
    }*/

    /*do {

        playerInstance.statsInstance.setBet();

        for (int i = 0; i < 2; i++){
            
            deckInstance.getCard(&handArr[0]);
            playerInstance.addToHand(handArr[0], handArr[1]);
        }

        for (int i = 0; i < 2; i++){
            
            deckInstance.getCard(&handArr[0]);
            dealerInstance.addToHand(handArr[0], handArr[1]);
        }*/

        //playerInstance.displayPlayerHand();

        //gameOptions = playerInstance.gameOptionsCheck();

        /*switch(gameOptions){ // exiting switch statement will then begin the dealer playing his hand / or not
        
            case 0: //[ naturals hit ]
            
            cout << "Dealer: Wow, nice! Here's your payout" << endl;
            cout << "+$" << playerInstance.statsInstance.naturalsPayout() << endl;
       
            playerInstance.statsInstance.updateBalance(gameOptions);

            break;
            case 1:     // [ double down sequence ]
            
            dealerInstance.printFaceCard();

            if(dealerInstance.naturalsCheck()){

            }
            // dealer naturals check
            // have the player double their bet
            // give the player 1 card
            // jump out of switch statement

            case 2:     // [ split ]
            // dealer naturals check
            // create a new player hand
            // add the last card of the old hand to the new hand
            // remove the last card of the old hand
            // ask to hit or stand on the first hand                            
            // ask to hit or stand on the second hand                           
            // repeated prev 2 steps until both hands have stand or busted
            // jump out of switch statement
            
        
            case 3:     // [ stand ]
            
            // print dealer's 'face' card
            // dealer naturals check
            // jump out of switch statements
            

            case 4:     // [ hit - stand sequence ]
            // print dealer's face card
            // dealer naturals check
            // give player additional card
            // check bust
            // ask to hit or stand                                              
            // repeat prev step until player has stand or busted
            // jump out of switch statement
            default:
    }  
    }while (playerInstance.continuePlayingResponce());*/

    //playerInstance.statsInstance.printCurrentStats();

    return 0;
}