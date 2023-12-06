#include <iostream>
#include <string>
#include "CLPlayer.h"
using namespace std;

Player::Player(){//default constructor
    _stamina = 0;
    _gold = 0;
    _effect = "";
    for(int i = 0; i < 9; i++){
        _inventory[i].name = "Empty";
    }
    _candy_amount = 0;
}
Player::Player(int stamina, double gold, string effect, Candy inventory[], const int candy_amount){//parameterized constructor
    _stamina = stamina;
    _gold = gold; 
    _effect = effect;
    for(int i = 0; i < candy_amount; i++){//renames empty spaces to "Empty"
        _inventory[i] = inventory[i];
        if(inventory[i].name == ""){
            _inventory[i].name = "Empty";
        }
    }
    for(int i = candy_amount; i < 9; i++){//starting from last candy to end of inventory, names spaces to "Empty"
        _inventory[i].name = "Empty";
    }
    int actual_candy = 0;
    for(int i = 0; i < 9; i++){
        if(_inventory[i].name != "Empty"){//any time there is a candy, increase actual candy amount
            actual_candy++;
        }
    }
    if(actual_candy == 0){
        _candy_amount = 0;//if there are no candies, then candy amount is 0
    }
    else{
        _candy_amount = candy_amount;//candy amount is how many candies there actually are
    }
}

//getters
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

//setters
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

void Player::printInventory(){//prints inventory
    for(int i = 0; i < _MAX_CANDY_AMOUNT; i++){
        cout << "[" << _inventory[i].name << "]  ";
        if(i == 2 || i == 5){
            cout << endl;
        }
    }
      for(int i = getCandyAmount(); i < 9; i++){
        _inventory[i].name = "Empty";
    }
}

Candy Player::findCandy(string candy_name){//finds candy in player inventory
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
bool Player::addCandy(Candy c){//adds a candy to players inventory
    bool replaceCandy;
    char replaceChoice;
    int indexToRemove;
    if(getCandyAmount() == 9){//if the inventory is full, ask to replace an index
        cout << "Your inventory is full! Would you like to replace an existing candy with a new one?(y/n)\n";
        cin >> replaceChoice;
        while((replaceChoice != 'y' && replaceChoice != 'Y') && (replaceChoice != 'n' && replaceChoice != 'N')){//exception handling for choice
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid option, try again\n";
            cin >> replaceChoice;
        }
        if(replaceChoice == 'y' || replaceChoice == 'Y'){
            printInventory();//shows the player their inventory
            cout << endl;
            cout << "Please choose an index to replace a candy at (1-9)\n";
            cin >> indexToRemove;
            while(indexToRemove > 9 && indexToRemove < 1){//exception handling for index
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
    setCandyAmount(getCandyAmount() + 1);//candy amount is 1 less

    return true;
}

bool Player::removeCandy(string name){//removes a candy
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
        if(lowerInventory == lowerName){//if lowercase candy name is equal to lowercase index name
            removeIndex = i;
            foundFlag = true;
        } 
    }
    if(foundFlag == true){
        for(int j = removeIndex; j < 8;j++){
            _inventory[j] = _inventory[j + 1];
        }   
        //makes last index empty
        _inventory[8].name = "Empty";
        _inventory[8].description = "";
        _inventory[8].price = 0;
        _inventory[8].candy_type = ""; 
        setCandyAmount(getCandyAmount() - 1);//one less candy udpate
        return true;
    }
    return false;
}

int Player::drawCard(){//draw card function
    Card card;
    double random = rand() % 100 + 1;
    if(random > 0 && random <= 30){//30% for single cards
        cout << "You drew a Marshmallow Magenta card. Your game piece advances to Magenta tile. Here's the updated trail\n";
        card.color = "magenta";
        card.x2 = false;
        return 1;
    } else if(random > 30  && random <= 60){
        cout << "You drew a Minty Green card. Your game piece advances to Green tile. Here's the updated trail\n";
        card.color = "green";
        card.x2 = false;
        return 2;
    } else if(random > 60  && random <= 90){
        cout << "You drew a Bubblegum Blue card. Your game piece advances to Blue tile. Here's the updated trail\n";
        card.color = "blue";
        card.x2 = false;
        return 3;
    } else if(random > 90  && random <= 93){//3% for double cards
        cout << "You drew a Double Marshmallow Magenta card. Your game piece advances two Magenta tiles. Here's the updated trail\n";
        card.color = "magenta";
        card.x2 = true;
        return 4;
    } else if(random > 93  && random <= 96){
        cout << "You drew a Double Minty Green card. Your game piece advances two Green tiles. Here's the updated trail\n";
        card.color = "green";
        card.x2 = true;
        return 5;
    } else if(random > 96  && random <= 100){
        cout << "You drew a Double Bubblegum Blue card. Your game piece advances two Blue tiles. Here's the updated trail\n";
        card.color = "blue";
        card.x2 = true;
        return 6;
    } 
    return 0;
}

bool Player::playRockPaperScissors(){
    char p1c;
    int  randomChoice= rand() % 3 + 1;
    char computerChoice;
    if(randomChoice == 1){//converts number to r, p, or s
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
    while(p1c != 'r' && p1c != 'p' && p1c != 's'){//exception handling for choice
        cout << "Invalid selection!\n";
        cin >> p1c;
    }

    while(p1c == computerChoice){//exception for ties
        cout << "Tie! Play again\n";
        randomChoice= rand() % 3 + 1;//redoes the random number
        cout << "Player 1: Enter r, p, or s\n";
        cin >> p1c;
    }
    if((p1c == 'r' && computerChoice == 's') || (p1c == 'p' && computerChoice == 'r') || (p1c == 's' && computerChoice == 'p')){
        return true;//player wins
    }
    else if((computerChoice == 'r' && p1c == 's') || (computerChoice == 'p' && p1c == 'r') || (computerChoice == 's' && p1c == 'p')){
        return false;//player loses
    }

    return false;
}

void Player::populatePlayer(string character){//sets player attributes to character attributes
    if(character == "Toffee_Todd"){
        setStamina(100);
        setGold(20);
        return;
    }
    else if(character == "Chocolate_Charlie"){
        setStamina(50);
        setGold(100);
        return;
    }
    else if(character == "Sour_Saul"){
        setStamina(80);
        setGold(60);
        return;
    }
    else if(character == "Honey_Harold"){
        setStamina(90);
        setGold(40);
        return;
    }
}

bool Player::hasMagicCandy(){//checks if player has a magical candy in their inventory
    for(int i = 0; i < 9; i++){
        if(_inventory[i].candy_type == "magical"){
            return true;//returns first magical candy found
        }
    }
    return false;//if no magical candy, return false
}

bool Player::hasImmunityCandy(){//checks if player has an immunity candy to use
    for(int i = 0; i < 9; i++){
        if(_inventory[i].candy_type == "immunity"){
            return true;
        }
    }
    return false;//if no immunity candy, return false
}

bool Player::hasRobbersRepel(){//checks if player has robbers repel
    for(int i = 0; i < 9; i++){
        if(_inventory[i].candy_type == "repel"){
            return true;
        }
    }
    return false;//returns false if no repel candy
}

Candy Player::findMagicalCandy(){//looks for a magical candy
    Candy empty = {"not found","","",0,"",0};
    for(int i = 0; i < 9; i++){
        if(_inventory[i].candy_type == "magical"){
            return _inventory[i];
        }
    }
    return empty;//if not found, returns empty
}


Candy Player::findImmunityCandy(){//finds highest strength candy first
    Candy empty = {"","","",0,"",0};//default candy
    for(int i = 0; i < 9; i++){//checks for strength 3 candy first
        if(_inventory[i].candy_type == "immunity" && _inventory[i].effect_value == 3){
            return _inventory[i];
        }
    }
    for(int i = 0; i < 9; i++){//then strength 2
        if(_inventory[i].candy_type == "immunity" && _inventory[i].effect_value == 2){
            return _inventory[i];
        }
    }
    for(int i = 0; i < 9; i++){//and finally one
        if(_inventory[i].candy_type == "immunity" && _inventory[i].effect_value == 1){
            return _inventory[i];
        }
    }
    return empty;//if no immunity, strength is 0
}


int Player::determineImmunityStrength(Candy immunityCandy){//determines strength of already found immmunity candy
    if(immunityCandy.effect_value == 1){
        return 1;
    }
    else if(immunityCandy.effect_value == 2){
        return 2;
    }
    else if(immunityCandy.effect_value == 3){
        return 3;
    }
    return 0;
}

int Player::determinePoisonStrength(Candy poisonCandy){//determines poison level for already found poison candy
    if(poisonCandy.effect_value == -10){
        return 1;
    }
    else if(poisonCandy.effect_value == -15){
        return 2;
    }
    else if(poisonCandy.effect_value == -20){
        return 3;
    }
    return 0;
}