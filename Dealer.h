#ifndef DEALER_H
#define DEALER_H

#include "Hand.h"

class Dealer{
 public:
  // Constructors
  Dealer(); // nessecary??
  Dealer(const Card& first_card, const Card& second_card);

  // Getters - Setters

  // Actions
  void ReceiveCard(const Card& new_card);

  //bool PlayHand();

  void DisplayHand() const;

  // Operator Overloads

 private:
  // Private Member Functions
  bool NaturalsCheck() const;
  bool BustCheck() const;

  bool Hit() const;
  bool Stand() const;

  Hand hand_;

};

#endif 
