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
    for(int i = 0; i < 3; i++){
        
        cout << "Name: "<< _store_inventory[i].name << endl;
        cout << "Description: " << _store_inventory[i].description << endl;
        cout << "Effect: " << _store_inventory[i].effect << endl;
        cout << "Effect Value: " << _store_inventory[i].effect_value << endl;
        cout << "Candy Type: " << _store_inventory[i].candy_type << endl; 
        cout << "Price: " << _store_inventory[i].price << endl;
        cout << "--------------------------------\n";
        
    }
}

vector<Candy> Store::readCandies(string file_name, vector<Candy> store_candies){ //add extra candy members
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


void Store::populateStore(string fileName){
    vector<Candy> allCandies;
    srand((unsigned) time(NULL));
    allCandies = readCandies(fileName, allCandies);
    for(int j = 0; j < 4; j++){
        _store_inventory[j] = allCandies[rand() % allCandies.size()];
    }

}