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

    return deck1.length() == 52;
}

bool DestructorTest() { // 

    Deck deck2;

    deck2.~Deck();

    return deck2.length() == 0;
}

bool RemoveCardTest1() { // 0 Node Deck

    Deck deck3(1);

    deck3.AddCard(kCard1);

    deck3.RemoveCard(kCard1);

    return deck3.length() == 0;
}

bool RemoveCardTest2() { // Removal at the head_

    Deck deck4;

    return (deck4.RemoveCard(kCard1) && deck4.TestConnections());
}

bool RemoveCardTest3() { // Removal at the tail_

    Deck deck5;

    return (deck5.RemoveCard(kCard2) && deck5.TestConnections());
}

bool RemoveCardTest4() { // Removal somewhere in the middle of the list

    Deck deck6;

    return (deck6.RemoveCard(kCard3) && deck6.TestConnections());
}

bool RemoveCardTest5() { // Removal closer to tail_

    Deck deck7;

    return (deck7.RemoveCard(kCard4) && deck7.TestConnections());
}

bool RemoveCardTest6() { // Removal closer to head_

    Deck deck8;

    return (deck8.RemoveCard(kCard5) && deck8.TestConnections());
}

bool RemoveCardTest7() { // Card not in the list

    Deck deck9;

    deck9.RemoveCard(kCard5);

    return (!deck9.RemoveCard(kCard5) && deck9.TestConnections());
}

bool RetrieveCardTest1() { // Retrieve the head_ card

    Deck deck10;
    Card retrival_card;

    deck10.RetrieveCard(retrival_card, 1); // Retrieving Ace of Hearts

    return retrival_card == kCard1;
}

bool RetrieveCardTest2() { // Retrieve the tail_ card

    Deck deck11; 
    Card retrival_card;

    deck11.RetrieveCard(retrival_card, 52);

    return retrival_card == kCard2;
}

bool RetrieveCardTest3() { // Card closer to head_

    Deck deck12;
    Card retrival_card;

    deck12.RetrieveCard(retrival_card, 9);

    return retrival_card == kCard5;
}

bool RetrieveCardTest4() { // Card closer to tail_

    Deck deck13;
    Card retrival_card;

    deck13.RetrieveCard(retrival_card, 31);

    return retrival_card == kCard4;
}

bool RetrieveCardTest5() { // Card has already been retrieved - create new random_tags

    Deck deck14;
    Card retrival_card1;
    Card retrival_card2;

    deck14.RetrieveCard(retrival_card1, 1);
    deck14.RetrieveCard(retrival_card2, 1);

    return retrival_card1 != retrival_card2;
}

bool DisplayDeckTest1() { // Display the entire Deck

    Deck deck15;
    
    cout << endl;
    deck15.DisplayDeck();

    return true; // Ehh
}

bool DisplayDeckTest2() { // Remove 1 card from each suit

    Deck deck16;
    
    deck16.RemoveCard(kCard1);
    deck16.RemoveCard(kCard2);
    deck16.RemoveCard(kCard3);
    deck16.RemoveCard(kCard4);

    cout << endl;
    deck16.DisplayDeck();

    return deck16.length() == 48; // Fine
}

bool DisplayDeckTest3() { // Remove 20 cards

    Deck deck17;

    for (int i = 0; i < 21; i++) {

        Card retrieve_card;

        deck17.RetrieveCard(retrieve_card, 0);
    }
    
    cout << endl;

    deck17.DisplayDeck();

    return deck17.length() == 31;
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

        Card retrieval_card;

        deck20.RetrieveCard(retrieval_card, 0);
    }

    return deck20.TestConnections();
}

bool TestConnectionsTest4() { // 40 removed cards

    Deck deck21;

    for (int i = 0; i < 21; i++) {

        Card retrieval_card;

        deck21.RetrieveCard(retrieval_card, 0);
    }

    return deck21.TestConnections();
}

int main() {

    cout << endl;

    cout << "Constructor Test: " << setw(12);
    cout << ((ConstructorTest()) ? "PASSED" : "FAILED") << endl;
    
    cout << "Destructor Test: " << setw(13);
    cout << ((DestructorTest()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "RemoveCard Test 1: " << setw(11);
    cout << ((RemoveCardTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "RemoveCard Test 2: " << setw(11);
    cout << ((RemoveCardTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "RemoveCard Test 3: " << setw(11);
    cout << ((RemoveCardTest3()) ? "PASSED" : "FAILED") << endl;

    cout << "RemoveCard Test 4: " << setw(11);
    cout << ((RemoveCardTest4()) ? "PASSED" : "FAILED") << endl;

    cout << "RemoveCard Test 5: " << setw(11);
    cout << ((RemoveCardTest5()) ? "PASSED" : "FAILED") << endl;

    cout << "RemoveCard Test 6: " << setw(11);
    cout << ((RemoveCardTest6()) ? "PASSED" : "FAILED") << endl;

    cout << "RemoveCard Test 7: " << setw(11);
    cout << ((RemoveCardTest7()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "RetrieveCard Test 1: " << setw(9);
    cout << ((RetrieveCardTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "RetrieveCard Test 2: " << setw(9);
    cout << ((RetrieveCardTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "RetrieveCard Test 3: " << setw(9);
    cout << ((RetrieveCardTest3()) ? "PASSED" : "FAILED") << endl;

    cout << "RetrieveCard Test 4: " << setw(9);
    cout << ((RetrieveCardTest4()) ? "PASSED" : "FAILED") << endl;

    cout << "RetrieveCard Test 5: " << setw(9);
    cout << ((RetrieveCardTest5()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "DisplayDeck Test 1: ";
    cout << ((DisplayDeckTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "DisplayDeck Test 2: ";
    cout << ((DisplayDeckTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "DisplayDeck Test 3: ";
    cout << ((DisplayDeckTest3()) ? "PASSED" : "FAILED") << endl << endl;


    cout << "TestConnections Test 1: ";
    cout << ((TestConnectionsTest1()) ? "PASSED" : "FAILED") << endl;

    cout << "TestConnections Test 2: ";
    cout << ((TestConnectionsTest2()) ? "PASSED" : "FAILED") << endl;

    cout << "TestConnections Test 3: ";
    cout << ((TestConnectionsTest3()) ? "PASSED" : "FAILED") << endl;

    cout << "TestConnections Test 4: ";
    cout << ((TestConnectionsTest4()) ? "PASSED" : "FAILED") << endl;

    return 0;
}