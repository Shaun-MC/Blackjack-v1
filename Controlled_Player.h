#ifndef CONTROLLED_PLAYER_H
#define CONTROLLED_PLAYER_H

#include "Hand.h"
#include "Statistics_Manager.h"

#include <vector>
#include <string>

const int kHandSize = 1;

class Controlled_Player {
 public:

  // Constructors - Destructor ??
  Controlled_Player();

  // Getters - Setters ?? 
  int hand_total(const int hand_key) const;

  // Actions
  void ReceiveCard(const Card& new_card, const int hand_index);

  bool NaturalsCheck(const int hand_index) const;

  bool BustCheck(const int hand_index) const;
  bool SplitCheck(const int hand_index) const;

  void BeginningBalance(const int balance);
  int Balance() const;// getter for Statistics_Manager::current_balance_
  void PlaceBet(const int bet);
  int Bet() const;

  bool HandBusted(const int hand_key) const;
  
  void AddAHand(const Card& split_card);
  
  void DisplayHand(const int hand_key) const;
  void DisplayHands() const;
  
  void UpdateGameStatistics();
  void DisplayStatisitics() const;

  void Wins(const int hand_type);
  void Loss(const int hand_type);
  void Shove();

  void FlushHands(); // UNTESTED

  // Operator Overloads
  
  // Public Member Data
  vector<Hand> hands_; 

 private:
  
  // TODO: Make private
  // Private Member Functions

  Statistics_Manager stats;
};

#endif