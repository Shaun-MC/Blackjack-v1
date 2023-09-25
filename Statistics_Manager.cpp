#include "Statistics_Manager.h"

#include <iostream>
#include <iomanip>

using namespace std;

StatsManager::StatsManager(){  // untested

    beginningBalance = currentBalance = currentBet = 0;

    handsPlayed = handsWon = handsLost = handsDrawed = 0;

    naturalsHit = 0;

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

void StatsManager::setBeginningBalance(){ 

    cout << "Dealer: Please offer a starting balance ($100 Minimum)" << endl;
    cin >> beginningBalance;

    while (beginningBalance <= 100 || beginningBalance < 0){
        
        if (beginningBalance < 0){

            cout << "Dealer: So then why are you here?" << endl;
        }

        cout << "Dealer: So how much are you really putting up?" << endl;
        cin >> beginningBalance;
    }

    currentBalance = beginningBalance;
    
    highestBalance = beginningBalance;
    lowestBalance = beginningBalance;
}

void StatsManager::setBet(){

    cout << "Dealer: So how much would you like to bet? ($)" << endl;
    cin >> currentBet;

    while (currentBet > currentBalance || currentBet < 0){
        
        if (currentBet < 0){

            cout << "Dealer: You can't do that." << endl;
        }

        if (currentBet > currentBalance){
            
            cout << "Dealer: Sorry, can't bet more than you have at the table." << endl;    
        }
        
        cout << "Dealer: So how much are you really betting? ($)" << endl;
        cin >> currentBet; 
    }

    ++handsPlayed;
}

void StatsManager::updateBalance(int gameResult){ // untested
    
    //error checking
    switch(gameResult){ 
        case 0:                                // natural                                                        // natural 
        currentBalance += naturalsPayout();
        
        ++handsWon;
        ++naturalsHit;
        
        break;
        case 1:                                 // standard & 1 split hand win
        
        break;

        case 2:                                 // double down & both splits hands win
        break;

        case 3:                                 // double down & both split hands loss
        break;

        case 4:                                 // standards loss

        currentBalance -= currentBet;
        ++handsLost;
        
        break;

        case 5:                                 // draw??
        break;

        default:
        cout << "ERROR in updateBalance(): unknown gameResult" << endl;
    }

    updateStatistics();
}

void StatsManager::updateStatistics() {

    if (highestBalance < currentBalance){
        
        highestBalance = currentBalance;
    }

    if (currentBalance < lowestBalance){

        lowestBalance = currentBalance;
    }
}

void StatsManager::updateFinalStatistics(){

    if (beginningBalance < highestBalance){

        totalProfit = highestBalance - beginningBalance;
    }

    if (lowestBalance < beginningBalance){

        totalLosses = beginningBalance - lowestBalance;
    }
}
void StatsManager::printGameStats() const { // untested
    
    cout << "END OF GAME STATISTICS" << endl;
    cout << " ";

    for (int i = 0; i < 30; i++) cout << '-';

    cout << "\n| Hands Played: " << setw(14) << handsPlayed << " |\n|" << setw(32) << "|\n";

    cout << "| Hands Won: " << setw(17) << handsWon << " |\n|" << setw(32) << "|\n"; 

    cout << "| Hands Lost: " << setw(16) << handsLost << " |\n|" << setw(32) << "|\n";

    cout << "| Hands Drew: " << setw(16) << handsDrawed << " |\n|" << setw(32) << "|\n";  

    cout << "| Naturals Hit: " << setw(14) << naturalsHit << " |\n|" << setw(32) << "|\n"; 

    cout << "| Starting Balance: " << setw(10) << beginningBalance << " |\n|" << setw(32) << "|\n"; 
    
    cout << "| Profit: " << setw(20) << totalProfit << " |\n|" << setw(32) << "|\n";

    cout << "| Total Losses: " << setw(14) << totalLosses << " |\n|" << setw(32) << "|\n";

    cout << "| Highest Balance: " << setw(11) << highestBalance << " |\n|" << setw(32) << "|\n";
    
    cout << "| Lowest Balance: " << setw(12) << lowestBalance << " |\n|" << setw(33) << "|\n "; 
    
    for (int i = 0; i < 30; i++) cout << '-';
    cout << endl;
}