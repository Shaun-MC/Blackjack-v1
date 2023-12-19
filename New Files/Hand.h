#ifndef HAND_H
#define HAND_H

#include "Card.h"

#include <Queue.h>

// Make it a Queue

class Hand {
 public:
  
  // Constructors - Destructors
  Hand();
  Hand(const Hand& rval);

  ~Hand();
  
  // Getters - Setters
  int size() const;

  // Actions

    // Duplicates Allowed 
  void AddCardToHand(const int suit, const int value);

    // 
  void RemoveCardFromHand(); 

  void DisplayHand() const;

  // Operator Overloads
  Hand& operator = (const Hand& rval);

 private:

  // Private Member Functions
  void UpdateHandTotal();

  Queue hand_;

  int hand_totals[2];

  int size_;

  int ace_counter_;
};

#endif
