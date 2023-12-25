#ifndef CONTROLLED_PLAYER_H
#define CONTROLLED_PLAYER_H

#include "Hand.h"
#include "Statistics_Manager.h"

#include <vector>
#include <string>

class Controlled_Player {
 public:

  // Constructors - Destructor ??
  Controlled_Player();

  // Getters - Setters ?? 
  int HandTotal(const int hand_key) const;

  // Actions
  void ReceiveCard(const Card& new_card, const int hand_index);

  bool NaturalsCheck(const int hand_index) const;
  int GameOptionsCheck(const int hand_index) const;
  bool BustCheck(const int hand_index) const;
  bool SplitCheck() const;

  void BeginningBalance(const int balance);
  int Balance() const;// getter for Statistics_Manager::current_balance_
  void PlaceBet(const int bet);
  int Bet() const;

  bool HandBusted(const int hand_key) const;

  void UpdateGameStatistics();
  
  //int GameOptionsCheck(const int hand_index) const;
  void AddAHand(const Card& split_card);
  
  void DisplayHand(const int hand_key) const;
  void DisplayHands() const;

  void DisplayStatisitics() const;

  void Wins(const int hand_key, const int hand_type);
  void Loss(const int hand_key, const int hand_type);
  void Shove(const int hand_key, const int hand_type);

  // Operator Overloads

  vector<Hand> hands_; // TODO: Make private
 private:
  
  // Private Member Functions
  
  bool SplitDesired() const;

  vector<Hand> hands_;

  Statistics_Manager stats;
};

#endif