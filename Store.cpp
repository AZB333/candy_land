#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Store.h"

Store::Store(){
    for(int i = 0; i < _MAX_STORE_CANDY; i++){
        _store_inventory[i] = {"Empty", "","",0,"",0}; 
    }
}

void Store::displayCandies(){
    cout << "Welcome to the Candy Store! Please choose one of these delicious candies\n";
    for(int i = 0; i < 3; i++){
        cout << "Name: "<< _store_inventory[i].name << endl;
        cout << "Description: " << _store_inventory[i].description << endl;
        cout << "Effect: " << _store_inventory[i].effect << endl;
        cout << "Effect Value: " << _store_inventory[i].effect_value << endl;
        cout << "Candy Type: " << _store_inventory[i].candy_type << endl; 
        cout << "Price: " << _store_inventory[i].price << endl;
        cout << "--------------------------------\n";
        
    }
    cout << "The selected candy is \n";

}

void Store::populateStore(string fileName, vector<Candy> allCandies){
    srand((unsigned) time(NULL));
        int candy1Index = rand() % allCandies.size();
        int candy2Index;
        int candy3Index;
        if(candy1Index > 2 && candy1Index < 10){
            int candy2Index = candy1Index - 2;
            int candy3Index = candy1Index + 2;
        }
        else if(candy1Index < 2){
            candy2Index = candy1Index + 2;
            candy3Index = candy1Index + 4;
        }
        else if(candy1Index > 10){
            candy2Index = candy1Index - 2;
            candy2Index = candy1Index - 4;
        }
        _store_inventory[0] = allCandies[candy1Index];
        _store_inventory[1] = allCandies[candy2Index];
        _store_inventory[2] = allCandies[candy3Index];
        
}

Candy Store::findCandy(string candyName){
    Candy desiredCandy = {"","","",0,"",0};
    string lowerCandyName = candyName;//lower parameter
    string lowerInventoryName;//lower inventory
    for(int i = 0; i < lowerCandyName.length(); i++){
        lowerCandyName[i] = tolower(candyName[i]); //make lowerCandy lower
    }
    for(int i = 0; i < 3; i++){
        lowerInventoryName = _store_inventory[i].name;
        for(int j = 0; j < _store_inventory[i].name.length(); j++){
            lowerInventoryName[j] = tolower(_store_inventory[i].name[j]);//make inventory lower
        }
        if(lowerInventoryName == lowerCandyName){//since it makes everything lowercase in the test file, gotta make the _inventory[i].name lowercase
            desiredCandy = _store_inventory[i];
            return desiredCandy;
        }
    }
    return desiredCandy;
}
