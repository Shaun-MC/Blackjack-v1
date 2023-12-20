#ifndef DECK_H
#define DECK_H

#include <random>
#include <vector>

#include "Card.h"

const int kDeckSize = 52;

class Deck {
 public:
  
  // Constructors - Destructors
  Deck();
  ~Deck();
  
  // Getters - Setters
  int length() const; // purely for testing correctness of other functions

  // Actions
  bool InitializeDeck(int suit, int value, int tag); // Recursive Function called in Constructor

  bool AddCard(int tag);

  bool RemoveCard(int tag);

  void RetrieveCard(int tag, Card* &ret_card);

  void DisplayDeck() const;

  bool TestConnections() const;

 private: 
  // Private Member Functions
  void SetDeck(int suit, int value, int tag);

  int CreateRandomTag() const;
  bool CheckUsedCardTags(const int tag) const;

  void ResetIterator() const; 
  
  struct Node {

    Card* card;

    int tag = 0;
    Node* next = nullptr;
    Node* prev = nullptr;
   };

   Node* head_;
   Node* tail_;

   mutable Node* iterator_;

   vector<int> tag_list_;

   int length_;
};

#endif 