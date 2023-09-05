#ifndef CONTROLLED_PLAYER_H
#define CONTROLLED_PLAYER_H

//#include "Statistics_Manager.h"
//#include "Statistics_Manager.cpp"

#include <vector>

using namespace std;

    // 'variables wanted for the 'player' class;
    // a linked list hand for holding the card data - and the ability to create another one if the case of spliting
    // statsManager class for keeping track of bets and a variety of other data //TODO WIP
    // 
    // create virtual functions that deal with the similarties between a 'Dealer' & a 'player'//TODO
    //virtual initializeHand(); ...

class player{
    public:

    class player_card_node{
        public:

        player_card_node() : next(nullptr), prev(nullptr), card_suit(0), card_value(0), card_suit_character("") {};
            
        player_card_node(const int suit, const int value);

        unsigned int card_suit, card_value;
        string card_suit_character; 
        player_card_node *next, *prev;
    };

    player() : head(nullptr), tail(nullptr), iterator(head), handTotal(), handSize(0) {};
    
    ~player();

    player(const player& copy_player);

    player& operator = (const player& left_player); 

    void add_card_to_hand(const int card_suit, const int card_value);

    bool remove_card_from_hand();
    
    bool display_player_hand();

    void update_hand_total();

    int check_game_options() const;

    bool bust_checker() const;

    bool split_check() const;

    bool double_down_check() const; 

    bool hit_or_stand_check() const;

    bool natural_check() const;

    void game_options_error_checking() const;

    // bool surrenderCheck() const;

    // function for creating another hand for splits

    // function for ending the hand ???

    void reset_iterator() const;
    bool has_more() const;
    player_card_node& next() const;
    void test_connections() const;

    //stats_manager statsInstance;
    
    private:

    int handSize;
    int handTotal[2]; 
    player_card_node *head, *tail;
    mutable player_card_node *iterator;
};

#endif