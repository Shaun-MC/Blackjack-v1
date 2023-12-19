#include "Queue.h"

Queue::Queue() {

    this->vec_.resize(2);

    this->front_ = &this->vec_[0];
    this->back_ = &this->vec_[1];

    this->front_index_ = 0;
    this->back_index_ = 1;

    this->length_ = 0;
}

Queue::Queue(const Queue& rval) {

    this->vec_.resize(2);

    *this = rval;
}

Queue::~Queue() { // Untested

    while (this->Pop());
}

// Getters
Card& Queue::front() const { // Untested

    if (IsEmpty()) {

        Card temp;

        cerr << "Queue::front() | Queue is Empty" << endl;

        return temp; // USE Exceptions - Fix Warning
    } else {

        return *this->front_;
    }
}

Card& Queue::back() const { // Untested

    if (IsEmpty()) {

        Card temp;

        cerr << "Queue::back() | Queue is Empty" << endl;
        
        return temp; // USE EXCEPTIONS
    } else {

        return *this->back_;
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

        return false;
    } else {

        this->front_index_ = (this->front_index_ + 1) % this->vec_.size();
        
        this->front_ = &this->vec_[front_index_];
        
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

        this->back_ = &this->vec_[back_index_];
    }

    ++this->length_;
}

bool Queue::IsEmpty() const {

    return (this->length_ == 0) ? true : false;
}

// Operator Overloads 
Queue& Queue::operator = (const Queue& rval) {

    if (this == &rval) {

        return *this;
    } 

    this->~Queue();
    this->vec_.resize(rval.vec_.size);

    if (!rval.IsEmpty()) {

        int rval_iterator = rval.front_index_;

        // Copy over elements until the queue wraps around (if it does)
        while (rval_iterator < rval.vec_.size() || rval_iterator <= rval.back_index_) {

            this->Push(rval.vec_.at(rval_iterator));

            ++rval_iterator;
            ++this->length_;
        }

        // Start from the begining of rval - copy over until back_index_;
        if (rval_iterator != rval.back_index_) { 

            rval_iterator = 0;

            while (rval_iterator != rval.back_index_) {

                this->Push(rval.vec_[rval_iterator]);

                ++rval_iterator;
                ++this->length_;
            }
        } 
    }

    this->front_ = &this->vec_[0];
    this->back_ = &this->vec_[this->length()];

    this->front_index_ = 0;
    this->back_index_ = this->length();

    return *this;
}

bool Queue::operator == (const Queue& rval) const {

    if (this == &rval) {

        return true;
    } else if (this->vec_.size() != rval.vec_.size() || this->length() != this->length()) {

        return false;
    }

    int iterator = this->front_index_;

    while (iterator < this->vec_.size() || iterator != this->back_index_) {

        if (this->vec_[iterator] != rval.vec_[iterator]) {

            return false;
        } else {

            ++iterator;
        }
    }

    if (iterator == this->vec_.size()) {

        iterator = 0;

        while (iterator != this->back_index_) {

            if (this->vec_[iterator] != rval.vec_[iterator]) {

                return false;
            } else {

                ++iterator;
            }
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
