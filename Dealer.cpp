#include "Dealer.h"

// Constructor
Dealer::Dealer(const Card& first_card, const Card& second_card) {

    this->hand_.AddCardToHand(first_card);
    this->hand_.AddCardToHand(second_card);
}

// Acctions
void Dealer::ReceiveCard(const Card& new_card) { // UNTESTED

    return;
}

void Dealer::PrintUpCard() const { // UNTESTED

    cout << this->hand_.front_card();
}

bool Dealer::NaturalsCheck() const {

    return (this->hand_.hand_totals1() == 21) ? true : false;
}

bool Dealer::BustCheck() const {

    return (this->hand_.hand_totals0() > 21) ? true : false;
}

bool Dealer::Stay() const {

    return (this->hand_.hand_totals0() >= 17 || this->hand_.hand_totals1() >= 17) ? true : false;
}

void Dealer::DisplayHand() const {

    this->hand_.DisplayHand();
}


