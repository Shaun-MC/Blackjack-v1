#ifndef DECK_H
#define DECK_H

#include <random>
#include <vector>
#include <iomanip>

#include "Card.h"

using namespace std;

const int kDeckSize = 52;

class Deck {
 public:
  
  // Constructors - Destructors
  Deck();

    // Exists only to test AddCard() & RemoveCard() w/ 1 Node 
  Deck(int skip_initializing);

  ~Deck();
  
  // Getters - Setters
  int length() const; // purely for testing correctness of other functions

  // Actions

    // Only implemented to test RemoveCard(), not currently used in any other context
    // No 'sorted' error checking, always adding to the back
  bool AddCard(const Card& card);

  bool RemoveCard(const Card& remove_card);

  void RetrieveCard(Card* &ret_card, int test_tag);

  void DisplayDeck() const;

  bool TestConnections() const;

 private: 
  // Private Member Functions
  bool InitializeDeck(int suit, int value, int tag); // Recursive Function called in Constructor
  void SetDeck(int suit, int value, int tag);

  int CreateRandomTag() const;
  bool CheckUsedCardTags(const int tag) const;

  void ResetIterator() const; 
  
  struct Node {

    Card* card = nullptr;

    Node* next = nullptr;
    Node* prev = nullptr;

    int tag = 0;
   };

   Node* head_;
   Node* tail_;

   mutable Node* iterator_;

   vector<int> tag_list_;

   int length_;
};

#endif 