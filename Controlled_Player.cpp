#include "Controlled_Player.h"

#include <iomanip>

player::player_card_node::player_card_node(const int suit, const int value){

    next = prev = nullptr;
    card_suit = suit;
    card_value = value;

    switch(suit){
        case 1: 
        card_suit_character = "\u2665";   // heart
        break;
        case 2:
        card_suit_character = "\u2666";   // diamond
        break;
        case 3:
        card_suit_character = "\u2663";   // club
        break;
        case 4:
        card_suit_character = "\u2660";   // spade
        break;
        default:
        cout << "ERROR IN player_card_node Constructor: INVALID SUIT VALUE!" << endl;
        exit(1);
    }
}

player::~player(){

    iterator = tail;

    player_card_node* deleteNode = new player_card_node();

    while (this->has_more()){
        deleteNode = iterator;
        iterator = iterator->prev;
        delete deleteNode;
    }
}
player::player(const player& copyplayer){

    this->handTotal[0] = copyplayer.handTotal[0];
    this->handTotal[1] = copyplayer.handTotal[1];

    this->head = this->tail = nullptr;
    
    this->reset_iterator();
    copyplayer.reset_iterator();

    while (copyplayer.has_more()){
        this->add_card_to_hand(copyplayer.iterator->card_suit, copyplayer.iterator->card_value);
        copyplayer.iterator = copyplayer.iterator->next;
    }

}
player& player::operator = (const player& leftplayer){

    this->handTotal[0] = leftplayer.handTotal[0];
    this->handTotal[1] = leftplayer.handTotal[1];

    this->head = this->tail = nullptr;
    
    this->reset_iterator();
    leftplayer.reset_iterator();

    while (leftplayer.has_more()){
        this->add_card_to_hand(leftplayer.iterator->card_suit, leftplayer.iterator->card_value);
        leftplayer.iterator = leftplayer.iterator->next;
    }

    return *this;

}
void player::add_card_to_hand(const int card_suit, const int card_value){ 

    player_card_node *insert_node = new player_card_node(card_suit, card_value);

    if (head == nullptr){   // 0 nodes
        
        head = tail = insert_node; 
    } else {                // 1 & many nodes
        insert_node->prev = tail;
        tail->next = insert_node;
        tail = insert_node;
        ++handSize;
    }

    reset_iterator();
    return;
}
bool player::remove_card_from_hand(){

    player_card_node *deleteNode = new player_card_node();

    if (head == nullptr){   // 0 nodes
        cout << "ERROR in remove_card_from_hand(): REMOVING FROM EMPTY LIST!" << endl;
        exit(1);
    } else if (head == tail){   // 1 node

        deleteNode = tail;
        head = tail = nullptr;
        --handSize;
        delete deleteNode;
        return true;
    }
    //many nodes
    deleteNode = tail;
    tail = tail->prev;
    --handSize;
    delete deleteNode;
    return true;
}
bool player::display_player_hand() { 

    this->update_hand_total();

    if (this->handTotal[0] == 0){
        cout << "ERROR in display_player_hand(): HAND IS EMPTY!" << endl;
        exit(1);
    } else {

        cout << "Current Hand Total:  " << this->handTotal[0];

        if (this->handTotal[1] <= 21 && this->handTotal[1] != 0){
            
            cout << " OR " << this->handTotal[1];
        }
    }

    cout << endl;

    unsigned int counter = 0;
    
    this->reset_iterator();

    while (this->has_more()){
        
        cout << setw(2);

        if (counter == 5) {
            
            cout << endl;
            counter = 0;
        }

        switch(this->iterator->card_value){
            case 1:
            cout << 'A';
            break;
            case 11:
            cout << 'J';
            break;
            case 12:
            cout << 'Q';
            break;
            case 13: 
            cout << 'K';
            break;
            default:
            cout << this->iterator->card_value;
        }

        cout << this->iterator->card_suit_character << "  ";

        this->iterator = this->iterator->next;
        ++counter;
    }
    cout << endl;

    return true;
}
void player::update_hand_total(){ // using handTotal and reseting it every call seems lame

    int aceCounter = 0;

    this->handTotal[0] = 0;
    this->handTotal[1] = 0;

    this->reset_iterator();

    if (head == nullptr) { //TODO feels improper, throw error?
        
        cout << "ERROR IN update_hand_total(): EMPTY HAND, CAN'T EVALUATE!";
        exit(1);
    }
    while(this->has_more()){
        if (this->iterator->card_value >= 10 && this->iterator->card_value < 14){
            
            this->handTotal[0] += 10;
        } 
        
        else if (iterator->card_value == 1){
            
            ++aceCounter;
        } 
        
        else{
        
            this->handTotal[0] += this->iterator->card_value;
        } 
        
        this->iterator = this->iterator->next;
    }

    switch(aceCounter){
        case 0:
        break;
        case 1:

        if ((this->handTotal[0] + 11) > 22 ) {   // if adding the 11 to the hand busts it, treat the ace as a 1
        
            this->handTotal[0] += aceCounter;
        } else {                                    // else, treat it as a 1 and 11 
            
            this->handTotal[0] += aceCounter;
            this->handTotal[1] = this->handTotal[0] + 10;
        }

        break;
        case 2:
        case 3:
        case 4:
        
        if ((this->handTotal[0] + 11) > 22 ) {
            
            this->handTotal[0] += aceCounter;
        } else {
            
            this->handTotal[0] += aceCounter;
            this->handTotal[1] = this->handTotal[0] + (11 - (--aceCounter));
        }

        break;
        default:
        cout << "TOO MANY ACES IN countHandTotal()!" << endl;
        exit(1);
    }
    
    return;
} 
void player::game_options_error_checking() const{

    reset_iterator();

    if (head == nullptr){
        cout << "ERROR in player::game_options_error_checking(): empty list" << endl;
        exit(1);
    }
    else if (iterator->next == nullptr){
        cout << "ERROR in player::game_options_error_checking(): only 1 node" << endl;
        exit(1);
    } else if (handSize >= 3){
        cout << "ERROR in player::game_options_error_checking(): invaild logic check, more than 2 cards" << endl;
        exit(1);
    }

    if (iterator->card_value == iterator->next->card_value){

        cout << "TEST PASSED" << endl;
        return;
    }
}
int player::check_game_options() const{

    // v2: have a surrender check

    if (natural_check()){

        return 0;
    }
    else if (split_check()){
        
        return 1; 
    } else if (double_down_check()){

        return 2;
    } else if (hit_or_stand_check()){ // hit

        return 3;
    } else if (!hit_or_stand_check()){ // stand

        return 4;
    } else {

        cout << "ERROR in player::check_game_options(): out of bounds check!" << endl;
        exit(1);
    }

    return 0;
}
bool player::bust_checker() const{

    // will have to be called after update_hand_total is called to eval the correct data at the proper time
    
    // return true if busted - false if not

    // dont have to check handTotal[1], as that index will only have data if it's < = 21
   
    if(this->handTotal[0] >= 22){

        return false;
    }

    return true;
}
bool player::split_check() const{

    game_options_error_checking();

    reset_iterator();

    if (iterator->card_value == iterator->next->card_value){

        cout << "TEST PASSED" << endl;
        return true;
    }

    return false;
}
bool player::double_down_check() const {
    
    game_options_error_checking();

    char responce;

    if (handTotal[0] >= 8 && handTotal[0] <= 11) {
        cout << "Dealer: Care to Double Down? (y/n, captilization matters)" << endl;
        cin >> responce;
    } else {
    
        return false;
    }

    while (responce != 'y' && responce != 'n'){
        cout << "Dealer: INVALID input, try again." << endl;
        cin >> responce;
    }

    if (responce == 'y'){

        cout << "Dealer:: Double Down it is." << endl;
        return true;
    }

    cout << "Dealer: No Doubling Down. Let's carry on." << endl;
    return false;
}
bool player::hit_or_stand_check() const{

    char responce;

    cout << "Dealer: Would you like to HIT or STAND? (y/n, capitalization matters)" << endl;
    cin >> responce;
    
    while (responce != 'y' && responce != 'n'){
        cout << "Dealer: INVALID input, try again." << endl;
        cin >> responce;
    }

    if (responce == 'y') {

        return true;
    } 

    return false;
}
bool player::natural_check() const{

    game_options_error_checking();
    
    if (handTotal[1] == 21){

        return true;
    }

    return false;
}

void player::reset_iterator() const{

    iterator = head;
}
bool player::has_more() const{

    if (iterator != nullptr){
        return true;
    }

    return false;
}
player::player_card_node& player::next() const{

    player_card_node *tempNode = new player_card_node();
    
    if (iterator == nullptr){
        cout << "ERROR IN next(): CANNOT RETRIEVE VALUE FROM AN EMPTY LIST\n";
        exit(1);
    } else {
        tempNode = iterator;
        iterator = iterator->next;
    }
    
    return *tempNode;
}
void player::test_connections() const{

    reset_iterator();

    if (head == nullptr){
        cout << "Empty List!" << endl;

    } else if (head->prev != nullptr){
        cout << "ERROR IN test_connections(): head->prev != nullptr!" << endl;

    } else if (tail->next != nullptr){
        cout << "ERROR IN test_connections(): tail-> " << endl;
   } 

    while (iterator != tail){
        if (iterator != iterator->next->prev){
            cout << "Bad Connection at " << iterator->card_value << iterator->card_suit_character << endl;
            return;
        }
        iterator = iterator->next;
    }

    cout << "TESTING CONNECTIONS PASSED\n" << endl;
} 

 