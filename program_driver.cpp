#include <iostream>

#include "Deck.h"
#include "Dealer.h"
#include "Controlled_Player.h"

using namespace std;

bool UserResponceErrorChecking(const char& user_responce, const int key) {

    if (user_responce < 65 || user_responce > 90) {

        return true;
    }

    bool ret = false;
    switch (key) {

        case 0:
        ret = (user_responce != 'D' && user_responce != 'S' && user_responce != 'H' && user_responce != 'T');
        break;
        
        case 1:
        ret = (user_responce != 'H' && user_responce != 'S');
        break;

        case 2:
        ret = (user_responce != 'D' &&user_responce != 'H' && user_responce != 'S');
        break;

        case 3:
        ret = (user_responce != 'Y' && user_responce != 'N');
        break;
    }

    return ret;
}

int main () {
    
    // STEP 1: Instantiate objects
    Deck deck;
    Controlled_Player active_player;
    Dealer dealer;

    bool game_continuation = true;
    
    // STEP 2: Set Controlled_Player beginning balance
    int balance = 0;
    cout << "Dealer: Please offer a starting balance ($100 Minimum): ";
    cin >> balance;

    while (balance <= 100){

        cout << "Dealer: Balance is Invalid. Try Again. ($100 Minimum): ";
        cin >> balance;
    }

    active_player.BeginningBalance(balance);

    do {

        int bet = 0, playable_hands = 1, current_hand = 0; // Naming 'conflicts' current_hand

        // STEP 3: Controlled_Player places a bet
        cout << "Dealer: How much would you like to bet? ($)" << endl;
        cin >> bet;

        while (bet > active_player.Balance() || bet < 0){
            
            if (bet < 0){

                cout << "Dealer: You can't make negative bets. Try Again. : ";
            }

            if (bet > active_player.Balance()){
                
                cout << "Dealer: Sorry, can't bet more than you have at the table. Try Again. : " << endl;    
            }
        
            cin >> bet; 
        }

        active_player.PlaceBet(bet);

        // STEP 4: Deal 2 cards to both the player and the dealer
        // TODO: eliminate the nessecity to create new memory ???, Deleting cards from the deck, can't just keep a reference
        for (int i = 0; i < 2; i++) {

            Card* player_card = new Card(); 
            Card* dealer_card = new Card();
            
            deck.RetrieveCard(player_card, 0);
            deck.RetrieveCard(dealer_card, 0);

            active_player.ReceiveCard(*player_card, current_hand);
            dealer.ReceiveCard(*dealer_card);

            delete player_card;
            delete dealer_card;
        }

        // STEP 5: Dealer and Player's hand are displayed to console, with respect to standard BlackJack rules
        cout << "DEALER UP CARD: ";
        dealer.PrintUpCard();

        cout << "PLAYER HAND: ";
        active_player.DisplayHands();

        // STEP 6: Naturals Check (BlackJack/21) for both Controlled_Player & Dealer
        const bool player_naturals = active_player.NaturalsCheck(0);
        const bool dealer_naturals = dealer.NaturalsCheck(); 
    
        if (player_naturals && dealer_naturals) { // Shove - Nobody wins - no insurance

            active_player.Shove(current_hand);
        } else if (dealer_naturals) { // Dealer wins - player loses

            active_player.Loss(current_hand);
        } else if (player_naturals) { // Player wins - 3/2 return 

            active_player.Wins(current_hand);
        } else {

            // STEP 7: Controlled Player decides how to play their hand
            char user_responce = ' ';
            
            // Reminding the player so they don't bet more than they have - hard coded to stop this behavior anyways
            cout << "On the Table: $" << active_player.Balance() << endl;

            string output = "Dealer: How Would You Like to Play Your Hand? (";
            
            // TODO: Bug - player types a character they don't have the option of pressing 
            //       Like S when they can't split... behavior is not stopped - FIXED? UNTESTED

            // STEP 7a: Checks if player can afford a split or double down, if they can, give player that option 
            // If a player cannot afford to double their bet for splits and double down
            int responce_key = -1;

            if (active_player.Bet() * 2 > active_player.Balance()) {

                responce_key = 1;
            } else if (active_player.SplitCheck()) {
                
                output += "V for Split, D for Double Down, "; // Chose V for Split because it looks like the most divergent character
                responce_key = 0;

            } else { // Player can afford to double down, but they cannot split their hand 
                     //  No hard coded range of card totals to be offered to double down

                output += "D for Double Down, ";
                responce_key = 2;
            }

            output += "H for Hit, and S for Stand): "; // Split(V) and Stand(S) can't be the same characters

            cout << output;
            cin >> user_responce;

            // TODO: BUG ^^  - Send a different key to reflect that the player can/cannot double down etc ??? - UNTESTED
            while (UserResponceErrorChecking(user_responce, responce_key)) { 

                cout << output;
                cin >> user_responce;                                                     
            }

            // STEP 7b: Switch statement used to determine the correct course of action depending on how the 
            //          Controlled_Player choose to play their hand
            switch (user_responce) {

                case 'D': // Intentional follow-through
                
                Card* c_ptr = new Card();
                deck.RetrieveCard(c_ptr, 0);

                active_player.ReceiveCard(*c_ptr, current_hand);
                cout << "Current Hand: " << endl;

                active_player.DisplayHands();

                if (active_player.BustCheck(current_hand)) {

                    cout << "Dealer: Bust. Looks like you lost this one" << endl;
                    
                    active_player.HandBusted(current_hand);       
                }

                delete c_ptr;
                
                case 'S': // Stand
                break;
                
                case 'V': // Split & Hit both require the hit-stand loop
                
                ++playable_hands;

                const Card* c_ptr = &active_player.hands_[0].front_card(); // TODO: Make Controlled_Player hands_ private

                active_player.AddAHand(*c_ptr);

                active_player.hands_[0].RemoveCardFromHand(); // TODO: Make Controlled_Player hands_ private

                case 'H': // Hit 

                for (int current_hand = 0; current_hand < playable_hands; current_hand++) {

                    while (user_responce == 'H') {

                        Card* c_ptr = new Card();

                        deck.RetrieveCard(c_ptr, 0);

                        active_player.ReceiveCard(*c_ptr, current_hand); // TODO: Add a key so the card is placed in the correct Controlled_Player::hands_

                        delete c_ptr;

                        active_player.DisplayHand(current_hand); // Use a that function is O(1) that only prints the back card of the current hand

                        if (active_player.BustCheck(current_hand)) {

                            cout << "Dealer: Bust. Looks like you lost this one" << endl;
                            active_player.HandBusted(current_hand);

                            continue; // for loop : i < playable_hands
                        } else {

                            cout << "Dealer: Would you like to hit your " << active_player.HandTotal(current_hand) << " ?" << endl;
                            cout << "Dealer: H for Hit, S for Stand, captilization matters: ";
                            cin >> user_responce;

                            int responce_key = 1; // Same variable used eariler - different scopes - reorganize???

                            while (UserResponceErrorChecking(user_responce, responce_key)) {

                                cout << "Dealer: Invalid Input. Try Again. (H/S), captilization matters: ";
                                cin >> user_responce;
                            }
                        }
                    } // End of while loop - user_responce == H

                } // End of case 'S' && case 'H'
                
                break;
            } // End of swtich statement

            // STEP 8: Dealer Plays their hand
            if (!dealer_naturals) {
                
                cout << "DEALER PLAYING HAND: ";
                dealer.DisplayHand();
        
                while(dealer.BustCheck() || !dealer.Stay()) {

                    Card* c_ptr = new Card(); // TODO: Requesting new, unnessecary memory ???

                    deck.RetrieveCard(c_ptr, 0);

                    dealer.ReceiveCard(*c_ptr);

                    cout << "DEALER HAND TOTAL: ";
                    dealer.DisplayHand();

                    delete c_ptr;
                }
            }

            // STEP 9: Determine Game Outcome
            for (int current_hand = 0; current_hand < playable_hands; current_hand++) {
                
                const bool player_busted = active_player.BustCheck(current_hand);
                const bool dealer_busted = dealer.BustCheck();

                if (player_busted || (active_player.HandTotal(current_hand) < dealer.hand_total()) ) {

                    // Player losses the hand
                    active_player.Loss(current_hand);
                } else if (dealer_busted && !player_busted || (active_player.HandTotal(current_hand) > dealer.hand_total()) ) {
                    
                    // Player wins the hand
                    active_player.Wins(current_hand);
                    
                } else { // Neither the dealer or player won the hand

                    active_player.Shove(current_hand);
                }
            }
        } 

        // STEP 10: Update Controlled_Player Statistics
        active_player.UpdateGameStatistics();

        // STEP 11: Dealer Asks Controlled_Player if they want to play another hand
        char user_responce = ' '; // Same one as used in the prev. switch statement, determine optimal scope
        int responce_key = 3;     // TODO: Repreated variable across the driver - reorganize
        
        cout << "Dealer: Would you like to play another hand? Y/N, capitalization matters: ";
        cin >> user_responce;

        while (UserResponceErrorChecking(user_responce, responce_key)) {

            cout << "Dealer: Invalid Responce. Would you like to player another hand? Y/N, (capitalization matters): ";
            cin >> user_responce;
        }

        game_continuation = (user_responce == 'Y');
    
    } while (game_continuation); // End of do-while loop
    // STEPS 3-11 Repeats until game_continuation is false

    // STEP 12: The stats the Controlled_Player accumulated over the course of the do-while loop are printed to the console
    cout << "Dealer: It was a pleasure, here's how you did overall: " << endl;
    
    active_player.DisplayStatisitics();

    cout << "Dealer: Farewell" << endl;
    
    return 0;
}
