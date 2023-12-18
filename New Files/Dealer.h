#ifndef DEALER_H
#define DEALER_H

#include "Hand.h"

class Dealer{
 public:
  // Constructors

  // Getters - Setters

  // Actions
  void DisplayHand() const;

  bool NaturalsCheck() const;
  bool BustCheck() const;

  void Hit() const;

  // Operator Overloads

 private:
  // Private Member Functions
   void UpdateHandTotal();

 Hand hand;

};

#endif 
