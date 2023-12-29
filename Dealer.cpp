#include "Dealer.h"

// Constructor
Dealer::Dealer() {

    // Unessecary to put anything here, at the time of writing uses Hand() constructor
}

Dealer::Dealer(const Card& first_card, const Card& second_card) {

    this->hand_.AddCardToHand(first_card);
    this->hand_.AddCardToHand(second_card);
}

// Getters - Setters
int Dealer::hand_total() const {

    return (this->hand_.hand_totals1() > this->hand_.hand_totals0()) ? this->hand_.hand_totals1() : this->hand_.hand_totals0();
}

int Dealer::hand_length() const {

    return this->hand_.count();
}

// Actions
void Dealer::ReceiveCard(const Card& new_card) { // UNTESTED

    this->hand_.AddCardToHand(new_card);
}

void Dealer::PrintUpCard() const { // UNTESTED

    cout << this->hand_.front_card() << endl;
}

bool Dealer::NaturalsCheck() const { // UNTESTED

    return (this->hand_.hand_totals1() == 21) ? true : false;
}

bool Dealer::Bust() const { // UNTESTED

    return (this->hand_total() > 21) ? true : false;
}

bool Dealer::Stay() const { // UNTESTED

    return (this->hand_total() >= 17) ? true : false;
}

void Dealer::DisplayHand() const { // UNTESTED

    cout << "Current Hand Total: " << this->hand_total() << endl;

    this->hand_.DisplayHand();
}


