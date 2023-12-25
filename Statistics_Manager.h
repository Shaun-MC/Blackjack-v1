#ifndef STATISTICS_MANAGER_H
#define STATISTICS_MANAGER_H

#include <iostream>
#include <iomanip>

using namespace std;

const double kNaturalsPayoutRate = 1.5; // 3 / 2

class Statistics_Manager {
 public: 

  // Constructor
  Statistics_Manager();
  
  // Getters - Setters
  int current_bet() const;
  int current_balance() const;

  void set_current_bet(const int bet);
  void set_total_profit(const int profit);
  void set_total_losses(const int losses);

  void set_balances(const int bet);
  
  // Actions

  void SetCurrentBet();
  
  void UpdateBalance(const int game_result);

  void UpdateStatistics();
  void UpdateEndGameStatistics();

  void DisplayGameStatisitics() const;

 private: 
  
  // Private Member Functions
  int NaturalsPayout();

  int beginning_balance_;
  int current_balance_;
  
  int current_bet_;

  int hands_played_;
  int hands_won_;
  int hands_lost_;
  int hands_drawed_;

  int naturals_hit_;

  int highest_balance_;
  int lowest_balance_;
  
  int total_losses_;
  int total_profit_;
};

#endif