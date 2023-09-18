#include "Statistics_Manager.h"

#include <iostream>
#include <iomanip>

StatsManager::StatsManager(){  // untested

    beginningBalance = 0;

    handsPlayed = handsWon = handsLost = handsDrawed = 0;

    naturalsHit = currentBalance = currentBet = 0;

    highestBalance = lowestBalance = totalLosses = totalProfit = 0; 
}

/*Player::StatsManager::~StatsManager(){ 

}*/

StatsManager::StatsManager(const StatsManager& rightInstance){ // untested

    this->beginningBalance = rightInstance.beginningBalance;

    this->currentBalance = rightInstance.currentBalance;

    this->currentBet = rightInstance.currentBet;

    this->handsPlayed = rightInstance.handsPlayed;

    this->handsWon = rightInstance.handsWon;

    this->handsLost = rightInstance.handsLost;

    this->handsDrawed = rightInstance.handsDrawed;

    this->naturalsHit = rightInstance.naturalsHit;

    this->totalProfit = rightInstance.totalProfit;

    this->totalLosses = rightInstance.totalLosses;

    this->highestBalance = rightInstance.highestBalance;

    this->lowestBalance = rightInstance.lowestBalance;
}

void StatsManager::operator = (const StatsManager& rightInstance){

    this->beginningBalance = rightInstance.beginningBalance;

    this->currentBalance = rightInstance.currentBalance;

    this->currentBet = rightInstance.currentBet;

    this->handsPlayed = rightInstance.handsPlayed;

    this->handsWon = rightInstance.handsWon;

    this->handsLost = rightInstance.handsLost;

    this->handsDrawed = rightInstance.handsDrawed;

    this->naturalsHit = rightInstance.naturalsHit;

    this->totalProfit = rightInstance.totalProfit;

    this->totalLosses = rightInstance.totalLosses;

    this->highestBalance = rightInstance.highestBalance;

    this->lowestBalance = rightInstance.lowestBalance;
}

void StatsManager::operator += (const StatsManager& rightInstance){

    this->beginningBalance += rightInstance.beginningBalance;

    this->currentBalance += rightInstance.currentBalance;

    this->currentBet += rightInstance.currentBet;

    this->handsPlayed += rightInstance.handsPlayed;

    this->handsWon += rightInstance.handsWon;

    this->handsLost += rightInstance.handsLost;

    this->handsDrawed += rightInstance.handsDrawed;

    this->naturalsHit += rightInstance.naturalsHit;

    this->totalProfit += rightInstance.totalProfit;

    this->totalLosses += rightInstance.totalLosses;

    this->highestBalance += rightInstance.highestBalance;

    this->lowestBalance += rightInstance.lowestBalance;
}

void StatsManager::setBeginningBalance(){ // untested

    int balanceVal = 0;
    cout << "Dealer: Please offer a starting balance ($100 Minimum)" << endl;
    cin >> balanceVal;

    while (balanceVal <= 100){
        
        cout << "Dealer: Starting Balances of Only 100 or Greater are Allowed at this Table." << endl;
        cin >> balanceVal;
    }
}

void StatsManager::printCurrentStats() const { // untested
    
    for (int i = 0; i < 30; i++) cout << '-';

    cout << "\n| Hands Played: " << setw(14) << totalProfit << " |\n|" << setw(32) << "|\n";

    cout << "| Hands Won: " << setw(17) << handsWon << " |\n|" << setw(32) << "|\n"; 

    cout << "| Hands Lost: " << setw(16) << handsLost << " |\n|" << setw(32) << "|\n";

    cout << "| Hands Drew: " << setw(16) << handsDrawed << " |\n|" << setw(32) << "|\n";  

    cout << "| Naturals Hit: " << setw(14) << naturalsHit << " |\n|" << setw(32) << "|\n\n"; 

    cout << "| Starting Balance: " << setw(10) << beginningBalance << " |\n|" << setw(32) << "|\n"; 
    
    cout << "| Profit: " << setw(20) << handsPlayed << " |\n|" << setw(32) << "|\n";

    cout << "| Total Losses: " << setw(14) << totalLosses << " |\n|" << setw(32) << "|\n";

    cout << "| Highest Balance: " << setw(11) << highestBalance << " |\n|" << setw(32) << "|\n";
    
    cout << "| Lowest Balance: " << setw(12) << lowestBalance << " |\n|" << setw(33) << "|\n "; 
    
    for (int i = 0; i < 30; i++) cout << '-';
    cout << endl;
}