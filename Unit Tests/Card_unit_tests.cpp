#include <iostream>
#include <sstream>
#include <iomanip>

#include "Card.h"

using namespace std;

bool ConstructorTest1() { // Heart & Ace initialization

    Card card1(1,1);

    return (card1.suit_character() == "\u2665" && card1.value() == 1 && 
            card1.card_character() == "A");
}

bool ConstructorTest2() { // Diamond & Jack initialization

    Card card2(2,11);

    return (card2.suit_character() == "\u2666" && card2.value() == 10 && 
            card2.card_character() == "J");
}

bool ConstructorTest3() { // Club & Queen initialization

    Card card3(3,12);

    return (card3.suit_character() == "\u2663" && card3.value() == 10 && 
            card3.card_character() == "Q");
}

bool ConstructorTest4() { // Spade & King initialization

    Card card4(4,13);

    return (card4.suit_character() == "\u2660" && card4.value() == 10 && 
            card4.card_character() == "K");
}

bool ConstructorTest5() { // value == 2 through 10 (less than 11)

    Card card5(2,5);

    return (card5.suit_character() == "\u2666" && card5.value() == 5 && 
            card5.card_character() == "5");
}

bool EqualityTest1() { // Suits are not equal

    Card card6(1,5);
    Card card7(2,5);

    return !(card6 == card7);
}

bool EqualityTest2() { // Values are not equal

    Card card8(1, 10);
    Card card9(1,9);

    return !(card8 == card9);
}

bool EqualityTest3() { // Card character's are not equal 

    Card card10(1, 10);
    Card card11(1, 12);

    return !(card10 == card11);
}

bool OStreamTest1() { // Standard

    Card card12(2,10);
    
    string display = "\u266610";
    stringstream console_display;

    console_display << card12;

    return display == console_display.str();
}

bool OStreamTest2() { // For the sake of it

    Card card13(4,1);

    string display = "\u2660A";
    stringstream console_display;

    console_display << card13;

    return display == console_display.str();
}

int main() {

    cout << endl;
    cout << "Parameterized Constructor Test 1: ";
    cout << ((ConstructorTest1()) ? "PASSED" : "FAILED") << endl;
    
    cout << "Parameterized Constructor Test 2: ";
    cout << ((ConstructorTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "Parameterized Constructor Test 3: ";
    cout << ((ConstructorTest3()) ? "PASSED" : "FAILED") << endl;

    cout << "Parameterized Constructor Test 4: ";
    cout << ((ConstructorTest4()) ? "PASSED" : "FAILED") << endl;

    cout << "Parameterized Constructor Test 5: ";
    cout << ((ConstructorTest5()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "Equality Test 1: " << setw(23);
    cout << ((EqualityTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "Equality Test 2: " << setw(23);
    cout << ((EqualityTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "Equality Test 3: " << setw(23);
    cout << ((EqualityTest3()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "Output Stream Operator Test 1: " << setw(9);
    cout << ((OStreamTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "Output Stream Operator Test 2: " << setw(9);
    cout << ((OStreamTest2()) ? "PASSED" : "FAILED") << endl << endl;

    return 0;
}