#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

class Card {
 public:
  
  Card();
  Card(const int suit, const int value);

  int suit() const;
  int value() const;

  void set_suit(const int suit);
  void set_value(int value);

  bool operator == (const Card& rval);
  bool operator != (const Card& rval);

 private:
  
  unsigned int suit_;
  unsigned int value_;

  string suit_character_;
};

#endif