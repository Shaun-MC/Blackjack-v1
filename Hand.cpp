#include "Hand.h"

// TODO: implement exceptions where appropreiate
// TODO: Code Reuse in operator =

// Constructors
Hand::Hand() : count_(0), ace_counter_(0) {

    this->hand_totals[0] = this->hand_totals[1] = 0;
}

Hand::Hand(const Hand& rval) : count_(rval.count()), ace_counter_(rval.ace_counter_) {

    this->hand_totals[0] = rval.hand_totals[0];
    this->hand_totals[1] = rval.hand_totals[1];

    *this = rval;
}

// Getter
int Hand::count() const {

    return this->count_;
}

int Hand::ace_counter() const {

    return this->ace_counter_;
}

int Hand::hand_totals0() const {

    return this->hand_totals[0];
}

int Hand::hand_totals1() const {

    return this->hand_totals[1];
}

const Card& Hand::front_card() const {

    return this->hand_.front();
}

const Card& Hand::back_card() const {

    return this->hand_.front();
}
// Actions
void Hand::AddCardToHand(const Card& insert_card) {

    this->hand_.Push(insert_card);

    if (insert_card.value() == 1) {

        ++this->ace_counter_;
    }

    ++this->count_;

    UpdateHandTotal();
}

void Hand::RemoveCardFromHand() { // Aces
    
    const Card* temp = &this->hand_.front(); // Retrieve the eventually Pop'ed Card

    bool ace_flag = (this->hand_totals[1] == 0) ? false : true;  // No Ace : Ace

    if (temp->value() == 1) { // Ace

        if (this->ace_counter() == 1) {

            hand_totals[1] = 0;
        } else if (this->ace_counter() >= 2){

            hand_totals[1] -= 1;
        }
        
        hand_totals[0] -= 1;
        --this->ace_counter_;

    } else if (temp->value() >= 10 && temp->value() <= 13) { // 10 thru King

        if (ace_flag) {

            hand_totals[1] -= 10;
        }

        hand_totals[0] -= 10;

    } else { // Any other card

        if (ace_flag) {

            hand_totals[1] -= temp->value();
        } 

        hand_totals[0] -= temp->value();
    }

    this->hand_.Pop();
    
    --this->count_;
}

void Hand::DisplayHand() const {

    cout << "Current Hand Total: " << hand_totals[0];
    
    if (hand_totals[1] != 0) {

        cout << " OR " << hand_totals[1];
    } 
    cout << endl;

    this->hand_.DisplayQueue();

    cout << endl;
}

// Operator Overloads
Hand& Hand::operator = (const Hand& rval) {

    if (this == &rval) { // Same extact list

        return *this;
    } 

    this->hand_ = rval.hand_; // Uses 'Queue' assignment op

    this->hand_totals[0] = rval.hand_totals[0]; // Next 6 lines get ran twice if = called from C.C.

    this->hand_totals[1] = rval.hand_totals[1];

    this->count_ = rval.count();

    this->ace_counter_ = rval.ace_counter_;

    return *this;
}

bool Hand::operator == (const Hand& rval) const {

    if (this == &rval) {

        return true;
    } else if (this->hand_ != rval.hand_ || (this->hand_totals[0] != rval.hand_totals[0] || 
                                             this->hand_totals[1] != rval.hand_totals[1])) {

        return false;
    } 

    return true;
}

bool Hand::operator != (const Hand& rval) const {

    return (*this == rval) ? true : false;
}

// Private Member Functions

// O(n) vs O(1)
void Hand::UpdateHandTotal() { 

    if (this->count() == 0) {

        cerr << "Hand::UpdateHandTotal() | Cannot update hand total w/ a Empty hand" << '\n';
        
        return; // Exception
    } 
    
    Card temp;

    temp = (this->count() == 1) ? this->hand_.front() : this->hand_.back();

    // A + A = 2 & 12
    // A + 10 = 11 & 21
    // 10 + 2 + A = 13 & 0
    // A + 10 + 2 = 13 & 0

    if (temp.value() == 1) {

        if (hand_totals[0] + 11 <= 21 && hand_totals[1] + 11 <= 21) {

            hand_totals[1] += hand_totals[0] + 11;
        } else if (hand_totals[1] + 11 > 21) {

            hand_totals[1] += 1;
        } 

        hand_totals[0] += 1;

    } else {

        this->hand_totals[0] += temp.value();

        if (this->ace_counter() > 0 && temp.value() + this->hand_totals[1] <= 21) {

            this->hand_totals[1] += temp.value();
        } else if (this->hand_totals[1] != 0) {

            this->hand_totals[1] = 0;
        }
    }
}

