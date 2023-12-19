#ifndef QUEUE_H
#define QUEUE_H

// Queue Data Structure Implemented as a Vector

#include <vector>

#include "Card.h"

class Queue {
 public:
  // Constructors - Destructor
  Queue();
  Queue(const Queue& rval);

  ~Queue();
  
  // Getters - Setters
  Card& front() const;
  Card& back() const;

  int length() const;

  // Actions
  bool Pop();
  void Push(const Card& element);

  bool IsEmpty() const;

  // Operator Overloads
  Queue& operator = (const Queue& rval);

  // Only for Testing - not used in any other context
  bool operator == (const Queue& rval) const;
  bool operator != (const Queue& rval) const; 

 private:
  
  // Private Data Functions
  void DoubleQueueSize();

  // Private Data Members
  vector<Card> vec_;
  
  Card* front_;
  Card* back_;

  int front_index_;
  int back_index_;

  int length_;
};

#endif