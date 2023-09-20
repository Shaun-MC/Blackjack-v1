#commit fixdisplayHand: (9/20/22 - 4:40PM)

    ##Fixed Dealer::displayHand() 

    ###Tested displayHand() w/ following code :

    Ran 3 Times
        
        for (int i = 0; i < 12; i++){

        deckInstance.getCard(&handArr[0]);
        
        dealerInstance.addToHand(handArr[0], handArr[1]);
        
        dealerInstance.displayHand();

        handArr[0] = 0;
        handArr[1] = 0;
    }

    ###Looking For:

        2 spaces per card 
        5 card per line formatting
        Correct hand totals - aces, no aces, no 'second hand' when ace is dealt after 21
        Making sure getCard() doesn't retrieve duplicate cards

    ###Minor fixes in main.cpp 

