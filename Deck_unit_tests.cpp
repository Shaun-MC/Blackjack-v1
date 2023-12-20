#include <iostream>
#include <iomanip>

#include "Deck.h"
#include "Card.h"

using namespace std;

// TODO: Make the 'Display' more testable???

bool ConstructorTest() {

    Deck deck1;

    return (deck1.length() == 52) ? true : false;
}

bool DestructorTest() { // the Leaks tool for Mac was used to determine if there is a memory leak 

    Deck deck2;

    deck2.~Deck();

    return (deck2.length() == 0) ? true : false;
}

bool RemoveCardTest1() { // 1 Node Deck


}

bool RemoveCardTest2() { // Removal at the head_


}

bool RemoveCardTest3() { // Removal at the tail_


}

bool RemoveCardTest4() { // Removal somewhere in the middle of the list


}

bool RemoveCardTest5() { // ^^^


}

bool RemoveCardTest6() { // ^^^

}

bool RemoveCardTest7() { // Card not in the list


}

bool RetrieveCardTest1() { // Retrieve the head_ card


}

bool RetrieveCardTest2() { // Retrieve the tail_ card


}

bool RetrieveCardTest3() { // Card closer to head_


}

bool RetrieveCardTest4() { // Card closer to tail_


}

bool RetrieveCardTest5() { // Card has already been retrieved - create new random_tags


}

bool DisplayDeckTest1() { // Display the entire Deck


}

bool DisplayDeckTest2() { // Remove 0-1 cards for each suit


}

bool DisplayDeckTest3() { // Remove 3-4 cards for each suit


}

bool DisplayDeckTest4() { // Remove 6-7 cards for each suit


}

bool TestConnectionsTest1() { // Entire deck


}

bool TestConnectionsTest2() { // 3 removed cards


}

bool TestConnectionsTest3() { // 9 removed cards


}

bool TestConnectionsTest4() { // 18 removed cards


}

int main() {

    cout << "Constructor Test: ";
    if (ConstructorTest()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }

    cout << "Destructor Test: ";
    if (DestructorTest()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
}