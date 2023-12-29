#include <iostream>

#include "Deck.h"
#include "Dealer.h"
#include "Controlled_Player.h"

using namespace std;

struct GameAttributes {

    int beginning_balance_ = 0;
    int bet_amount_ = 0;
    
    char user_responce_ = ' '; 
    int responce_key_ = 0;

    bool continuation_ = false;
};

bool UserResponceErrorChecking(const char& user_responce, const int key) { // Function is in a while-loop, returns true so loop continues

    if (user_responce < 65 || user_responce > 90) { // Basic ACSII checking

        return true;
    }

    bool ret = false;
    switch (key) { // Could use some reorganization for cleaner looking comparisons

        case 0:
        ret = (user_responce != 'V' && user_responce != 'D' && user_responce != 'H' && user_responce != 'S'); // Split
        break;

        case 1:
        ret = (user_responce != 'D' && user_responce != 'H' && user_responce != 'S'); // Double down
        break;

        case 2:
        ret = (user_responce != 'H' && user_responce != 'S'); // Hit or Stand
        break;

        case 3:
        ret = (user_responce != 'Y' && user_responce != 'N'); // Game continuation 
        break;

        default: 
        cerr << "UserResponceChecking() | Invalid key value" << endl;
    }

    return ret;
}

int main () {
    
    // STEP 1: Instantiate objects
    Deck deck;
    Controlled_Player active_player;
    Dealer dealer;
    
    GameAttributes game;
    
    // STEP 2: Set Controlled_Player beginning balance
    cout << "Dealer: Please offer a starting balance ($100 Minimum): ";
    cin >> game.beginning_balance_;

    while (game.beginning_balance_ < 100){

        cout << "Dealer: Balance is Invalid. Try Again. ($100 Minimum): ";
        cin >> game.beginning_balance_;
    }

    active_player.BeginningBalance(game.beginning_balance_);

    do {

        int playable_hands = 1, current_hand = 0; // TODO: Naming 'conflicts' current_hand

        // STEP 3: Controlled_Player places a bet
        cout << "Dealer: How much would you like to bet? ($): ";
        cin >> game.bet_amount_;
        // TODO: Bug - when the input is a character - console basically crashes

        while (game.bet_amount_ > active_player.Balance() || game.bet_amount_ <= 0){
            
            if (game.bet_amount_ <= 0){

                cout << "Dealer: You can't make negative or free bets. Try Again. ($): ";
            } else if (game.bet_amount_ > active_player.Balance()) {
                
                cout << "Dealer: Sorry, can't bet more than you have at the table. Try Again. ($): ";
            }
        
            cin >> game.bet_amount_; 
        }

        active_player.PlaceBet(game.bet_amount_);
        cout << endl;

        // STEP 4: Deal 2 cards to both the player and the dealer
        for (int i = 0; i < 2; i++) {

            Card player_card; 
            Card dealer_card;
            
            deck.RetrieveCard(player_card, 0);
            deck.RetrieveCard(dealer_card, 0);

            active_player.ReceiveCard(player_card, current_hand);
            dealer.ReceiveCard(dealer_card);
        }

        // STEP 5: Dealer and Player's hand are displayed to console with respect to standard BlackJack procedure
        cout << "DEALER UP CARD: ";
        dealer.PrintUpCard();

        cout << "PLAYER HAND: ";
        active_player.DisplayHands(); // TODO: Display both hand totals

        // STEP 6: Naturals Check (BlackJack/21) for both Controlled_Player & Dealer
        const bool player_naturals = active_player.NaturalsCheck(current_hand);
        const bool dealer_naturals = dealer.NaturalsCheck(); 
        const int hand_type = 0; // .......
    
        if (player_naturals && dealer_naturals) { // Shove - Nobody wins - no insurance

            active_player.Shove();
        } else if (dealer_naturals) { // Dealer wins - player loses

            dealer.DisplayHand();
            active_player.Loss(hand_type);
        } else if (player_naturals) { // Player wins - 3/2 return 

            active_player.Wins(hand_type);
        } else {
            
            cout << endl;
            // STEP 7: Controlled Player decides how to play their hand
            // Reminding the player so they don't bet more than they have - hard coded to stop this behavior anyways
            cout << "On the Table: $" << active_player.Balance() << endl;

            cout << "Dealer: ";
            string output = "How Would You Like to Play Your Hand? " ;

            // STEP 7a: Checks if player can afford a split or double down, if they can, give player that option 
            // If a player cannot afford to double their bet for splits and double down
            game.responce_key_ = 2;

            if (active_player.Bet() * 2 > active_player.Balance()) {

                game.responce_key_ = 3;
            } else if (active_player.SplitCheck(current_hand)) { 
                
                output += "(V for Split, D for Double Down, "; // Chose V for Split because it looks like the most divergent character
                game.responce_key_ = 0;

            } else { // Player can afford to double down, but they cannot split their hand 
                     //  No hard coded range of card totals to be offered double down option

                output += "(D for Double Down, ";
                game.responce_key_ = 1;
            }

            output += "(H for Hit, and S for Stand): "; // Split(V) and Stand(S) can not be the same characters

            cout << output;
            cin >> game.user_responce_;

            while (UserResponceErrorChecking(game.user_responce_, game.responce_key_)) { 

                cout << "Dealer: Invalid Responce. " << output;
                cin >> game.user_responce_;                                                     
            }

            // STEP 7b: Switch statement used to determine the correct course of action depending on how the 
            //          Controlled_Player choose to play their hand
            switch (game.user_responce_) {

                case 'D': { // Intentional follow-through
                
                    Card new_card;
                    deck.RetrieveCard(new_card, 0);

                    active_player.ReceiveCard(new_card, current_hand);
                    cout << "Current Hand: " << endl;

                    active_player.DisplayHands(); // TODO: Display both hand totals

                    if (active_player.BustCheck(current_hand)) {

                        cout << "Dealer: Bust. Looks like you lost this one" << endl;
                        
                        active_player.HandBusted(current_hand);       
                    }
                }
                
                case 'S': // Stand
                break;
                
                case 'V': { // Split & Hit both require the hit-stand loop
                // TODO: Bug - No prompt to hit cards appears after requesting to Split - Potential solution
                    ++playable_hands;

                    const Card* c_ptr = &active_player.hands_[0].front_card(); // TODO: Make Controlled_Player hands_ private

                    active_player.AddAHand(*c_ptr);

                    active_player.hands_[0].RemoveCardFromHand(); // TODO: Make Controlled_Player hands_ private
                }
                case 'H': {// Hit 

                    for (int i = 0; i < playable_hands; i++) {

                        do {

                            Card new_card;

                            deck.RetrieveCard(new_card, 0);

                            active_player.ReceiveCard(new_card, current_hand); 

                            active_player.DisplayHand(current_hand); // Use a that function is O(1) that only prints the back card of the current hand

                            if (active_player.BustCheck(current_hand)) {

                                cout << "Dealer: Bust. Looks like you lost this one" << endl;
                                active_player.HandBusted(current_hand);

                                game.user_responce_ = 'X'; // Not the best way to fix this
                            } else {

                                cout << "Dealer: Would you like to hit your " << active_player.hand_total(current_hand) << " ?" << endl; // TODO: display both value of the hand if applicable
                                cout << "Dealer: H for Hit, S for Stand, captilization matters: ";
                                cin >> game.user_responce_;

                                game.responce_key_ = 1; // Same variable used eariler - different scopes - reorganize???

                                while (UserResponceErrorChecking(game.user_responce_, game.responce_key_)) {

                                    cout << "Dealer: Invalid Input. Try Again. (H/S), captilization matters: ";
                                    cin >> game.user_responce_;
                                }
                            }
                        } while (game.user_responce_ == 'H');// End of while loop - user_responce == H
                        
                        ++current_hand;
                    } // End of i < playable_hands for loop
                }
                
                break; // End of case 'S' && case 'H'
            } // End of swtich statement

            // STEP 8: Dealer Plays their hand
            if (!dealer_naturals) { 
                
                cout << "DEALER PLAYING HAND: ";
                dealer.DisplayHand();

                while(!dealer.Bust() && !dealer.Stay()) {

                    Card new_card;

                    deck.RetrieveCard(new_card, 0);

                    dealer.ReceiveCard(new_card);

                    cout << "DEALER HAND: ";
                    dealer.DisplayHand(); // TODO: Bug - Doesn't need to include the 'OR' stuff w/ aces - just the highest digit
                }
            }

            // STEP 9: Determine Game Outcome

            // TODO: something that determines whether or not the hand was doubled down to correctly account funds
            //       currently hard coded to always be standard win
            // TOOD: Make each text line reflect how much the player actually won

            for (int hand_index = 0; hand_index < playable_hands; hand_index++) {
                
                const bool player_busted = active_player.BustCheck(hand_index);
                const bool dealer_busted = dealer.Bust();

                if (player_busted || (active_player.hand_total(hand_index) < dealer.hand_total()) ) {

                    // Player losses the hand
                    cout << "Dealer: Looks like you lost this hand. (-$" << active_player.Bet() << ")" << endl;
                    active_player.Loss(1);
                } else if (dealer_busted && !player_busted || (active_player.hand_total(hand_index) > dealer.hand_total()) ) {
                    
                    // Player wins the hand
                    cout << "Dealer: Looks like you won this hand. (+$" << active_player.Bet() << ")" << endl; 
                    active_player.Wins(1);
                    
                } else { // Neither the dealer or player won the hand

                    cout << "Dealer: Shove" << endl;
                    active_player.Shove();
                }
            }
        } // TODO: Bug - No indication that a player wins after get a BlackJack

        // STEP 10: Dealer Asks Controlled_Player if they want to play another hand
        cout << "Dealer: Would you like to play another hand? Y/N, capitalization matters: ";
        
        cin >> game.user_responce_;
        game.responce_key_ = 3;

        while (UserResponceErrorChecking(game.user_responce_, game.responce_key_)) {

            cout << "Dealer: Invalid Responce. Would you like to player another hand? Y/N, (capitalization matters): ";
            cin >> game.user_responce_;
        }

        game.continuation_ = (game.user_responce_ == 'Y');
        
        active_player.FlushHands(); // TODO: Bug - doesn't flush the entire hand or reset hand total
        dealer.FlushHands();

    } while (game.continuation_); // End of do-while loop
    // STEPS 3-10 Repeats until game.continuation_ is false

    // STEP 11: The stats the Controlled_Player accumulated over the course of the do-while loop are printed to the console
    cout << "Dealer: It was a pleasure, here's how you did overall: " << endl;
    
    active_player.DisplayStatisitics(); 
    // TODO: Bug - Total losses doesn't get updated 

    cout << "Dealer: Farewell" << endl;
    
    return 0;
}
