#include "Deck.h"

// TODO: Implement exceptions where appropreiate

// Constructor - Destructor
Deck::Deck() : length_(0) {

    this->head_ = this->tail_ = this->iterator_ = nullptr;

    this->InitializeDeck(0, 0, 0);
}

Deck::Deck(int skip_initializing) {

    this->head_ = this->tail_ = this->iterator_ = nullptr;

    this->length_ = 0;
}

Deck::~Deck() {

    Node* delete_node = this->head_;

    this->ResetIterator();

    while (delete_node != nullptr) {

        this->iterator_ = this->iterator_->next;

        delete delete_node->card;
        delete delete_node;

        --this->length_;

        delete_node = this->iterator_;
    }

    this->head_ = nullptr;
    this->tail_ = nullptr;
}

// Getter 
int Deck::length() const {

    return this->length_;
}

// Actions
bool Deck::InitializeDeck(int suit, int value, int tag) {

    if (tag == kDeckSize) {

        return false;
    } 
    
    if (tag == 0) {
    
        this->SetDeck(suit + 1, value + 1, tag + 1);
        
        return this->InitializeDeck(suit + 1, suit + 1, tag + 1);
    } else if (tag == 13 || tag == 26 || tag == 39) {

        this->SetDeck(suit + 1, 1, tag + 1);
        
        return this->InitializeDeck(suit + 1, 1, tag + 1);
    } else {

        this->SetDeck(suit, value + 1, tag + 1);
        
        return this->InitializeDeck(suit, value + 1, tag + 1);
    }
}

bool Deck::AddCard(const Card& card) {

    Node* insert_node = new Node();
    insert_node->card = new Card(card);
    insert_node->tag = (card.suit() > 1) ? (13 * (card.suit() - 1)) + card.face_value() : card.value();

    if (this->head_ == nullptr) { // O Nodes, Adding at the Front

        this->head_ = this->tail_ = insert_node;

    } else { // Multiple nodes, adding at the Back

        this->tail_->next = insert_node;
        insert_node->prev = this->tail_;

        this->tail_ = insert_node;
    }

    ++this->length_;
    
    return true;
}

bool Deck::RemoveCard(const Card& remove_card) { // UNTESTED

    if (this->head_ == nullptr) { // 0 Nodes

        cerr << "Deck::RemoveCard() | Attempting To Remove From an Empty List" << endl; // Exception ??
        return false;
    }

    if (this->head_ == this->tail_ && *(this->head_->card) == remove_card){ // 1 Node

        Node* delete_node = this->head_;

        delete delete_node;

        this->head_ = this->tail_ = nullptr;

        --this->length_;

        return true;
    } 

    if (*this->head_->card == remove_card) { // Removal At Head

        Node* delete_node = this->head_;

        this->head_ = this->head_->next;

        delete delete_node;

        this->head_->prev = nullptr;

        --this->length_;

        return true;
    }

    if (*this->tail_->card == remove_card) { // Removal at Tail

        Node* delete_node = this->tail_;

        this->tail_ = this->tail_->prev;

        delete delete_node;

        this->tail_->next = nullptr;

        --this->length_;

        return true;
    }

    ResetIterator();

    this->iterator_ = this->iterator_->next;

    while (this->iterator_ != this->tail_) { // If remove_card tag < head_ || remove_card tag > tail || is greater than iterator at any point

        if (*this->iterator_->card == remove_card) {  // Removal somewhere in the middle

            Node* delete_node = this->iterator_;

            this->iterator_->next->prev = delete_node->prev;
            this->iterator_->prev->next = delete_node->next;
            
            this->iterator_ = nullptr;
            
            delete delete_node;

            --this->length_;

            return true;
        } else {

            this->iterator_ = this->iterator_->next;
        }
    }

    return false; // Node not found in the list
}

void Deck::RetrieveCard(Card &ret_card, const int test_tag) { // Untested - O nodes, 1 nodes ...

    // So a random card can be retrieved from the list - simulating a shoe of cards
    int random_tag = 0; 
    
    // Error Checking for test_tag
    if (test_tag != 0) {

        random_tag = test_tag;
    } else {

        random_tag = CreateRandomTag();
    }

    // If a card w/ that random_tag has already been dealt - get another random_tag
    while (CheckUsedCardTags(random_tag)) {

        random_tag = CreateRandomTag();
    }
    
    // Which ever one is closer to the card w/ the random_tag - this->head_ OR this->tail_
    if (random_tag - this->head_->tag <= this->tail_->tag - random_tag) { 

        this->ResetIterator();
    } else {

        this->iterator_ = this->tail_;
    }

    // Move iterator into position
    if (this->iterator_ == this->head_) { // Starting from the head_

        while (this->iterator_->tag != random_tag) {

            this->iterator_ = this->iterator_->next;
        }
    } else {    // Starting from the tail_

        while (this->iterator_->tag != random_tag) {

            this->iterator_ = this->iterator_->prev;
        }
    }

    // The correct card has been located based on random_tag
    ret_card = *this->iterator_->card;

    // Add random_tag to the vector of used tags
    this->tag_list_.push_back(random_tag);

    // Remove card w/ random_tag from the list - same code as in RemoveCard();
    Node* delete_node = this->iterator_;

    if (this->iterator_ == this->head_) {

        this->head_ = this->head_->next;
        this->head_->prev = nullptr;

        delete delete_node;
    } else if (this->iterator_ == this->tail_) {

        this->tail_ = this->tail_->prev;
        this->tail_->next = nullptr;

        delete delete_node;
    } else {

        this->iterator_->next->prev = delete_node->prev;
        this->iterator_->prev->next = delete_node->next;

        this->iterator_ = nullptr;

        this->ResetIterator();

        delete delete_node;
    }

    --this->length_;
}

void Deck::DisplayDeck() const { // Untested

    this->ResetIterator();

    cout << "PRINTING DECK" << endl;

    while(this->iterator_ != nullptr) {

        cout << setw(4) << *this->iterator_->card;

        if (this->iterator_->next != nullptr && (this->iterator_->card->suit() != this->iterator_->next->card->suit())) {

            cout << endl;
        }

        this->iterator_ = this->iterator_->next;
    }

    cout << endl;
}

// Private Member Functions
void Deck::SetDeck(int suit, int value, int tag) {

    Node* insert_node = new Node();             // Deleted in Destructor OR RemoveCard()
    insert_node->card = new Card(suit, value);  // Deleted in Destructor OR RemoveCard()

    insert_node->tag = tag;

    if (this->head_ == nullptr) { // 0 Nodes / Empty List

        this->head_ = this->tail_ = insert_node;

        ++this->length_;
    } else {    // 1 to Many Nodes

        tail_->next = insert_node;
        insert_node->prev = this->tail_;

        this->tail_ = insert_node;

        ++this->length_;
    }
}

int Deck::CreateRandomTag() const {

    random_device rd;
    mt19937 mt(rd());                                   
    uniform_int_distribution<int> dist(1, 52);

    return dist(mt);
}

bool Deck::CheckUsedCardTags(const int tag) const { // Untested

    if (this->tag_list_.size() == 0) {

        return false;
    }

    for (int i = 0; i < this->tag_list_.size(); i++) {

        if (this->tag_list_[i] == tag) {

            return true;
        }
    }

    return false;
}
void Deck::ResetIterator() const {

    this->iterator_ = this->head_; // Consider: Empty List - Exception??
}

bool Deck::TestConnections() const { // Untested

    this->ResetIterator();

    if (this->iterator_ == nullptr) {

        cerr << "Deck::TestConnections() | Cannot call function w/ an empty list" << endl; // Exception
    }

    while (this->iterator_->next != nullptr) {

        if (this->iterator_->next->prev != this->iterator_) {

            return false;
        }

        this->iterator_ = this->iterator_->next;
    }

    return true;
}