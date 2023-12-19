#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include "Queue.h"

// Make it a Queue

class Hand {
 public:
  
  // Constructors - Destructors
  Hand();
  Hand(const Hand& rval);
  
  // Getters - Setters
  int count() const;
  int ace_counter() const;

   // Only used for UpdateHandTotal correctness
  int hand_totals0() const;
  int hand_totals1() const;

  // Actions

    // Duplicates Allowed 
  void AddCardToHand(const Card& insert_card);

    // 
  void RemoveCardFromHand(); 

  void DisplayHand() const; 

  // Operator Overloads
  Hand& operator = (const Hand& rval);

  // Boolean operators are only used for testing, not used in other any context
  bool operator == (const Hand& rval) const;
  bool operator != (const Hand& rval) const;

 private:

  // Private Member Functions
  void UpdateHandTotal();

  Queue hand_;

  int hand_totals[2];

  int count_;

  int ace_counter_;
};

#endif
