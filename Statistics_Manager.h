#ifndef STATISTICS_MANAGER_H
#define STATISTICS_MANAGER_H

class StatsManager{
    public:

    StatsManager() ;
    //~StatsManager();    // unnecessary??? - not using new & variables are only ints
    StatsManager(const StatsManager& rightInstance);

    void operator = (const StatsManager& rightInstance);
    void operator += (const StatsManager& rightInstance);

    void setBeginningBalance();
    void printCurrentStats() const;

    //updateFunctions

    unsigned int beginningBalance;

    unsigned int handsPlayed;
    unsigned int handsWon;
    unsigned int handsLost;
    unsigned int handsDrawed;

    unsigned naturalsHit;        
    unsigned int currentBalance;
    unsigned int currentBet;

    int highestBalance;
    int lowestBalance;
    int totalLosses;
    int totalProfit; 
};

#endif