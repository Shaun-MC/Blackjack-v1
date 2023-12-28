#include "Controlled_Player.h"

// Constructors
Controlled_Player::Controlled_Player() {

    Hand temp;

    this->hands_.push_back(temp);
}

int Controlled_Player::hand_total(const int hand_index) const { // UNTESTED

    const int total1 = this->hands_[hand_index].hand_totals1();
    const int total2 = this->hands_[hand_index].hand_totals0();
    
    return (total1 > total2) ? total1 : total2;
}

// Actions
void Controlled_Player::ReceiveCard(const Card& new_card, const int hand_index) {

    this->hands_[hand_index].AddCardToHand(new_card);
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

bool Controlled_Player::SplitCheck(const int hand_index) const {

    return (this->hands_[hand_index].front_card() == this->hands_[hand_index].back_card());
}

void Controlled_Player::BeginningBalance(const int balance) {

    this->stats.set_balances(balance);
}

int Controlled_Player::Balance() const {

    return this->stats.current_balance();
}

void Controlled_Player::PlaceBet(const int bet) {

    this->stats.set_current_bet(bet);
}

int Controlled_Player::Bet() const {

    return this->stats.current_bet();
}

bool Controlled_Player::HandBusted(const int hand_key) const {

    return (this->hands_[hand_key].hand_totals0() > 21);
}

void Controlled_Player::AddAHand(const Card& split_card) { // UNTESTED

    Hand temp;

    this->hands_.push_back(temp);

    this->hands_[this->hands_.size() - 1].AddCardToHand(split_card);
}

void Controlled_Player::DisplayHand(const int hand_key) const {

    this->hands_[hand_key].DisplayHand();
}

void Controlled_Player::Wins(const int hand_type) {

    this->stats.UpdateBalance(hand_type);
}

void Controlled_Player::Loss(const int hand_type) {

    this->stats.UpdateBalance(hand_type + 2);
}

void Controlled_Player::Shove() {

    this->stats.UpdateBalance(5);
}

void Controlled_Player::UpdateGameStatistics() { // More than just calling a stats function

    
}

void Controlled_Player::DisplayHands() const {

    for (int i = 0; i < this->hands_.size(); i++) {

        this->hands_[i].DisplayHand();
    }
}

void Controlled_Player::DisplayStatisitics() const {

    this->stats.DisplayGameStatisitics();
}

void Controlled_Player::FlushHands() {

    for (int i = 0; i < this->hands_.size() - 1; i++) {

        this->hands_[i].EmptyHand();
    }
}
// Private Member Functions