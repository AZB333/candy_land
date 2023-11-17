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



/*just throwing this here in case its needed

vector<Candy> readCandy(string file_name, vector<Candy> candies){ //add extra candy members
    cout << fixed << setprecision(2);
    ifstream candyFile;
    string line;
    candyFile.open(file_name);
    if(candyFile.fail()){
        return candies;
    }
    else{
        string name = "";
        string description = "";
        string effect = "";
        string effectValue = "";
        int actualEffectValue = 0;
        string candyType = "";
        string price = "";
        int actualPrice = 0;
        while(getline(candyFile, line)){
            stringstream ss(line);
            int iterator = 0;
            Candy current_candy;
            if(line.size() != 0){
            while(getline(ss, line, '|')){
                if(iterator == 0){
                    iterator ++;
                    name = line;
                } else if(iterator == 1){
                    iterator++;
                    description = line;
                } else if(iterator == 2){
                    iterator++;
                    price = line;
                    actualPrice = stoi(price);
                } else if(iterator == 3){
                    iterator++;
                    candyType = line;
                }
               
            }
            current_candy.name = name;
            current_candy.description = description;
            current_candy.price = actualPrice;
            current_candy. candy_type = candyType;
            candies.push_back(current_candy);
            }
           
        }
    return candies;
}
}

*/