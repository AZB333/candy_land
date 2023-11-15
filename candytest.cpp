#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Board.h"

using namespace std;

int main(){
    //generate random members
    //how often a calamity occurs
    //generate a random card draw and a deck of cards


    //need to seed a random number generator
    srand((unsigned) time(NULL)); //passes the current time in seconds since 01/01/1900
    cout << rand() << endl; //no upper bound
    for(int i = 0; i < 5; i++){
        int x = rand() % 100 + 1;
        cout << x << "  ";
    }
}