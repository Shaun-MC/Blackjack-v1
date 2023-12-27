#include "Controlled_Player.h"

// Constructors
Controlled_Player::Controlled_Player() {

    Hand temp;

    this->hands_.push_back(temp);

    this->stats; // Investigate nessessity 
}

// Actions

void ReceiveCard(const Card& new_card) {

    return;
}

bool Controlled_Player::NaturalsCheck(const int hand_index) const {

    // Player can only have 2 cards on 1 hand to be considered - naturals
    // Error checking done before the function is called

    return (this->hands_[hand_index].hand_totals0() == 21) ? true : false;
}

bool Controlled_Player::BustCheck(const int hand_index) const {

    // dont have to check hand_totals_[1], as that index will only have data if it's < = 21

    return (this->hands_[hand_index].hand_totals0() >= 22) ? true : false;
}

void Controlled_Player::BeginningBalance(const int balance) {

    this->stats.set_balances(balance);
}

int Controlled_Player::Balance() const {

    this->stats.current_balance();
}

void Controlled_Player::PlaceBet(const int bet) {

    this->stats.set_current_bet(bet);
}

int Controlled_Player::Bet() const {

    return this->stats.current_bet();
}

void Controlled_Player::DisplayHands() const {

    for (int i = 0; i < this->hands_.size(); i++) {

        this->hands_[i].DisplayHand();
    }
}

void Controlled_Player::DisplayStatisitics() const {

    this->stats.DisplayGameStatisitics();
}

// Private Member Fucntions

bool Controlled_Player::SplitCheck() const {

    return (this->hands_[0].front_card() == this->hands_[0].back_card()) ? true : false;
}