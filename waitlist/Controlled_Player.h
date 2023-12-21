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

  // Actions
  int GameOptionsCheck(const int hand_index) const;

  bool BustCheck(const int hand_index) const;

  void DisplayHands() const;

  // Operator Overloads

 private:
  
  // Private Member Functions
  bool NaturalsCheck(const int hand_index) const;
  bool SplitCheck(const int hand_index) const;
  
  bool HitStandCheck(const int hand_index) const;

  void AddAHand(const Card& split_card);
  
  bool SplitDesired() const;

  vector<Hand> hands_;

  Statistics_Manager stats;
};

#endif