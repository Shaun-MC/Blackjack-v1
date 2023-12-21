#include "Queue.h"

Queue::Queue() {

    this->vec_.resize(2);

    this->front_index_ = 0;
    this->back_index_ = 1;

    this->length_ = 0;
}

Queue::Queue(const Queue& rval) {

    this->vec_.resize(2);

    this->front_index_ = 0;
    this->back_index_ = 1;
    
    this->length_ = 0;

    *this = rval;
}

// Getters
const Card& Queue::front() const { // TODO: Use exceptions instead of boolean - make const

    if (IsEmpty()) {

        cerr << "Queue::front() | Queue is Empty" << endl;

        return this->vec_[this->front_index_]; // Exception
    } else {

        return this->vec_[this->front_index_];
    }
}

const Card& Queue::back() const { // TODO: use exceptions instead of boolean - make const


    if (IsEmpty()) {

        cerr << "Queue::back() | Queue is Empty" << endl;

        return this->vec_[this->front_index_]; // Exception
    } else {
        
        return (this->length() == 1) ? this->vec_[this->front_index_] : this->vec_[this->back_index_];
    }
}
int Queue::front_index() const { // TODO: use exceptions instead of garbage

    if (IsEmpty()) {

        cerr << "Queue::front_index() | Queue is Empty" << endl;

        return -1; // Exception
    } else {

        return this->front_index_;
    }
}

int Queue::back_index() const { // TODO: use exceptions instead of garbage

    if (IsEmpty()) {

        cerr << "Queue::back_index() | Queue is Empty" << endl;
        
        return -1; // EXCEPTION
    } else {

        return this->back_index_;
    }
}

int Queue::length() const {

    return this->length_;
}

// Actions

// Worst Case: O(1)
// Best Case O(1)
// Average Case O(1)
bool Queue::Pop() { // Untested

    if (IsEmpty()) {

        return false; // EXCEPTIONS
    } else {

        this->front_index_ = (this->front_index_ + 1) % this->vec_.size();
        
        --this->length_;

        return true;
    }
}

// Worst Case: O(n) - having to double the queue size
// Best Case: O(1)
// Average Case: O(1)
void Queue::Push(const Card& element) {

    if (this->IsEmpty()) {

        this->vec_[0] = element;

    } else if (this->length() == 1) {

        this->vec_[1] = element;

    } else {

        if (this->length() == this->vec_.size()) {

            this->DoubleQueueSize();
        }

        this->back_index_ = (this->back_index_ + 1) % this->vec_.size();

        this->vec_[back_index_] = element;
    }

    ++this->length_;
}

bool Queue::IsEmpty() const {

    return (this->length_ == 0) ? true : false;
}

void Queue::DisplayQueue() const {

    for (int i = 0; i < this->length(); i++) {

        cout << this->vec_[(this->front_index() + i) % this->vec_.size()] << " ";

        if (i != 0 && i % 5 == 0) {

            cout << endl;
        }
    }
}
// Operator Overloads 

// Worst Case: O(??)
// Best Case: O(1)
// Average Case: O(??)
Queue& Queue::operator = (const Queue& rval) {

    if (this == &rval) {

        return *this;
    } 

    while(this->Pop());

    this->front_index_ = 0;
    this->back_index_ = 1;

    this->vec_.resize(rval.vec_.size());

    if (!rval.IsEmpty()) {

        int rval_iterator = rval.front_index_;

        // Copy over elements until the queue wraps around (if it does)
        while (rval_iterator < rval.vec_.size() && rval_iterator <= rval.back_index_) {

            this->Push(rval.vec_.at(rval_iterator));

            ++rval_iterator;
        }

        // Start from the begining of rval - copy over until back_index_;
        if (rval_iterator <= rval.back_index_) { 

            rval_iterator = 0;

            while (rval_iterator <= rval.back_index_) {

                this->Push(rval.vec_[rval_iterator]);

                ++rval_iterator;
                ++this->length_;
            }
        } 
    }

    this->front_index_ = 0;
    this->back_index_ = (this->length() - 1 < 0)? 0 : this->length() - 1;

    return *this;
}

// Worst Case: O(n)
// Best Case: O(1)
// Average Case:  O(n)
bool Queue::operator == (const Queue& rval) const {

    if (this == &rval || (this->length() == 0 && rval.length() == 0)) {

        return true;
    } else if (this->vec_.size() != rval.vec_.size() || this->length() != this->length()) {

        return false;
    }

    int lval_iterator = this->front_index_;
    int rval_iterator = rval.front_index_;

    for (int i = 0; i < this->length(); i++) {
        
        if (this->vec_[lval_iterator] != rval.vec_[rval_iterator]) { // Comparison

            return false;
        }

        // Move Iterators

        if (lval_iterator == this->back_index_) { // Wrap Around

            lval_iterator = 0;
        } else {    // Don't wrap around

            ++lval_iterator;
        }

        if (rval_iterator == rval.back_index_) { // ^^

            rval_iterator = 0;
        } else {    // ^^

            ++rval_iterator;
        }
    }

    return true;
}

bool Queue::operator != (const Queue& rval) const {

    return (*this == rval) ? false : true;
}

// Private Member Functions

// Worst Case: O(n + n) == O(n) - resize(...) + having to copy over elements 
// Best Case: O(n) - resize()
// Average Case: O(n)
void Queue::DoubleQueueSize() {

    int previous_size = this->vec_.size();

    vec_.resize(previous_size * 2);

    if (this->back_index_ < this->front_index_) {

        for (int i = 0; i <= this->back_index_; i++) {

            this->vec_[previous_size + i] = this->vec_[i];
        }

        this->back_index_ += previous_size;
    }
}
