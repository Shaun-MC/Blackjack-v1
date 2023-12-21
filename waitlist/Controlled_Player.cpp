#include "Controlled_Player.h"

// Constructors
Controlled_Player::Controlled_Player() {

    Hand temp;

    this->hands_.push_back(temp);

    this->stats; // Investigate nessessity 
}

// Actions
int Controlled_Player::GameOptionsCheck(int hand_index) const { // REORGANIZE AFTER DRIVER DEV.

    const int naturals = 1, split = 2, double_down = 3, hit = 4, stand = 5, complete_hand = 6; // complete_hand - nessecary?

    int ret_value = 0;

    if (this->hands_[hand_index - 1].count() == 2) {

        if (this->NaturalsCheck(hand_index)) {

            ret_value = naturals;
        } else if (this->SplitCheck(hand_index) && this->SplitDesired()) {

            ret_value = split;
        }
    }

    if (ret_value == 0) {

        char responce = ' ';

        cout << "Dealer: Would you like to Double Down, Hit or Stand? ";
        cout << "D for D.D, H for Hit, S for Stand, (capitalization matters)" << endl;
        cin >> responce;

        while ( (responce > 90 || responce < 65) && (responce != 'D' && responce != 'H' && responce != 'S') ){ // Same output per digit 'bug' ?? 

            cout << "Dealer: Invalid Input, Try Again. D for Double Down , H for Hit, S for Stand, (Capitalization matters)" << endl;
            cin >> responce;
        }

        switch(responce) {

            case 'D':
            ret_value = double_down;
            break;

            case 'H':
            ret_value = hit;
            break;

            case 'S':
            ret_value = stand;
            break;
            
            default:
            cerr << "Controlled_Player::GameOptionsCheck() | Unknown responce value" << endl; // Exception
            ret_value = -1;
            break;
        }
    }

    return ret_value;
}

bool Controlled_Player::BustCheck(const int hand_index) const {

    // dont have to check hand_totals_[1], as that index will only have data if it's < = 21

    return (this->hands_[hand_index].hand_totals0() >= 22) ? true : false;
}

void Controlled_Player::DisplayHands() const {

    for (int i = 0; i < this->hands_.size(); i++) {

        this->hands_[i].DisplayHand();
    }
}

// Private Member Fucntions
bool Controlled_Player::NaturalsCheck(const int hand_index) const {

    // Player can only have 2 cards on 1 hand to be considered - naturals
    // Error checking done before the function is called

    return (this->hands_[hand_index].hand_totals0() == 21) ? true : false;
}

bool Controlled_Player::SplitCheck(const int hand_index) const {

    // Size of hand is handled before function call
    return (this->hands_[hand_index].front_card() == this->hands_[hand_index].back_card()) ? true : false;
}