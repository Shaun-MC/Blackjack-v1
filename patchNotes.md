# commit fix_displayHand: (9/20/23 - 4:40PM)

## Fixed Dealer::displayHand() 

### Tested displayHand() w/ following code:

_Ran 3 Times_
        
    for (int i = 0; i < 12; i++){

        deckInstance.getCard(&handArr[0]);
        
        dealerInstance.addToHand(handArr[0], handArr[1]);
        
        dealerInstance.displayHand();

        handArr[0] = 0;
        handArr[1] = 0;
    }

### Looking For:

* 2 spaces per card 
* 5 card per line formatting
* Correct hand totals - aces, no aces, no 'second hand' when ace is dealt after 21
* Making sure getCard() doesn't retrieve duplicate cards

## Minor fixes in main.cpp 

# commit add_doublingDown (9/20/23 - ???)

## Added unistd.h library & usleep() so player has time to relize they hit a natural 21 - (9/21/23 - 10:20AM)

## Added updateStatistics() and updateFinalStatistics() - (9/21/23 - 10:52AM)


