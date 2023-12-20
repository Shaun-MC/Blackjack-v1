#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

class Card {
 public:
  
  // Constructors
  Card();
  Card(const int suit, const int value);

  // Getters - Setters
  int suit() const;
  int value() const;
  string suit_character() const;
  string card_character() const;

  void set_suit(const int suit);
  void set_value(int value);
  
  // Operator Overloads
  bool operator == (const Card& rval) const;
  bool operator != (const Card& rval) const;

  friend ostream& operator << (ostream& ostrm, const Card& output);

 private:
  
  unsigned int suit_;
  unsigned int value_;

  string suit_character_;

  string card_character_;
};

#endif