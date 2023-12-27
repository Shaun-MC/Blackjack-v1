#ifndef DEALER_H
#define DEALER_H

#include "Hand.h"

class Dealer{
 public:
  // Constructors
  Dealer();
  Dealer(const Card& first_card, const Card& second_card);

  // Getters - Setters
  int hand_length() const;
  int hand_total() const;

  // Actions
  void ReceiveCard(const Card& new_card);

  void PrintUpCard() const;

  bool NaturalsCheck() const;
  
  bool BustCheck() const;
  bool Stay() const;

  void DisplayHand() const;

  // Operator Overloads

 private:
  // Private Member Functions

  Hand hand_;

};

#endif 
