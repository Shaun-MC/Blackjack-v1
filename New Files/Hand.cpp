#include "Hand.h"

// Constructors
Hand::Hand() { // Untested

    this->head_ = nullptr;
    this->tail_ = nullptr;

    this->hand_totals[0] = this->hand_totals[1] = 0;

    this->size_ = 0;

    this->ace_counter_ = 0;
}

Hand::Hand(const Hand& rval) { // Untested

    *this = rval;

    this->size_ = rval.size();
    this->ace_counter_ = rval.ace_counter_;
}

Hand::~Hand() { // Untested

    for (int i = 0; i < this->size(); i++) {

        this->RemoveCardFromHand();
    }

    this->head_ = nullptr;
    this->tail_ = nullptr;
}

// Getter
int Hand::size() const { // Untested

    return this->size_;
}

// Actions
void Hand::AddCardToHand(const int suit, const int value) { // Untested

    Node* insert_node = new Node();             // Deleted in Destructor
    insert_node->card = new Card(suit, value);  // Deleted in Destructor

    if (this->head_ == nullptr) {

        this->head_ = insert_node;
        this->tail_ = insert_node;

        ++this->size_;
    } else {

        Node* temp = this->head_;

        this->head_ = insert_node;

        insert_node->prev = temp;
        temp->next = insert_node;
    }

    if (value == 1) {

        ++this->ace_counter_;
    }

    UpdateHandTotal();
}

void Hand::RemoveCardFromHand() { // Untested

    Node* delete_node = this->head_;

    this->head_ = this->head_->prev;

    delete delete_node->card;
    delete delete_node;
}

void Hand::DisplayHand() const { // Untested

    Node* iterator = this->head_;

    cout << "Current Hand Total: " << hand_totals[0];

    if (hand_totals[1] != 0) {

        cout << " OR " << hand_totals[1];
    } 

    cout << endl;

    for (int i = 0; i < this->size(); i++) {

        cout << *(iterator->card) << " ";

        if (i == 5) {

            cout << endl;
        }
    }

    cout << endl;
}

// Operator Overloads
Hand& Hand::operator = (const Hand& rval) { // Untested

    if (this == &rval) { // Same extact list

        return *this;
    } 
    
    this->~Hand();

    if (rval.size() != 0) {

        Node* rval_iterator = rval.head_;
        Node* lval_iterator = new Node();
        lval_iterator->card = new Card(*rval_iterator->card);

        rval_iterator = rval_iterator->next;

        this->head_ = lval_iterator;

        while (rval_iterator != nullptr) {
            
            Node* temp = lval_iterator;

            lval_iterator->next = new Node();
            lval_iterator->next->card = new Card(*rval_iterator->card);

            lval_iterator = lval_iterator->next;
            lval_iterator->prev = temp;

            rval_iterator = rval_iterator;
        }

        this->tail_ = lval_iterator;
    }

    return *this;
}

// Private Member Functions

// O(n) vs O(1)
void Hand::UpdateHandTotal() { // Untested

    if (this->head_ == nullptr) {

        cerr << "Error: Hand::UpdateHandTotal() - this->head_ == nullptr" << '\n';
        return; // Exception???
    } 
    
    switch (this->head_->card->value()) {

        case 1:

        if (hand_totals[0] + 11 <= 21) {

            hand_totals[1] = hand_totals[0] + 11;
        }

        hand_totals[0] += 1;
        break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9: 

        hand_totals[0] += this->head_->card->value();
        hand_totals[1] += this->head_->card->value();
        break;

        case 10:
        case 11:
        case 12:
        case 13:

        hand_totals[0] += 10;
        hand_totals[1] += 10;
        break;

        default:
        cerr << "Error: Hand::UpdateHandTotal | Invalid 'this->head_->card_value()' " << endl;
        break;
    }
}

