#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Store.h"

Store::Store(){//default constructor
    for(int i = 0; i < _MAX_STORE_CANDY; i++){
        _store_inventory[i] = {"Empty", "","",0,"",0}; 
    }
}

void Store::displayCandies(){//shows the stores candies
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

void Store::populateStore(string fileName, vector<Candy> allCandies){//gives the store candies
    srand((unsigned) time(NULL));//seeds random
    int candy1Index = rand() % allCandies.size();//random index in the candy vector
    int candy2Index;
    int candy3Index;
    if(candy1Index > 2 && candy1Index < 10){//if candy index is 3-9
        int candy2Index = candy1Index - 2;//other indeces are 2 below and above
        int candy3Index = candy1Index + 2;
    }
    else if(candy1Index < 2){//if index is 0-1
        candy2Index = candy1Index + 2;//other indeces are 2 and 4 above
        candy3Index = candy1Index + 4;
    }
    else if(candy1Index > 10){//if index is 10-11
        candy2Index = candy1Index - 2;//other indeces are 2 and 4 below
        candy2Index = candy1Index - 4;
    }
    _store_inventory[0] = allCandies[candy1Index];//populates store inventory with candies
    _store_inventory[1] = allCandies[candy2Index];
    _store_inventory[2] = allCandies[candy3Index];
        
}

Candy Store::findCandy(string candyName){//finds a candy in the store
    Candy desiredCandy = {"","","",0,"",0};//default candy is empty
    string lowerCandyName = candyName;//lower parameter
    string lowerInventoryName;//lower inventory
    for(int i = 0; i < lowerCandyName.length(); i++){
        lowerCandyName[i] = tolower(candyName[i]); //make lowerCandy lowercase
    }
    for(int i = 0; i < 3; i++){//loops through store's inventory
        lowerInventoryName = _store_inventory[i].name;
        for(int j = 0; j < _store_inventory[i].name.length(); j++){
            lowerInventoryName[j] = tolower(_store_inventory[i].name[j]);//make inventory lowercase
        }
        if(lowerInventoryName == lowerCandyName){//since it makes everything lowercase in the test file, make the _inventory[i].name lowercase
            desiredCandy = _store_inventory[i];
            return desiredCandy;
        }
    }
    return desiredCandy;//if it makes it to here, it returns an empty candy
}
