#ifndef DEALER_H
#define DEALER_H

#include "Hand.h"

class Dealer{
 public:
  // Constructors
  Dealer(); // nessecary??
  Dealer(const Card& first_card, const Card& second_card);

  // Getters - Setters
  int HandTotal() const;

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
