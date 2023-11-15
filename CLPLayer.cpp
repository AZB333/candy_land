#include <iostream>
#include "CLPlayer.h"

Player::Player(){
    _stamina = 0;
    _gold = 0;
    _effect = "";
    for(int i = 0; i < 4; i++){
        _inventory[i].name = "Empty";
    }
    _candy_amount = 0;
}
Player::Player(int stamina, double gold, string effect, Candy inventory[], const int candy_amount){
    _stamina = stamina;
    _gold = gold;
    _effect = effect;
    for(int i = 0; i < candy_amount; i++){
        _inventory[i] = inventory[i];
        if(inventory[i].name == ""){
            _inventory[i].name = "Empty";
        }
    }
    for(int i = candy_amount; i < 4; i++){
        _inventory[i].name = "Empty";
    }
    int actual_candy = 0;
    for(int i = 0; i < 4; i++){
        if(_inventory[i].name != "Empty"){
            actual_candy++;
        }
    }
    if(actual_candy == 0){
        _candy_amount = 0;
    }
    else{
    _candy_amount = candy_amount;
    }
}

int Player::getCandyAmount() const{
    return _candy_amount;
}

int Player::getStamina() const{
    return _stamina;
}
double Player::getGold() const{
    return _gold;
}
string Player::getEffect() const{
    return _effect;
}

void Player::setCandyAmount(int candy_amount){
    _candy_amount = candy_amount;
}

void Player::setStamina(int stamina){
    _stamina = stamina;
}

void Player::setGold(double gold){
    _gold = gold;
}

void Player::setEffect(string effect){
    _effect = effect;
}

void Player::printInventory(){
    for(int i = getCandyAmount(); i < 4; i++){
        _inventory[i].name = "Empty";
    }

    for(int i = 0; i < _MAX_CANDY_AMOUNT; i++){
        if(i != 3){
        cout << "|[" << _inventory[i].name << "]";
        }
        else{
            cout << "|[" << _inventory[i].name << "]|";
        }
        if(i == 1){
            cout <<  "|" << endl;
        }
        if(i == 3){
            cout << endl;
        }
    }
}
Candy Player::findCandy(string candy_name){
    Candy desiredCandy = {"","",0,""};
    string lowerCandyName = candy_name;//lower parameter
    string lowerInventoryName;//lower inventory
    for(int i = 0; i < lowerCandyName.length(); i++){
        lowerCandyName[i] = tolower(candy_name[i]); //make lowerCandy lower
    }
    for(int i = 0; i < 4; i++){
        lowerInventoryName = _inventory[i].name;
        for(int j = 0; j < _inventory[i].name.length(); j++){//stops right here
            lowerInventoryName[j] = tolower(_inventory[i].name[j]);//make inventory lower
        }
        if(lowerInventoryName == lowerCandyName){//since it makes everything lowercase in the test file, gotta make the _inventory[i].name lowercase
            desiredCandy = _inventory[i];
            return desiredCandy;
        }
    }
    return desiredCandy;
}
bool Player::addCandy(Candy c){
    if(getCandyAmount() == 4){
        return false;
    }
    else{
        _inventory[_candy_amount] = c;
    }
    setCandyAmount(getCandyAmount() + 1);
    return true;
}

bool Player::removeCandy(string name){
    string lowerName = name;
    string lowerInventory;
    for(int i = 0; i < name.length(); i++){ //makes everything lowercase
        lowerName[i] = tolower(name[i]);
    }
    bool foundFlag = false;
    int removeIndex = -1;
    for(int i = 0; i < 4; i++){
        lowerInventory = _inventory[i].name;
        for(int j = 0; j < lowerInventory.length(); j++){
            lowerInventory[j] = tolower(_inventory[i].name[j]);
        }
        if(lowerInventory == lowerName){
            removeIndex = i;
            foundFlag = true;
        } 
    }
    if(foundFlag == true){
        for(int j = removeIndex; j < 3;j++){
            _inventory[j] = _inventory[j + 1];
        }   

        _inventory[3].name = "Empty";
        _inventory[3].description = "";
        _inventory[3].price = 0;
        _inventory[3].candy_type = ""; 
        setCandyAmount(getCandyAmount() - 1);
        return true;
    }
    
    return false;
}

