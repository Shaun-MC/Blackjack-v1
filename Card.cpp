#include "Card.h"

// TODO: Add Exceptions where appropreiate

// Constructors
Card::Card() : suit_(0), value_(0), face_value_(0) {

    this->suit_character_ = "";
    this->card_character_ = "";
}

Card::Card(const int suit, const int value) : suit_(suit) {

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
        cerr << "Card::Card(suit, value) | Invalid suit digit [1,4]" << endl; // Exception
    }

    if (value == 1) {

        this->card_character_ = "A";
        this->value_ = value;
        this->face_value_ = value;

    } else if (value >= 11) {

        switch(value) {
            case 11:
            this->card_character_ = "J";
            this->face_value_ = 11;
            break;

            case 12:
            this->card_character_ = "Q";
            this->face_value_ = 12;
            break;

            case 13:
            this->card_character_ = "K";
            this->face_value_ = 13;
            break;

            default:
            cerr << "Card::Card(suit, value) | Invalid value digit [1, 13]" << endl; // Better Error Checking - Exception at the top of the function
        }

        this->value_ = 10;
    } else {

        this->card_character_ = to_string(value);
        this->value_ = value;
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

string Card::card_character() const {

    return this->card_character_;
}

int Card::face_value() const {

    return this->face_value_;
}

void Card::set_suit(const int suit) {

    this->suit_ = suit;
} 

void Card::set_value(const int value) {

    this->value_ = value;
}

// Operator Overloads
void Card::operator = (const Card& rval) {

    this->suit_ = rval.suit_;
    this->value_ = rval.value_;

    this->suit_character_ = rval.suit_character_;
    this->card_character_ = rval.card_character_;

    this->face_value_ = rval.face_value_;
}

bool Card::operator == (const Card& rval) const {

    return (this->suit() == rval.suit() && this->value() == rval.value() && 
            this->card_character() == rval.card_character()) ? true : false;
}

bool Card::operator != (const Card& rval) const {

    return (*this == rval) ? false : true;
}

ostream& operator << (ostream& ostrm, const Card& output) {

    ostrm << output.suit_character();
    ostrm << output.card_character();

    return ostrm;
}

