#include <iostream>

#include "Queue.h"

using namespace std;

const Card card(1,1); // Ace of Hearts

bool ConstructorsTest() {

    Queue hand;

    hand.Push(card);

    Queue hand1(hand);

    if (hand1 != hand) {

        return false;
    }

    Queue hand2 = hand;

    if (hand2 != hand) {

        return false;
    }

    return true;
}

bool AssignmentOpTest() {


    return true;
}

bool FrontTest() {

    return true;
}

bool BackTest() {

    return true;
}

bool PopTest() {

    return true;
}

bool PushTest() {

    return true;
}

bool EqualityTest() {

    return true;
}

bool SimulatedHand1() {

    return true;
}

bool SimulatedHand2() {

    return true;
}

bool SimulatedHand3() {

    return true;
}

int main() {

    Queue hand;

    hand.Push(card);

    Queue hand1(hand);

    if (hand1 != hand) {

        return 0;
    }

    Queue hand2 = hand;

    if (hand2 != hand) {

        return 0;
    }

    return 1;

    cout << "Constructors and Assignemnt Operator Test: ";
    if (ConstructorsTest()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;


    cout << "Front-Getter Test: ";
    if (FrontTest()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;


    cout << "Back-Getter Test: ";
    if (FrontTest()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;


    cout << "Pop Test: ";
    if (PopTest()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;


    cout << "Push Test: ";
    if (PushTest()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    return 0;
}