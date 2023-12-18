#ifndef HAND_H
#define HAND_H

#include "Card.h"

#include <queue>

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

    // Duplicates Allowed - First in Last Out
  void AddCardToHand(const int suit, const int value);

    // First in Last Out - Takes the 'head_' card out of the hand
  void RemoveCardFromHand(); 

  void DisplayHand() const;

  // Operator Overloads
  Hand& operator = (const Hand& rval);

 private:

  // Private Member Functions
  void UpdateHandTotal();
  
  struct Node {

    Card* card;
    Node* next = nullptr; 
    Node* prev = nullptr;
  };

  Node* head_; 
  Node* tail_;

  int hand_totals[2];

  int size_;

  int ace_counter_;
};

#endif
