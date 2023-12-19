#include "Card.h"

// Constructors
Card::Card() : suit_(0), value_(0) {

    this->suit_character_ = "";
}

Card::Card(const int suit, const int value) : suit_(suit), value_(value) {

    switch(suit) {

        case 1: 
        this->suit_character_ = "\u2665";   // Heart
        break;
        
        case 2:
        this->suit_character_ = "\u2666";   // Diamond
        break;
        
        case 3:
        this->suit_character_ = "\u2663";   // Club
        break;
        
        case 4:
        this->suit_character_ = "\u2660";   // Spade
        break;
        
        default:
        cerr << "ERROR: Card(int, int): INVALID SUIT ERROR" << endl;
    }
}

// Getters - Setters
int Card::suit() const {

    return this->suit_;
}

int Card::value() const {

    return this->value_;
}

string Card::suit_character() const {

    return this->suit_character_;
}

void Card::set_suit(const int suit) {

    this->suit_ = suit;
} 

void Card::set_value(const int value) {

    this->value_ = value;
}

// Operator Overloads
void Card::operator = (const Card& rval) {

    this->suit_ = rval.suit();
    this->value_ = rval.value();

    this->suit_character_ = rval.suit_character();
}
bool Card::operator == (const Card& rval) const {

    return (this->suit() == rval.suit() && this->value() == rval.value()) ? true : false;
}

bool Card::operator != (const Card& rval) const {

    return (*this == rval) ? false : true;
}

ostream& operator << (ostream& ostrm, const Card& output) {

    cout << output.suit_character();

    switch(output.value()) {

        case 1: 
        cout << "A";
        break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10: 
        cout << output.value();
        break;

        case 11: 
        cout << "J";
        break;

        case 12:
        cout << "Q";
        break;

        case 13:
        cout << "K";
        break;

        default:
        cout << "Erorr: Card::operator << | Invalid output.value() digit [1,14]";
        break;
    }

    return ostrm;
}

