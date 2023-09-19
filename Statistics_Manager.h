#ifndef STATISTICS_MANAGER_H
#define STATISTICS_MANAGER_H

const float naturalsPayoutRate = 1.5;

class StatsManager{
    public:

    StatsManager() ;
    //~StatsManager();    // unnecessary??? - not using new & variables are only ints
    StatsManager(const StatsManager& rightInstance);

    void operator = (const StatsManager& rightInstance);
    void operator += (const StatsManager& rightInstance);

    void setBeginningBalance();
    void setBet();

    void updateBalance(const int gameResult);

    int naturalsPayout() { return currentBet * naturalsPayoutRate; }

    void printCurrentStats() const;

    //updateFunctions

    private:
    int beginningBalance;
    int currentBalance;
    int currentBet;

    unsigned int handsPlayed;
    unsigned int handsWon;
    unsigned int handsLost;
    unsigned int handsDrawed;

    unsigned naturalsHit;        

    int highestBalance;
    int lowestBalance;
    int totalLosses;
    int totalProfit; 
};

#endif