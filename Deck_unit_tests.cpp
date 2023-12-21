#include <iostream>
#include <iomanip>

#include "Deck.h"
#include "Card.h"

const Card kCard1(1, 1);  // Ace of Hearts    ~ initialized to head_ in InitializeDeck(...)
const Card kCard2(4, 13); // King of Spades   ~ initialized to tail_ in InitializeDeck(...)
const Card kCard3(2, 13); // King of Diamonds ~ Extact middle of the deck in InitializeDeck(...), tag == 26
const Card kCard4(3, 5);  // 5 of Clubs       ~ Closer to tail_ for RemoveCard(...) & RetrieveCard(...)
const Card kCard5(1, 9);  // Nine of Hearts   ~ Closer to head_ for RemoveCard(...) & RetrieveCard(...)

using namespace std;

// TODO: Make the 'Display' more testable???

bool ConstructorTest() {

    Deck deck1;

    return (deck1.length() == 52) ? true : false;
}

bool DestructorTest() { // To determine 

    Deck deck2;

    deck2.~Deck();

    return (deck2.length() == 0) ? true : false;
}

bool RemoveCardTest1() { // 1 Node Deck

    Deck deck3(1);

    deck3.AddCard(kCard1);

    deck3.RemoveCard(kCard1);

    return (deck3.length() == 0) ? true : false;
}

bool RemoveCardTest2() { // Removal at the head_

    Deck deck4;

    return (deck4.RemoveCard(kCard1) && deck4.TestConnections()) ? true : false;
}

bool RemoveCardTest3() { // Removal at the tail_

    Deck deck5;

    return (deck5.RemoveCard(kCard2) && deck5.TestConnections()) ? true : false;
}

bool RemoveCardTest4() { // Removal somewhere in the middle of the list

    Deck deck6;

    return (deck6.RemoveCard(kCard3) && deck6.TestConnections()) ? true : false;
}

bool RemoveCardTest5() { // Removal closer to tail_

    Deck deck7;

    return (deck7.RemoveCard(kCard4) && deck7.TestConnections()) ? true : false;
}

bool RemoveCardTest6() { // Removal closer to head_

    Deck deck8;

    return (deck8.RemoveCard(kCard5) && deck8.TestConnections()) ? true : false;
}

bool RemoveCardTest7() { // Card not in the list

    Deck deck9;

    deck9.RemoveCard(kCard5);

    return (!deck9.RemoveCard(kCard5) && deck9.TestConnections()) ? true : false;
}

bool RetrieveCardTest1() { // Retrieve the head_ card

    Deck deck10;
    Card* c_ptr = new Card();
    bool ret = false;

    deck10.RetrieveCard(c_ptr, 1); // Retrieving Ace of Hearts

    if (*c_ptr == kCard1) {

        ret = true;
    }

    delete c_ptr;
    
    return ret;
}

bool RetrieveCardTest2() { // Retrieve the tail_ card

    Deck deck11; 
    Card* c_ptr = new Card();
    bool ret = false;

    deck11.RetrieveCard(c_ptr, 52);

    if (*c_ptr == kCard2) {

        ret = true;
    }

    delete c_ptr;

    return ret;
}

bool RetrieveCardTest3() { // Card closer to head_

    Deck deck12;
    Card* c_ptr = new Card();
    bool ret = false;

    deck12.RetrieveCard(c_ptr, 9);

    if (*c_ptr == kCard5) {

        ret = true;
    }

    delete c_ptr;

    return ret;
}

bool RetrieveCardTest4() { // Card closer to tail_

    Deck deck13;
    Card* c_ptr = new Card();
    bool ret = false;

    deck13.RetrieveCard(c_ptr, 31);

    if (*c_ptr == kCard4) {

        ret = true;
    }

    delete c_ptr;

    return ret;
}

bool RetrieveCardTest5() { // Card has already been retrieved - create new random_tags

    Deck deck14;
    Card* c1_ptr = new Card();
    Card* c2_ptr = new Card();
    bool ret = false;

    deck14.RetrieveCard(c1_ptr, 1);
    deck14.RetrieveCard(c2_ptr, 1);

    if (*c1_ptr != *c2_ptr) {

        ret = true;
    }

    delete c1_ptr;
    delete c2_ptr;

    return ret;
}

bool DisplayDeckTest1() { // Display the entire Deck

    Deck deck15;
    
    cout << endl;
    deck15.DisplayDeck();

    return (deck15.length() == 52) ? true : false;
}

bool DisplayDeckTest2() { // Remove 1 card from each suit

    Deck deck16;
    
    deck16.RemoveCard(kCard1);
    deck16.RemoveCard(kCard2);
    deck16.RemoveCard(kCard3);
    deck16.RemoveCard(kCard4);

    cout << endl;
    deck16.DisplayDeck();

    return (deck16.length() == 48) ? true : false;
}

bool DisplayDeckTest3() { // Remove 20 cards

    Deck deck17;

    for (int i = 0; i < 21; i++) {

        Card* c_ptr = new Card();

        deck17.RetrieveCard(c_ptr, 0);

        delete c_ptr;
    }
    
    cout << endl;

    deck17.DisplayDeck();

    return (deck17.length() == 31) ? true : false;
}

bool TestConnectionsTest1() { // Entire deck

    Deck deck18;

    return deck18.TestConnections();
}

bool TestConnectionsTest2() { // 5 cards removed
    
    Deck deck19;

    deck19.RemoveCard(kCard1);
    deck19.RemoveCard(kCard2);
    deck19.RemoveCard(kCard3);
    deck19.RemoveCard(kCard4);
    deck19.RemoveCard(kCard5);

    return deck19.TestConnections();
}

bool TestConnectionsTest3() { // 20 removed cards

    Deck deck20;

    for (int i = 0; i < 21; i++) {

        Card* c_ptr = new Card();

        deck20.RetrieveCard(c_ptr, 0);

        delete c_ptr;
    }

    return deck20.TestConnections();
}

bool TestConnectionsTest4() { // 40 removed cards

    Deck deck21;

    for (int i = 0; i < 41; i++) {

        Card* c_ptr = new Card();
        
        deck21.RetrieveCard(c_ptr, 0);

        delete c_ptr;
    }

    return deck21.TestConnections();
}

int main() {

    cout << "Constructor Test: ";
    if (ConstructorTest()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "Destructor Test: ";
    if (DestructorTest()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl << endl;


    cout << "RemoveCard Test 1: ";
    if (RemoveCardTest1()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "RemoveCard Test 2: ";
    if (RemoveCardTest2()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "RemoveCard Test 3: ";
    if (RemoveCardTest3()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "RemoveCard Test 4: ";
    if (RemoveCardTest4()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "RemoveCard Test 5: ";
    if (RemoveCardTest5()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "RemoveCard Test 6: ";
    if (RemoveCardTest6()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "RemoveCard Test 7: ";
    if (RemoveCardTest7()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl << endl;


    cout << "RetrieveCard Test 1: ";
    if (RetrieveCardTest1()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "RetrieveCard Test 2: ";
    if (RetrieveCardTest2()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "RetrieveCard Test 3: ";
    if (RetrieveCardTest4()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "RetrieveCard Test 4: ";
    if (RetrieveCardTest4()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "RetrieveCard Test 5: ";
    if (RetrieveCardTest5()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl << endl;


    cout << "DisplayDeck Test 1: ";
    if (DisplayDeckTest1()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "DisplayDeck Test 2: ";
    if (DisplayDeckTest2()) { 

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "DisplayDeck Test 3: ";
    if (DisplayDeckTest3()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl << endl;


    cout << "TestConnections Test 1: ";
    if (TestConnectionsTest1()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "TestConnections Test 2: ";
    if (TestConnectionsTest2()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "TestConnections Test 3: ";
    if (TestConnectionsTest3()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl;

    cout << "TestConnections Test 4: ";
    if (TestConnectionsTest4()) {

        cout << "PASSED";
    } else {

        cout << "FAILED";
    }
    cout << endl << endl;

    return 0;
}