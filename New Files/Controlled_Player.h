#ifndef CONTROLLED_PLAYER_H
#define CONTROLLED_PLAYER_H

#include "Hand.h"
#include "Statistics_Manager.h"

#include <vector>

class Controlled_Player {
 public:

  // Constructors - Destructor ??

  // Getters - Setters ?? 

  // Actions
  int GameOptionsCheck() const;

  bool BustCheck() const;
  bool SplitCheck() const;
  bool DoubleDownCheck() const;
  bool HitStandCheck() const;
  bool NaturalsCheck() const;

  void DisplayHands() const;

  // Operator Overloads

 private:
  
  // Private Member Functions
  void AddAHand(const Card& split_card);

  vector<Hand> hands_;

  Statistics_Manager stats;
};

#endif