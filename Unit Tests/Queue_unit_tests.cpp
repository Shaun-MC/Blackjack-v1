#include <iostream>
#include <iomanip>

#include "Queue.h"

using namespace std;

const Card kCard1(1,1); // Ace of Hearts
const Card kCard2(2,1); // Ace of Diamonds

// TODO: Add Tests For front() & back()
// TODO: Add Tests For DisplayQueue()

bool CopyConstructorTest1() {

    Queue hand1;

    hand1.Push(kCard1);
    hand1.Push(kCard2);

    Queue hand2(hand1);

    return hand2 == hand1;
}

bool CopyConstructorTest2() {

    Queue hand3;

    hand3.Push(kCard1);
    hand3.Push(kCard2);

    Queue hand4 = hand3;

    return hand4 == hand3;
}

bool AssignmentOpTest1() { // this == &rval

    Queue hand5, hand6;
    
    hand5.Push(kCard1);
    hand5.Push(kCard2);
    
    hand6.Push(kCard1);
    hand6.Push(kCard2);

    hand5 = hand5;

    return hand6 == hand5; // Ehh
}

bool AssignmentOpTest2() { // rval is Empty

    Queue hand7, hand8, hand9;

    hand7.Push(kCard1);
    hand7.Push(kCard2);

    hand7 = hand8;

    return hand7 == hand9;
}

bool AssignmentOpTest3() { // straight transfer

    Queue hand10, hand11, hand12;

    for (int i = 0; i < 5; i++) {

        hand10.Push(kCard2);
        hand11.Push(kCard2);
    }

    for (int j = 0; j < 3; j++) {

        hand12.Push(kCard1);
    }

    hand12 = hand10;

    return hand12 == hand11;
}

bool AssignmentOpTest4() { // accounting for rval being circular

    Queue hand13, hand14;

    for (int i = 0; i < 8; i++) {

        hand13.Push(kCard1);
    }

    for (int j = 0; j < 3; j++) {

        hand13.Pop();
    }

    for (int k = 0; k < 4; k++) {

        hand13.Push(kCard2);
    }
   
    hand14 = hand13;

    return hand14 == hand13;
}

bool FrontTest() {

    Queue hand;
    Card temp;

    hand.Push(kCard1);

    temp = hand.front();

    return temp == kCard1;
}

bool BackTest1() { // Queue of length 1

    Queue hand;
    Card temp;

    hand.Push(kCard1);

    temp = hand.back();

    return temp == kCard1;
}

bool BackTest2() { // Queue with a lenght more than 1

    Queue hand;
    Card temp;

    hand.Push(kCard1);
    hand.Push(kCard2);

    temp = hand.back();

    return temp == kCard2;
}

bool PopTest1() { // Empty Queue

    Queue hand15;

    return !hand15.Pop();
}

bool PopTest2() { // Not Empty Queue

    Queue hand16;

    hand16.Push(kCard2);
    hand16.Pop();

    return hand16.length() == 0;
}

bool PushTest1() { // Empty Queue

    Queue hand18;

    hand18.Push(kCard1);

    return hand18.length() == 1;
}

bool PushTest2() { // Queue w/ 1 element & Pushing under the vec_ size

    Queue hand20;

    hand20.Push(kCard1);
    hand20.Push(kCard2);

    return hand20.length() == 2;
}

bool PushTest3() { // Doubling the queue size

    Queue hand22;

    for (int i = 0; i < 20; i++) {

        hand22.Push(kCard1);
    }

    return hand22.length() == 20;
}

bool EqualityTest1() { // Same object

    Queue hand23;

    return hand23 == hand23;
}

bool EqualityTest2() { // Both have 0 length

    Queue hand24, hand25;

    return hand24 == hand25;
}

bool EqualityTest3() { // Differnt sizes

    Queue hand25, hand26;

    for (int i = 0; i < 5; i++) {

        hand25.Push(kCard1);
    }

    return !(hand25 == hand26);
}

bool EqualityTest4() { // Differnt lengths

    Queue hand27, hand28;

    hand27.Push(kCard1);

    return !(hand27 == hand28);
}

bool EqualityTest5() { // Disimilar Queues - no wrap around

    Queue hand29, hand30;

    for (int i = 0; i < 2; i++) {

        hand29.Push(kCard1);
        hand30.Push(kCard2);
    }

    return !(hand29 == hand30);
}

bool EqualityTest6() {  // Disimilar Queues - wrap around

    Queue hand31, hand32;

    for (int i = 0; i < 5; i++) {

        hand31.Push(kCard1);
        hand32.Push(kCard1);
    }

    hand31.Pop();

    hand31.Push(kCard2);

    return !(hand31 == hand32);
}

bool EqualityTest7() { // Similar Queues - no wrap around

    Queue hand33, hand34;

    for (int i = 0; i < 10; i++) {

        hand33.Push(kCard1);
        hand34.Push(kCard1);
    }

    return hand33 == hand34;
}

bool EqualityTest8() {  // Similar Queues - wrap around

    Queue hand35, hand36;

    for (int i = 0; i < 10; i++) {

        hand35.Push(kCard1);
        hand36.Push(kCard1);
    }

    hand35.Pop();
    hand36.Pop();

    hand35.Push(kCard2);
    hand36.Push(kCard2);

    return hand35 == hand36;
}
int main() {

    cout << endl;

    cout << "Copy Constructor Test 1: " << setw(9);
    cout << ((CopyConstructorTest1()) ? "PASSED" : "FAILED") << endl;
    

    cout << "Copy Constructor Test 2: " << setw(9);
    cout << ((CopyConstructorTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "Assignment Operator Test 1: ";
    cout << ((AssignmentOpTest1()) ? "PASSED" : "FAILED") << endl;
    
    cout << "Assignment Operator Test 2: ";
    cout << ((AssignmentOpTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "Assignment Operator Test 3: ";
    cout << ((AssignmentOpTest3()) ? "PASSED" : "FAILED") << endl;

    cout << "Assignment Operator Test 4: ";
    cout << ((AssignmentOpTest4()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "Front Test: " << setw(22);
    cout << ((FrontTest()) ? "PASSED" : "FAILED") << endl;

    cout << "Back Test 1: " << setw(21);
    cout << ((BackTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "Back Test 2: " << setw(21);
    cout << ((BackTest2()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "Pop Test 1: " << setw(22);
    cout << ((PopTest1()) ? "PASSED" : "FAILED") << endl;
    
    cout << "Pop Test 2: " << setw(22);
    cout << ((PopTest2()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "Push Test 1: " << setw(21);
    cout << ((PushTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "Push Test 2: " << setw(21);
    cout << ((PushTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "Push Test 3: " << setw(21);
    cout << ((PushTest3()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "Equality Test 1: " << setw(17);
    cout << ((EqualityTest1()) ? "PASSED" : "FAILED") << endl;
    
    cout << "Equality Test 2: " << setw(17);
    cout << ((EqualityTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "Equality Test 3: " << setw(17);
    cout << ((EqualityTest3()) ? "PASSED" : "FAILED") << endl;

    cout << "Equality Test 4: " << setw(17);
    cout << ((EqualityTest4()) ? "PASSED" : "FAILED") << endl;

    cout << "Equality Test 5: " << setw(17);
    cout << ((EqualityTest5()) ? "PASSED" : "FAILED") << endl;

    cout << "Equality Test 6: " << setw(17);
    cout << ((EqualityTest6()) ? "PASSED" : "FAILED") << endl;

    cout << "Equality Test 7: " << setw(17);
    cout << ((EqualityTest7()) ? "PASSED" : "FAILED") << endl;

    cout << "Equality Test 8: " << setw(17);
    cout << ((EqualityTest8()) ? "PASSED" : "FAILED") << endl << endl;

    return 0;
}