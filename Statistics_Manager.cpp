#include "Statistics_Manager.h"

// Constructor
Statistics_Manager::Statistics_Manager() {

  this->beginning_balance_ = this->current_balance_ = this->current_bet_ = 0;

  this->hands_played_ = this->hands_won_ = this->hands_lost_ = this->hands_drawed_ = 0;

  this->naturals_hit_ = 0;

  this->highest_balance_ = lowest_balance_ = 0;
  
  this->total_losses_ = this->total_profit_ = 0;
}

// Getters - Setters
int Statistics_Manager::current_bet() const {

    return this->current_bet_;
}

int Statistics_Manager::current_balance() const {

    return this->current_balance_;
}

void Statistics_Manager::set_current_balance(const int payout) {

    this->current_balance_ = payout;
}

void Statistics_Manager::set_current_bet(const int bet) {

    this->current_bet_ = bet;
}

void Statistics_Manager::set_total_profit(const int profit) {

    this->total_profit_ = profit;
}

void Statistics_Manager::set_total_losses(const int losses) {

    this->total_losses_ = losses;
}

void Statistics_Manager::set_balances(const int balance) {

    this->current_balance_ = this->highest_balance_ = this->lowest_balance_ = this->beginning_balance_ = balance;
}

// Actions


void Statistics_Manager::SetCurrentBet() {

    int bet = 0;

    cout << "Dealer: How much would you like to bet? ($)" << endl;
    cin >> bet;

    while (bet > this->current_balance() || bet < 0){
        
        if (bet < 0){

            //cout << "Dealer: You can't make negative bets. Try Again" << endl;
        }

        if (bet > this->current_balance()){
            
            cout << "Dealer: Sorry, can't bet more than you have at the table." << endl;    
        }
        
        //cout << "Dealer: So how much are you really betting? ($)" << endl;
        cin >> bet; 
    }

    this->current_bet_ = bet;

    ++this->hands_played_;
}

void Statistics_Manager::UpdateBalance(const int game_result) {

    // Splits are very awkward - 3 splits ....,
    // Kept at 2 hands for now
    // Pass in hands played????
    // Better/Different way to do this???

    switch(game_result){ 
        case 0: // Naturals win                                                                
        this->current_balance_ += (this->NaturalsPayout() * this->current_bet_);
        ++this->hands_won_;
        ++this->naturals_hit_;
        break;
        
        case 1:  // standard & split hand win
        case 2:  // Double down win - the current_bet_ will be updated to reflect a double down bet                      
        this->current_balance_ += (2 * this->current_bet_);
        ++this->hands_won_;

        case 3: // standards loss
        case 4: // double down loss - the current_bet_ will be updated to reflect a double down bet                      
        this->current_balance_ -= (2 * this->current_bet_);
        ++this->hands_lost_;
        break;

        case 5:                                 // draw / shoves
        this->current_balance_ += this->current_bet_; // player gets their bet back
        ++this->hands_drawed_;
        break;

        default:
        cerr << "Statistics_Manager::UpdateBalance(): | Invalid game Result" << endl;
    }

    this->UpdateStatistics();
}

void Statistics_Manager::UpdateStatistics() {

    if (this->highest_balance_ < this->current_balance_){
        
       this->highest_balance_ = this->current_balance_;
    }

    if (this->current_balance_ < this->lowest_balance_){

        this->lowest_balance_ = this->current_balance_;
    }
}

void Statistics_Manager::UpdateEndGameStatistics() {

    if (this->beginning_balance_ < this->highest_balance_){

        this->set_total_profit(this->highest_balance_ - this->beginning_balance_);
    }

    if (this->lowest_balance_ < this->beginning_balance_){

        this->set_total_losses(this->beginning_balance_ - this->lowest_balance_);
    }
}

void Statistics_Manager::DisplayGameStatisitics() const {

    cout << "END OF GAME STATISTICS" << endl;
    cout << " ";

    for (int i = 0; i < 30; i++) cout << '-';

    cout << "\n| Hands Played: " << setw(14) << this->hands_played_ << " |\n|" << setw(32) << "|\n";

    cout << "| Hands Won: " << setw(17) << this->hands_won_ << " |\n|" << setw(32) << "|\n"; 

    cout << "| Hands Lost: " << setw(16) << this->hands_lost_ << " |\n|" << setw(32) << "|\n";

    cout << "| Hands Drew: " << setw(16) << this->hands_drawed_ << " |\n|" << setw(32) << "|\n";  

    cout << "| Naturals Hit: " << setw(14) << this->naturals_hit_ << " |\n|" << setw(32) << "|\n"; 

    cout << "| Starting Balance: " << setw(10) << this->beginning_balance_ << " |\n|" << setw(32) << "|\n"; 
    
    cout << "| Profit: " << setw(20) << this->total_profit_ << " |\n|" << setw(32) << "|\n";

    cout << "| Total Losses: " << setw(14) << this->total_losses_ << " |\n|" << setw(32) << "|\n";

    cout << "| Highest Balance: " << setw(11) << this->highest_balance_ << " |\n|" << setw(32) << "|\n";
    
    cout << "| Lowest Balance: " << setw(12) << this->lowest_balance_ << " |\n|" << setw(33) << "|\n "; 
    
    for (int i = 0; i < 30; i++) cout << '-';
    cout << endl;
}

// Private Memeber Functions
int Statistics_Manager::NaturalsPayout() {

    return this->current_bet_ * kNaturalsPayoutRate;
}




