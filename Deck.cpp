#include <Deck.h>

// TODO: Implement exceptions where appropreiate

// Constructor - Destructor
Deck::Deck() : length_(0) {

    this->head_ = this->tail_ = this->iterator_ = nullptr;

    this->InitializeDeck(0, 0, 0);
}

Deck::~Deck() { // UNTESTED

    Node* delete_node = this->head_;

    this->ResetIterator();

    while (delete_node != nullptr) {

        this->iterator_ = this->iterator_->next;

        delete delete_node->card;
        delete delete_node;

        --this->length_;

        delete_node = this->iterator_;
    }
}

// Actions
bool Deck::InitializeDeck(int suit, int value, int tag) { // UNTESTED

    if (tag == kDeckSize + 1) {

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

bool Deck::RemoveCard(const int tag) { // UNTESTED

    if (tag <= 0 || tag > 52) {

        cerr << "Deck::RemoveCard() | Invalid tag value, [1,51]" << endl; // Exception??
        return false;
    }

    if (this->head_ == nullptr) { // 0 Nodes

        cerr << "Deck::RemoveCard() | Attempting To Remove From an Empty List" << endl; // ^^ ??
        return false;
    }

    if (this->head_ == this->tail_){ // 1 Node

        Node* delete_node = this->head_;

        delete delete_node;

        this->head_ = this->tail_ = nullptr;

        --this->length_;

        return true;
    } 

    if (tag == this->head_->tag) { // Removal At Head

        Node* delete_node = this->head_;

        this->head_ = this->head_->next;

        delete delete_node;

        this->head_->prev = nullptr;

        --this->length_;

        return true;
    }

    if (tag == this->tail_->tag) { // Removal at Tail

        Node* delete_node = this->tail_;

        this->tail_ = this->tail_->next;

        delete delete_node;

        this->tail_->next = nullptr;

        --this->length_;

        return true;
    }

    ResetIterator();

    this->iterator_ = this->iterator_->next;

    while (this->iterator_ != this->tail_) {

        if (tag == this->iterator_->tag) {  // Removal somewhere in the middle

            Node* delete_node = this->iterator_;

            this->iterator_->next->prev = delete_node->prev;
            this->iterator_->prev->next = delete_node->next;
            
            this->iterator_ = this->iterator_->next;
            
            delete delete_node;

            --this->length_;

            return true;
        } else {

            this->iterator_ = this->iterator_->next;
        }
    }

    return false; // Node not found in the list
}

void Deck::RetrieveCard(int tag, Card* &ret_card) { // Untested - O nodes, 1 nodes ...

    // So a random card can be retrieved from the list - simulating a shoe of cards
    int random_tag = CreateRandomTag();

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
    if (this->iterator_ == this->head_) { // Consider: 1 Node long list

        while (this->iterator_->tag != tag) {

            this->iterator_ = this->iterator_->next;
        }
    } else {

        while (this->iterator_->tag != tag) {

            this->iterator_ = this->iterator_->prev;
        }
    }

    // The correct card has been located based on random_tag
    *ret_card = *(this->iterator_->card);

    // Add random_tag to the vector of used tags
    this->tag_list_.push_back(random_tag);

    // Remove card w/ random_tag from the list - same code as in RemoveCard();
    Node* delete_node = this->iterator_;

    this->iterator_->next->prev = delete_node->prev;
    this->iterator_->prev->next = delete_node->next;
            
    this->iterator_ = this->iterator_->next;
            
    delete delete_node;

    --this->length_;
}

void Deck::DisplayDeck() const { // Untested

    this->ResetIterator();

    cout << "PRINTING DECK" << endl;

    while (this->iterator_ != nullptr) {

        cout << *this->iterator_->card << " ";

        if (this->iterator_->next != nullptr && (this->iterator_->card->suit() != this->iterator_->card->suit())) {

            cout << endl;
        }
    }
}

// Private Member Functions
void Deck::SetDeck(int suit, int value, int tag) { // Untested

    Node* insert_node = new Node();             // Deleted in Destructor OR RemoveCard()
    insert_node->card = new Card(suit, value);  // Deleted in Destructor OR RemoveCard()

    insert_node->tag = tag;

    if (this->head_ = nullptr) { // 0 Nodes / Empty List

        this->head_ = this->tail_ = insert_node;

        ++this->length_;
    } else {    // 1 to Many Nodes

        tail_->next = insert_node;
        insert_node->prev = this->tail_;

        this->tail_ = insert_node;

        ++this->length_;
    }
}

int Deck::CreateRandomTag() const { // Untested

    random_device rd;
    mt19937 mt(rd());                                   
    uniform_int_distribution<int> dist(1, 52);

    return dist(mt);
}

bool Deck::CheckUsedCardTags(const int tag) const { // Untested

    for (int i = 0; i < this->tag_list_.size() - 1; i++) {

        if (this->tag_list_[i] == tag) {

            return true;
        }
    }
}
void Deck::ResetIterator() const {

    this->iterator_ = this->head_; // Consider: Empty List - Exception??
}

bool Deck::TestConnections() const { // Untested

    while (this->iterator_ != nullptr) {

        if (this->iterator_->next->prev != this->iterator_) {

            return false;
        }

        this->iterator_ = this->iterator_->next;
    }

    return true;
}