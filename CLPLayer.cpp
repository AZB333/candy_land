#include <iostream>
#include <string>
#include "CLPlayer.h"
using namespace std;

Player::Player(){
    _stamina = 0;
    _gold = 0;
    _effect = "";
    for(int i = 0; i < 9; i++){
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
    for(int i = candy_amount; i < 9; i++){
        _inventory[i].name = "Empty";
    }
    int actual_candy = 0;
    for(int i = 0; i < 9; i++){
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
    for(int i = getCandyAmount(); i < 9; i++){
        _inventory[i].name = "Empty";
    }

    for(int i = 0; i < _MAX_CANDY_AMOUNT; i++){
        cout << "[" << _inventory[i].name << "]  ";
        if(i == 2 || i == 5){
            cout << endl;
        }
    }
}
Candy Player::findCandy(string candy_name){
    Candy desiredCandy = {"","","",0,"",0};
    string lowerCandyName = candy_name;//lower parameter
    string lowerInventoryName;//lower inventory
    for(int i = 0; i < lowerCandyName.length(); i++){
        lowerCandyName[i] = tolower(candy_name[i]); //make lowerCandy lower
    }
    for(int i = 0; i < 9; i++){
        lowerInventoryName = _inventory[i].name;
        for(int j = 0; j < _inventory[i].name.length(); j++){
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
    bool replaceCandy;
    char replaceChoice;
    int indexToRemove;
    if(getCandyAmount() == 9){//need to change if inventory is full to swapping a desired index, might need to do this in main
        cout << "Your inventory is full! Would you like to replace an existing candy with a new one?(y/n)\n";
        cin >> replaceChoice;
        while((replaceChoice != 'y' && replaceChoice != 'Y') && (replaceChoice != 'n' && replaceChoice != 'N')){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid option, try again\n";
            cin >> replaceChoice;
        }
        if(replaceChoice == 'y' || replaceChoice == 'Y'){
            cout << "Please choose an index to replace a candy at (1-9)\n";
            cin >> indexToRemove;
            while(indexToRemove > 9 && indexToRemove < 1){
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Invalid input, enter a number between 1 and 9\n";
                cin >> indexToRemove;
            }
            _inventory[indexToRemove - 1] = c;
            return true;
        }
        else{
            return false;
        }
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
    for(int i = 0; i < 9; i++){
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

        _inventory[8].name = "Empty";
        _inventory[8].description = "";
        _inventory[8].price = 0;
        _inventory[8].candy_type = ""; 
        setCandyAmount(getCandyAmount() - 1);
        return true;
    }
    
    return false;
}

int Player::drawCard(){
    double random = rand() % 100 + 1;
    if(random > 0 && random <= 30){
        cout << "You drew a Marshmallow Magenta card. Your game piece advances to Magenta tile. Here's the updated trail\n";
        return 1;
    } else if(random > 30  && random <= 60){
        cout << "You drew a Minty Green card. Your game piece advances to Green tile. Here's the updated trail\n";
        return 2;
    } else if(random > 60  && random <= 90){
        cout << "You drew a Bubblegum Blue card. Your game piece advances to Blue tile. Here's the updated trail\n";
        return 3;
    } else if(random > 90  && random <= 93){
        cout << "You drew a Double Marshmallow Magenta card. Your game piece advances two Magenta tiles. Here's the updated trail\n";
        return 4;
    } else if(random > 93  && random <= 96){
        cout << "You drew a Double Minty Green card. Your game piece advances two Green tiles. Here's the updated trail\n";
        return 5;
    } else if(random > 96  && random <= 100){
        cout << "You drew a Double Bubblegum Blue card. Your game piece advances two Blue tiles. Here's the updated trail\n";
        return 6;
    } 
    return 0;
}

bool Player::playRockPaperScissors(){
    char p1c;
    int  randomChoice= rand() % 3 + 1;
    char computerChoice;
    if( randomChoice == 1){
        computerChoice = 'r';
    }
    else if(randomChoice == 2){
        computerChoice = 'p';
    }
    else if(randomChoice == 3){
        computerChoice = 's';
    }
    cout << "Enter r, p, or s\n";
    cin >> p1c;
    while(p1c != 'r' && p1c != 'p' && p1c != 's'){
        cout << "Invalid selection!\n";
        cin >> p1c;
    }
   
    while(p1c == computerChoice){
        cout << "Tie! Play again\n";
        randomChoice= rand() % 3 + 1;
        cout << "Player 1: Enter r, p, or s\n";
        cin >> p1c;
    }
    if((p1c == 'r' && computerChoice == 's') || (p1c == 'p' && computerChoice == 'r') || (p1c == 's' && computerChoice == 'p')){
        return true;
    }
    else if((computerChoice == 'r' && p1c == 's') || (computerChoice == 'p' && p1c == 'r') || (computerChoice == 's' && p1c == 'p')){
        return false;
    }

    return false;

}

void Player::populatePlayer(string character){
    if(character == "Toffee_Todd"){
        setStamina(200);
        setGold(20);
    }
    else if(character == "Chocolate_Charlie"){
        setStamina(50);
        setGold(100);
    }
    else if(character == "Sour_Saul"){
        setStamina(100);
        setGold(60);
    }
    else if(character == "Honey_Harold"){
        setStamina(150);
        setGold(40);
    }
}