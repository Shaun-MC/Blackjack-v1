#include <iostream>
#include <iomanip>
#include <string>

#include "Hand.h"

using namespace std;

// TODO: Make DisplayTests 'testable' - stringstreams?, make it look better

const Card card1(1, 7);  // 7 of Hearts
const Card card2(2, 10); // 10 of Diamonds
const Card card3(3, 1);  // Ace of Clubs
const Card card4(4, 12); // Queen of Spades
const Card card5(2, 2);  // 2 of Diamonds

bool CopyConstructorTest1() { // Innvocation #1

    Hand hand1;

    hand1.AddCardToHand(card1);
    hand1.AddCardToHand(card2);

    Hand hand2(hand1);

    return hand2 == hand1;
}

bool CopyConstructorTest2() { // Innvocation #2

    Hand hand3;

    hand3.AddCardToHand(card3);
    hand3.AddCardToHand(card4);
    hand3.AddCardToHand(card1);

    Hand hand4 = hand3;

    return hand4 == hand3;
}

bool AssignmentOpTest1() { // Innvocation

    Hand hand5;

    for (int i = 0; i < 4; i++ ) {

        hand5.AddCardToHand(card2);
    }

    Hand hand6;
    hand6 = hand5;

    return hand5 == hand6;
}

bool AddCardToHandTest1() { // Standard push

    Hand hand7;

    hand7.AddCardToHand(card4);

    return hand7.count() == 1;
}

bool AddCardToHandTest2() { // Adding an Ace

    Hand hand8;

    hand8.AddCardToHand(card3);

    return (hand8.count() == 1 && hand8.ace_counter() == 1);
}

bool RemoveCardFromHandTest1() { // Removing an Ace 

    Hand hand9, hand10;

    hand9.AddCardToHand(card3);
    hand9.AddCardToHand(card4);

    hand9.RemoveCardFromHand();

    hand10.AddCardToHand(card4);

    return hand10 == hand9;
}

bool RemoveCardFromHandTest2() { // Removing an Ace from a Hand w/ another Ace in the Hand

    Hand hand11, hand12;

    for (int i = 0; i < 2; i++) {
    
        hand11.AddCardToHand(card3);    
    }

    hand11.RemoveCardFromHand();

    hand12.AddCardToHand(card3);

    return hand11 == hand12;
}

bool RemoveCardFromHandTest3() { // Removing a 10 value card - no ace in hand

    Hand hand13, hand14;

    for (int i = 0; i < 2; i++) {

        hand13.AddCardToHand(card4);
    }

    hand13.RemoveCardFromHand();

    hand14.AddCardToHand(card4);

    return hand13 == hand14;
}

bool RemoveCardFromHandTest4() { // Removing a 10 value card - ace in hand

    Hand hand15, hand16;

    hand15.AddCardToHand(card4);
    hand15.AddCardToHand(card3);

    hand15.RemoveCardFromHand();

    hand16.AddCardToHand(card3);

    return hand15 == hand16;
}

bool RemoveCardFromHandTest5() { // Removing a card value 2-9 - no ace in hand

    Hand hand17, hand18;

    for (int i = 0; i < 2; i++) {

        hand17.AddCardToHand(card1);
    }

    hand17.RemoveCardFromHand();

    hand18.AddCardToHand(card1);

    return hand17 == hand18;
}

bool RemoveCardFromHandTest6() { // Removing a card value 2-9 - ace in hand

    Hand hand19, hand20;

    hand19.AddCardToHand(card1);
    hand19.AddCardToHand(card3);

    hand19.RemoveCardFromHand();

    hand20.AddCardToHand(card3);

    return hand19 == hand20;
}

bool DisplayHandTest1() { // Hand has an Ace

    Hand hand21;

    hand21.AddCardToHand(card4);
    hand21.AddCardToHand(card3);

    cout << endl;
    hand21.DisplayHand();

    string display = "Current Hand Total: 11 OR 21\n\u2660Q \u2663A <-- (Expected)";
    cout << display << endl;

    return true;
}

bool DisplayHandTest2() { // Hand doens't have an Ace

    Hand hand22;

    for (int i = 0; i < 2; i++) {

        hand22.AddCardToHand(card1);
    }

    cout << endl;
    hand22.DisplayHand();

    string display = "Current Hand Total: 14 \n\u26657 \u26657 <-- (Expected)";
    cout << display << endl;

    return true;
}

bool UpdateHandTotalTest1() { // Hand has 1 card 

    Hand hand23;

    hand23.AddCardToHand(card1);

    return (hand23.hand_totals0() == 7 && hand23.hand_totals1() == 0);
}

bool UpdateHandTotalTest2() { // Newest card is an Ace - doesn't bust hand_totals[1]

    Hand hand24;

    hand24.AddCardToHand(card1);
    hand24.AddCardToHand(card3);

    return (hand24.hand_totals0() == 8 && hand24.hand_totals1() == 18);
}

bool UpdateHandTotalTest3() { // Newest card is an Ace - hand_totals[1] is irrelevant

    Hand hand25;
    
    hand25.AddCardToHand(card2);
    hand25.AddCardToHand(card2);
    hand25.AddCardToHand(card3);

    return (hand25.hand_totals0() == 21 && hand25.hand_totals1() == 0);
}

bool UpdateHandTotalTest4() { // hand_totals[1] becomes irrelevant because it busts

    Hand hand26;

    hand26.AddCardToHand(card3);
    hand26.AddCardToHand(card4);
    hand26.AddCardToHand(card5);

    return (hand26.hand_totals0() == 13 && hand26.hand_totals1() == 0);

    return true;
}

bool UpdateHandTotalTest5() { // Adding 10-value card to hand

    Hand hand27;

    hand27.AddCardToHand(card2);

    return (hand27.hand_totals0() == 10 && hand27.hand_totals1() == 0);
}

bool UpdateHandTotalTest6() { // Adding 2-9 value card to hand

    Hand hand28;

    hand28.AddCardToHand(card5);

    return (hand28.hand_totals0() == 2 && hand28.hand_totals1() == 0);
}

int main() {
    
    cout << endl;

    cout << "Copy Constructor Test 1: " << setw(9);
    cout << ((CopyConstructorTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "Copy Constructor Test 2: " << setw(9);
    cout << ((CopyConstructorTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "Assignment Operator Test 1: ";
    cout << ((AssignmentOpTest1()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "AddCardToHand Test 1: " << setw(12);
    cout << ((AddCardToHandTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "AddCardToHand Test 2: " << setw(12);
    cout << ((AddCardToHandTest2()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "RemoveCardFromHand Test 1: " << setw(7);
    cout << ((RemoveCardFromHandTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "RemoveCardFromHand Test 2: " << setw(7);
    cout << ((RemoveCardFromHandTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "RemoveCardFromHand Test 3: " << setw(7);
    cout << ((RemoveCardFromHandTest3()) ? "PASSED" : "FAILED") << endl;

    cout << "RemoveCardFromHand Test 4: " << setw(7);
    cout << ((RemoveCardFromHandTest4()) ? "PASSED" : "FAILED") << endl;

    cout << "RemoveCardFromHand Test 5: " << setw(7);
    cout << ((RemoveCardFromHandTest5()) ? "PASSED" : "FAILED") << endl;

    cout << "RemoveCardFromHand Test 6: " << setw(7);
    cout << ((RemoveCardFromHandTest6()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "DisplayHand Test 1: " << setw(14);
    cout << ((DisplayHandTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "DisplayHand Test 2: " << setw(14);
    cout << ((DisplayHandTest2()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "UpdateHandTotal Test 1:" << setw(11);
    cout << ((UpdateHandTotalTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "UpdateHandTotal Test 2:" << setw(11);
    cout << ((UpdateHandTotalTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "UpdateHandTotal Test 3:" << setw(11);
    cout << ((UpdateHandTotalTest3()) ? "PASSED" : "FAILED") << endl; 

    cout << "UpdateHandTotal Test 4:" << setw(11);
    cout << ((UpdateHandTotalTest4()) ? "PASSED" : "FAILED") << endl;

    cout << "UpdateHandTotal Test 5:" << setw(11);
    cout << ((UpdateHandTotalTest5()) ? "PASSED" : "FAILED") << endl;

    cout << "UpdateHandTotal Test 6:" << setw(11);
    cout << ((UpdateHandTotalTest6()) ? "PASSED" : "FAILED") << endl << endl;

    return 0;
}