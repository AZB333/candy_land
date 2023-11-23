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
    for(int i = 0; i < 4; i++){
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

/*vector<Candy> Store::readCandies(string file_name, vector<Candy> store_candies){ //add extra candy members
    ifstream candyFile;
    string line;
    candyFile.open(file_name);
    if(candyFile.fail()){
        return store_candies;
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
        getline(candyFile, line);
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
                    effect = line;
                } else if(iterator == 3){
                    iterator++;
                    effectValue = line;
                    actualEffectValue = stoi(effectValue);
                } else if(iterator == 4){
                    iterator++;
                    candyType = line;
                } else if(iterator == 5){
                    price = line;
                    actualPrice = stoi(price);
                }
            }
            current_candy.name = name;
            current_candy.description = description;
            current_candy.effect = effect;
            current_candy.effect_value = actualEffectValue;
            current_candy.candy_type = candyType;
            current_candy.price = actualPrice;
            store_candies.push_back(current_candy);
            }
        }
    return store_candies;
}
}
*/

void Store::populateStore(string fileName, vector<Candy> allCandies){//as far as i know this works
    srand((unsigned) time(NULL));
    int random;
    int cantUse[4];
    // allCandies = readCandies(fileName, allCandies);
    for(int i = 0; i < 4; i++){//should populate the store four times
        random = rand() % allCandies.size();
        cantUse[i] = random;
        for(int j = 0; j < 4; j++){//checks if that value has already been used
            if(i != j && cantUse[i] == cantUse[j]){
                if(random < 11){
                    _store_inventory[j] = allCandies[random + 2];
                }else if(random > 2){
                    _store_inventory[j] = allCandies[random - 2];
                }
            }
            else{
                _store_inventory[i] = allCandies[random];
            }
            
        }
    }


}

Candy Store::findCandy(string candyName){
    Candy desiredCandy = {"","","",0,"",0};
    string lowerCandyName = candyName;//lower parameter
    string lowerInventoryName;//lower inventory
    for(int i = 0; i < lowerCandyName.length(); i++){
        lowerCandyName[i] = tolower(candyName[i]); //make lowerCandy lower
    }
    for(int i = 0; i < 4; i++){
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
