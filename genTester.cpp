#include <iostream>

using namespace std;

int main() {
    
    char responce;

    cout << "Dealer: Would you like to Double Down, Hit or Stand? (D for D.D, H for Hit, S for Stand, capitalization matters)" << endl;
    cin >> responce;

    while (responce != 'D' && responce != 'H' && responce != 'S'){

        cout << "Dealer: Invalid Input, please Try Again. (D for D.D, H for Hit, S for Stand, capitalization matters)" << endl;
        cin >> responce;
    }

}