#include <iostream>
#include <iomanip>

#include "Dealer.h"
#include "Card.h"

const Card kCard1(1, 1);  // Ace of Hearts
const Card kCard2(2, 10); // 10 of Diamonds
const Card kCard3(3, 3);  // 3 of Clubs
const Card kCard4(4, 2);  // 2 of Spades
const Card kCard5(3, 9);  // 9 of Clubs

using namespace std;

bool ConstructorTest1() { // Default

    Dealer dealer1;

    return dealer1.hand_length() == 0;
}

bool ConstructorTest2() { // Parameterized

    Dealer dealer2(kCard1, kCard2);

    return dealer2.hand_length() == 2;
}

bool HandTotalTest1() { // BlackJack

    Dealer dealer3(kCard1, kCard2);

    return dealer3.hand_total() == 21;
}

bool HandTotalTest2() { // No aces - only value in Hand::hand_total0()

    Dealer dealer4(kCard2, kCard3);

    return dealer4.hand_total() == 13;
}

bool HandTotalTest3() { // Aces - value in Hand::hand_total1()

    Dealer dealer5(kCard3, kCard4);

    dealer5.ReceiveCard(kCard1);

    return dealer5.hand_total() == 16;
}

bool HandTotalTest4() { // Hand where hand_total1() zeros out

    Dealer dealer6(kCard1, kCard4);

    dealer6.ReceiveCard(kCard2);

    return dealer6.hand_total() == 13;
}

bool ReceiveCardTest1() { // Function uses Hand::AddCardToHand() - Tested in Hand_unit_tests.cpp

    Dealer dealer7;

    dealer7.ReceiveCard(kCard1);
    dealer7.ReceiveCard(kCard2);

    return dealer7.hand_length() == 2;
}

bool ReceiveCardTest2() { // Confidence test - ^^

    Dealer dealer8;

    dealer8.ReceiveCard(kCard3);
    dealer8.ReceiveCard(kCard3);
    dealer8.ReceiveCard(kCard1);
    dealer8.ReceiveCard(kCard1);
    dealer8.ReceiveCard(kCard4);

    return dealer8.hand_length() == 5;
}

bool PrintUpCardTest1() {

    Dealer dealer9(kCard1, kCard2);

    cout << endl;
    cout << kCard1 << "   <--Expected\n";

    dealer9.PrintUpCard();
    cout << endl;

    return true; // Ehh
}

bool PrintUpCardTest2() { // Confidence test

    Dealer dealer10(kCard4, kCard5);

    dealer10.ReceiveCard(kCard3);
    dealer10.ReceiveCard(kCard4);
    dealer10.ReceiveCard(kCard1);
    dealer10.ReceiveCard(kCard5);

    cout << endl;
    cout << kCard4 << "    <--Expected\n";

    dealer10.PrintUpCard();
    cout << endl;

    return true; // Ehh
}

bool NaturalsCheckTest1() { // Dealer has BlackJack

    Dealer dealer11(kCard1, kCard2);

    return dealer11.NaturalsCheck();
}

bool NaturalsCheckTest2() { // Dealer doens't have BlackJack

    Dealer dealer12(kCard4, kCard5);

    return !dealer12.NaturalsCheck();
}

bool BustTest1() { // Busted - No Aces

    Dealer dealer13(kCard2, kCard2); // Hand Total : 20

    dealer13.ReceiveCard(kCard4); // Hand Total : 22

    return dealer13.Bust();
}

bool BustTest2() { // Busted - Has Aces

    Dealer dealer14(kCard2, kCard3); // Hand Total : 13
    bool ret = false;

    dealer14.ReceiveCard(kCard1); // Hand Total : 14

    ret = (!dealer14.Bust()) ? true : false;

    if (!ret) {

        return ret;
    } else {

        dealer14.ReceiveCard(kCard2); // Hand total : 24;

        return dealer14.Bust();
    }
}

bool BustTest3() { // Hasn't Busted

    Dealer dealer15(kCard4, kCard5);

    return !dealer15.Bust(); // Hand Total : 11
}

bool StayTest1() { // Has to Stay - No Aces

    Dealer dealer16(kCard2, kCard2); // Hand Total : 20

    return dealer16.Stay();
}

bool StayTest2() { // Has to Stay - 'Hard 17'

    Dealer dealer17(kCard2, kCard3); // Hand Total : 13

    dealer17.ReceiveCard(kCard4); // Hand Total : 15
    dealer17.ReceiveCard(kCard4); // Hand Total : 17

    return dealer17.Stay();
}

bool StayTest3() { // Has to Stay - Aces / 'Soft 17'

    Dealer dealer18(kCard2, kCard3); // Hand Total : 13

    dealer18.ReceiveCard(kCard1); // Hand Total : 14
    dealer18.ReceiveCard(kCard3); // Hand Total : 17

    return dealer18.Stay();
}

bool StayTest4() { // Can't Stay

    Dealer dealer19(kCard3, kCard5); // Hand Total : 12

    return !dealer19.Stay();
}

int main() {

    cout << endl;

    cout << "Constructor Test 1: " << setw(8);
    cout << ((ConstructorTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "Constructor Test 2: " << setw(8);
    cout << ((ConstructorTest2()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "HandTotal Test 1: " << setw(10); 
    cout << ((HandTotalTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "HandTotal Test 2: " << setw(10);
    cout << ((HandTotalTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "HandTotal Test 3: " << setw(10);
    cout << ((HandTotalTest3()) ? "PASSED" : "FAILED") << endl;

    cout << "HandTotal Test 4: " << setw(10); 
    cout << ((HandTotalTest4()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "ReceiveCard Test 1: " << setw(8);
    cout << ((ReceiveCardTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "ReceiveCard Test 2: " << setw(8);
    cout << ((HandTotalTest2()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "PrintUpCard Test 1: ";
    cout << ((PrintUpCardTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "PrintUpCard Test 2: ";
    cout << ((PrintUpCardTest2()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "NaturalsCheck Test 1: ";
    cout << ((NaturalsCheckTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "NaturalsCheck Test 2: ";
    cout << ((NaturalsCheckTest2()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "BustCheck Test 1: " << setw(10);
    cout << ((BustTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "BustCheck Test 2: " << setw(10);
    cout << ((BustTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "BustCheck Test 3: " << setw(10);
    cout << ((BustTest3()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "Stay Test 1: " << setw(15);
    cout << ((StayTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "Stay Test 2: " << setw(15);
    cout << ((StayTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "Stay Test 3: " << setw(15);
    cout << ((StayTest3()) ? "PASSED" : "FAILED") << endl;

    cout << "Stay Test 4: " << setw(15);
    cout << ((StayTest4()) ? "PASSED" : "FAILED") << endl << endl;


    return 0;
}