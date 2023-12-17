#include "Card.h"

Card::Card() {

    this->suit_ = 0;
    this->value_ = 0;

    this->suit_character_ = "";
}

Card::Card(const int suit, const int value) {

    this->suit_ = suit;
    this->value_ = value;

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