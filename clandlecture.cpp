#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

//pass by value
void passByValue(int i){
    i++;
}
void passByReference(int &i){
    i++;
}
void passAnArray(int a[]){
    a[0] = 5;
}
void passAVector(vector<int> b){
    b[0] = 5;
}
int main(){
    int i = 0; 
    passByValue(i); //i not updated in main
    //i is 0 here
    passByReference(i); // i is updated, memory of address is updated, not the value
    //i is 1 here
    int a[2] = {0,0};
    passAnArray(a);
    //a[0] is 5
    vector<int> b(2);
    passAVector(b);
    //b[0] = 0 still 

    //generate random members
    //how often a calamity occurs
    //generate a random card draw and a deck of cards

    //need to seed a random number generator
    srand((unsigned) time(NULL)); //passes the current time in seconds since 01/01/1900
    // cout << rand() << endl; //no upper bound
    //offset + random & range
    int x = rand() % 100 + 1; //1-10
    int random = 5 + rand() % 10; //5-15
    
    //if i generate a number randomly between 1-100, the number should be 40 or less 40% of the time
    int count = 0;
    for(int i = 0; i < 100; i++){
        random = rand() % 100 + 1;
        if(random <= 40){
            count++;
        }
    }
    // cout << count;

    //if you want a distribution of cards, single and double color, how do you set it up
    //so that single colors are more likely to be drawn than double colors

    //if(random number > 0 < 51) then single else is double
    /*
    create an array with 9 positions
    each single color gets two positions, and each double color gets 1
    generate a random number between 0-9 that is an index in the array

    */
    string cards[9] = {"m","m","g","g","b","b","dm","dg","db"};
    //draw 100 cards and keep track of the counts
    int cardCounts[6] = {0,0,0,0,0,0};
    for(int i = 0; i < 100; i++){
        random = rand() % 9;
        if(random == 0 || random == 1){
            cardCounts[0]++;
        } else if(random == 2 || random == 3){
            cardCounts[1]++;
        } else if(random == 4 || random == 5){
            cardCounts[2]++;
        } else if(random == 6){
            cardCounts[3]++;
        } else if(random == 7){
            cardCounts[4]++;
        } else{
            cardCounts[5]++;
        }
    }
    for(int i = 0; i < 6; i++){
        cout << cardCounts[i] << " ";
    }
}