#include "Dealer.h"

Dealer::Dealer(const Card& first_card, const Card& second_card) {

    this->hand_.AddCardToHand(first_card);
    this->hand_.AddCardToHand(second_card);
}

// Actions
/*bool Dealer::PlayHand() {

    bool dealer_win = true;

    while(this->BustCheck() || !this->Stand()) {

        this->Hit();
    }

    if (this->BustCheck()) {

        dealer_win = false;
    }

    return dealer_win;
}*/

void Dealer::ReceiveCard(const Card& new_card) {

    return;
}

void Dealer::DisplayHand() const {

    this->hand_.DisplayHand();
}

// Private Member Functions
bool Dealer::NaturalsCheck() const {

    return (this->hand_.hand_totals1() == 21) ? true : false;
}

bool Dealer::BustCheck() const {

    return (this->hand_.hand_totals0() > 21) ? true : false;
}

bool Dealer::Stand() const {

    return (this->hand_.hand_totals0() >= 17 || this->hand_.hand_totals1() >= 17) ? true : false;
}

bool Dealer::Hit() const {

    return true;
}

