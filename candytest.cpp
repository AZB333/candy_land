#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "CLPlayer.h"
#include "Board.h"
#include "Store.h"

struct Character{
    string name;
    int stamina;
    int gold;
    vector<string> candies;
};

struct Riddle{
    string question;
    string answer;
};

vector<Candy> readCandy(string file_name, vector<Candy> candies){ //loads candy file
    ifstream candyFile;
    string line;
    candyFile.open(file_name);
    if(candyFile.fail()){
        cout << "Failed to load text file\n";
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
        getline(candyFile, line);
        while(getline(candyFile, line)){//gets everything between '|'
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
            candies.push_back(current_candy);
            }
        }
    }
    candyFile.close();
    return candies;
}

vector<Character> readCharacter(string fileName, vector<Character> characters){//reads character file
    ifstream characterFile;
    characterFile.open(fileName);
    if(characterFile.fail()){
        cout << "Failed to open text file\n";
        return characters;
    }
    else{
        string name = "";
        string stamina = "";
        int actualStamina = 0;
        string gold = "";
        int actualGold = 0;
        string candyLine;
        string line;
        getline(characterFile, line);
        while(getline(characterFile, line)){//gets everything between '|'
            vector<string> candyNames;
            stringstream ss(line);
            int iterator = 0;
            Character current_character;
            if(line.size() != 0){
            while(getline(ss, line, '|')){
                if(iterator == 0){
                    iterator ++;
                    name = line;
                } else if(iterator == 1){
                    iterator++;
                    stamina = line;
                    actualStamina = stoi(stamina);
                } else if(iterator == 2){
                    iterator++;
                    gold = line;
                    actualGold = stoi(gold);
                } else if(iterator == 3){
                    stringstream candySS(line);
                    while(getline(candySS, line, ',')){//gets every candy
                        candyNames.push_back(line);
                    }
                }
            }
            current_character.name = name;
            current_character.stamina = actualStamina;
            current_character.gold = actualGold;
            for(int i = 0; i < candyNames.size(); i++){
                current_character.candies.push_back(candyNames[i]);
            }
            characters.push_back(current_character);
            }
        }
    }
    characterFile.close();
    return characters;

}

vector<Riddle> readRiddles(string fileName, vector<Riddle> riddles){
    ifstream riddleFile;
    string line;
    riddleFile.open(fileName);
    if(riddleFile.fail()){
        cout << "Failed to load text file\n";
        return riddles;
    }
    else{            
        string question = "";
        string answer = "";
        while(getline(riddleFile, line)){

            stringstream ss(line);
            int iterator = 0;
            Riddle current_riddle;
            if(line.size() != 0){
            while(getline(ss, line, '|')){
                if(iterator == 0){
                    iterator ++;
                    question = line;
                } else if(iterator == 1){
                    answer = line;
            }
            current_riddle.question = question;
            current_riddle.answer = answer;
            }
            riddles.push_back(current_riddle);
        }
    }
    riddleFile.close();
    return riddles;
}
}

bool Calamities(Player &player){//player is passed by reference
    srand((unsigned) time(NULL));
    char bandits;
    char labyrinth;
    char avalanche;
    bool trap = false;
    bool rpsStatus;
    int random = rand() % 100 + 1;
    if(random >=1 && random <=12){
        cout << "Candy Bandits! Do you want to play rock paper scissors to try to avoid them?\n";
        cin >> bandits;
        while((bandits != 'y' && bandits != 'Y') && (bandits != 'n' && bandits != 'N')){
        cin.clear();
        cout << "Invalid option, try again\n";
        cin >> bandits;
        
    }
    if(bandits == 'y' || bandits == 'Y'){
            rpsStatus = player.playRockPaperScissors();
            if(rpsStatus == true){
                cout << "You've won! The bandits leave you alone out of respect\n";
                return true;
            }
            else{
                int coinLoss = rand() % 10 + 1;
                cout << "The bandits beat you to a pulp, taking " << coinLoss << " coins\n";
                player.setGold(player.getGold() - coinLoss);
                if(player.getGold() < 0){//if player has less than 0 gold after, set to 0
                    player.setGold(0);
                }
                return true;
            }
        }
        else if(bandits == 'n' || bandits == 'N'){
            int coinLoss = rand() % 10 + 1;
            cout << "You surrender to the bandits, giving " << coinLoss << " coins in exchange for your life\n";
            player.setGold(player.getGold() - coinLoss);
             if(player.getGold() < 0){//if player has less than 0 gold after, set to 0
                player.setGold(0);
            }
            return true;
        }
    
    }
    else if(random >12 && random <= 26){
            cout << "Oh dear! You got lost in the lollipop labyrinth! Do you wanna play rock paper scissors to see if you can make it out?\n";
            cin >> labyrinth;
            while((labyrinth != 'y' && labyrinth != 'Y') && (labyrinth != 'n' && labyrinth != 'N')){
            cin.clear();
            cout << "Invalid option, try again\n";
            cin >> labyrinth;
            
        }
        if(labyrinth == 'y' || labyrinth == 'Y'){
                rpsStatus = player.playRockPaperScissors();
                if(rpsStatus == true){
                    cout << "With insane luck and skill, you make it out of the labyrinth in 5 minutes\n";
                    return true;
                } else{
                    cout << "You get lost in the labyrinth and lose your next turn\n";
                    return false;
                }
            }
            else if(labyrinth == 'n' || labyrinth == 'N'){
                cout << "You spend 5 years in the labyrinth, losing your next turn  \n";
                return false;
            }
    }
    else if(random >26 && random <= 32){
            cout << "Watch out! A candy avalanche has struck! Do you want to play rock paper scissors to see if you survive in one piece?\n";
            cin >> avalanche;
            while((avalanche != 'y' && avalanche != 'Y') && (avalanche != 'n' && avalanche != 'N')){
            cin.clear();
            cout << "Invalid option, try again\n";
            cin >> avalanche;
        }
        if(avalanche == 'y' || avalanche == 'Y'){
                rpsStatus = player.playRockPaperScissors();
                if(rpsStatus == true){
                    cout << "You surfed the avalanche down and landed unharmed!\n";
                    return true;
                }
                else{
                    int stamLost = rand() % 5 + 5;
                    player.setStamina(player.getStamina() - stamLost);
                    if(player.getStamina() < 0){
                        player.setStamina(0);
                    }
                    cout << "You tried to surf the avalanche and fell, losing " << stamLost << " stamina and your next turn\n";
                    return false;
                }
            }
            else if(avalanche == 'n' || avalanche == 'N'){
                int stamLost = rand() % 5 + 5;
                player.setStamina(player.getStamina() - stamLost);
                if(player.getStamina() < 0){
                    player.setStamina(0);
                }
                cout << "You watch as the avalanche engulfs you, losing " << stamLost << " stamina and your next turn\n";
                return false;
            }
    }
    else if(random >32 && random <= 40){
        cout << "Oops! You are stuck in a sticky taffy trap!";
        trap = player.hasMagicCandy();
        if(trap == false){
            cout << " Sadly, you do not have a magical candy, so you lose your turn\n";
            return false;
        }
        else{
            char useCandy;
            cout << " There is still hope, you have a magical candy that can get you free from the trap. Would you like to use it?\n";
            cin >> useCandy;
            while((useCandy != 'y' && useCandy != 'Y') && (useCandy != 'n' && useCandy != 'N')){
                cin.clear();
                cout << "Invalid option, try again\n";
                cin >> useCandy;
            }
            if(useCandy == 'y' || useCandy == 'Y'){
                cin.ignore(1000,'\n');
                Candy magicalCandy = player.findMagicalCandy();
                cout << "You have used " << magicalCandy.name << " to free yourself\n";
                player.removeCandy(magicalCandy.name);
                return true;
            }
            else if(useCandy == 'n' || useCandy == 'N'){
                cout << "You have chosen not to use a candy to free yourself, losing your next turn\n";
                return false;
            }
        }
    }
    return true;
}

int specialTiles(Player &player, int position){
    bool onSpecialTile = false;
    int specialTile1 = rand() % 21 + 1;
    int specialTile2 = rand() % 21 + 20;
    int specialTile3 = rand() % 21 + 41;
    int specialTile4 = rand() % 21 + 61;
    int landedOnTile = rand() % 100 + 1;
    if(landedOnTile > 75 && landedOnTile < 100){
        onSpecialTile = true;
    }
    if(position == specialTile1 || position == specialTile2 || position == specialTile3 ||position == specialTile4){
        onSpecialTile = true;
    }
    if(onSpecialTile == true){
        int randomTile = rand() % 100 + 1;
        if(randomTile >= 75 && randomTile < 82){
            cout << "You landed on a Shortcut Tile! You've been given the golden opportunity to leap ahead four tiles!\n";
            return 1;
        }
        else if(randomTile >= 82 && randomTile < 88){
            cout << "You landed on an Ice Cream Shop Tile! You've been given an additional turn!\n";
            return 2;
        }
        else if(randomTile >= 88 && randomTile < 94){
            int goldLost = rand() % 5 + 10;
            cout << "Uh oh, a Gumdrop Forest Tile! You have lost " << goldLost << " gold, and were moved back 4 tiles\n";
            player.setGold(player.getGold() - goldLost);
            return 3;
        }
        else if(randomTile >= 94 && randomTile < 100){
            cout << "You've landed on a Gingerbread House Tile! You've been moved back to your previous position, and you've lost an immunity candy!\n";
            Candy candytoRemove = player.findImmunityCandy();
            player.removeCandy(candytoRemove.name);
            return 4;
        }
    }
    return 0;
}

bool answerRiddle(vector<Riddle> riddles){
    int riddleIndex = rand() % riddles.size();
    string riddleToSolve = riddles[riddleIndex].question;
    string riddleAnswer;
    cout << "To earn the hidden treasure, you must answer this riddle\n";
    cout << riddles[riddleIndex].question;
    cout << endl;
    cin >> riddleAnswer;
    if(riddleAnswer != riddles[riddleIndex].answer){
        cout << "Unfortunately that is incorrect, the correct answer was " << riddles[riddleIndex].answer << endl;
        return false;
    }
    else if(riddleAnswer == riddles[riddleIndex].answer){
        cout << "Congratulations! You have solved the riddle and discovered a hidden treasure!\n";
        return true;
    }
    return false;
}

void hiddenTreasures(Player &player, int position,vector<Riddle> riddles){
    int hiddenTreasure1 = rand() % 27 + 1;
    int hiddenTreasure2 = rand() % 27 + 28;
    int hiddenTreasure3 = rand() % 27 + 55;

    if(position == hiddenTreasure1 || position == hiddenTreasure2 || position == hiddenTreasure3 || position == 100){
        cout << "You have discovered a hidden treasure! ";
        bool riddleSolved = answerRiddle(riddles); //getting the treasure is determined by the answerRiddle function
        int treasureType = rand() % 100 + 1;
        if(riddleSolved == true){
            if (treasureType > 0 && treasureType <= 30) {
                int staminaRefill = rand() % 20 + 10;
                int initialStamina = player.getStamina();
                player.setStamina(player.getStamina() + staminaRefill);

                if(player.getStamina() > 100){
                    int stamOverflow = player.getStamina() - 100;
                    player.setStamina(100);  //cap the stamina at 100
                    int actualRefill = staminaRefill - stamOverflow;//actual amount replenished by
                    cout << "You found a hidden treasure! Your stamina has been replenished by " << actualRefill << " units!\n";
                } 
                else{
                    cout << "You found a hidden treasure! Your stamina has been replenished by " << staminaRefill << " units!\n";
                }
        }
            else if(treasureType > 30 && treasureType <= 40){
                int goldGain = rand() % 20 + 10;
                int initialGold = player.getGold();
                player.setGold(player.getGold() + goldGain);
                if(player.getGold() > 100){
                    int goldOverflow = player.getGold() - 100;
                    player.setGold(100);//cap gold at 100
                    int actualGold = goldGain - goldOverflow;//actual gold
                    cout << "You have found a hidden treasure! You have found " << actualGold << " gold!\n";
                }
                else{
                    cout << "You found a hidden treasure! You have found " << goldGain << " gold!\n";
                }
            }
            else if(treasureType > 40 && treasureType <= 70){
                Candy robbersRepel = {"Robber's Repel","An anti-robbery shield, safeguarding the player's gold from potential theft by others during their journey","protection",0,"repel",0};
                cout << "You have found the Robber's Repel Candy! Use this candy to avoid being robbed when landing on another player's tile!\n";
                player.addCandy(robbersRepel);
                cout << "Player inventory is now \n";
                player.printInventory();
                cout << endl;
            }
            else if(treasureType > 70 && treasureType <= 100){
                int acquisitionType = rand() % 100 + 1;
                if(acquisitionType <= 70){
                    Candy vigorBean = {"Jellybean of Vigor","","stamina",50,"jellybean",0};
                    cout << "You found the Jellybean of Vigor! Using it boosts stamina by 50 points!\n";
                    player.addCandy(vigorBean);
                    cout << "Player inventory is now \n";
                    player.printInventory();
                    cout << endl;
                }
                else{
                    Candy treasureTruffle = {"Treasure Hunter's Truffle","allows the player to unlock a hidden treasure","",0,"treasure",0};
                    cout << "You found the Treasure Hunter's Truffle! If you use it, you have the ability to solve a riddle for another hidden treasure!\n";
                    player.addCandy(treasureTruffle);
                    cout << "Player inventory is now \n";
                    player.printInventory();
                    cout << endl;
                }
            }
        }
    }
}

 int determineMoveAmount(int playerPos, int cardResult){
    int moveAmount = 0;
    if((playerPos % 3 == 0 && cardResult == 2) || (playerPos % 3 == 1 && cardResult == 3) || (playerPos % 3 == 2 && cardResult == 1)){//pos two less than result
        moveAmount = 1;
    }
    else if((playerPos % 3 == 0 && cardResult == 3) || (playerPos % 3 == 1 && cardResult == 1) || (playerPos % 3 == 2 && cardResult == 2)){//pos equals result
        moveAmount = 2;
    }
    else if((playerPos % 3 == 0 && cardResult == 1) || (playerPos % 3 == 1 && cardResult == 2) || (playerPos % 3 == 2 && cardResult == 3)){//pos is one less than result
        moveAmount = 3;
    }
    else if((playerPos % 3 == 0 && cardResult == 5) || (playerPos % 3 == 1 && cardResult == 6) || (playerPos % 3 == 2 && cardResult == 4)){//pos five less than result
        moveAmount = 4;
    }
    else if((playerPos % 3 == 0 && cardResult == 6) || (playerPos % 3 == 1 && cardResult == 4) || (playerPos % 3 == 2 && cardResult == 5)){//pos five less than result
        moveAmount = 5;
    }
    else if((playerPos % 3 == 0 && cardResult == 4) || (playerPos % 3 == 1 && cardResult == 5) || (playerPos % 3 == 2 && cardResult == 6)){//pos four less than result
        moveAmount = 6;
    }
    return moveAmount;
}

void displayCharacters(vector<Character> characters){
        for(int i = 0; i < characters.size(); i++){ //this is the problem
        cout << "Name: " << characters[i].name << " " << endl;
        cout << "Stamina: " <<characters[i].stamina << " " << endl;
        cout << "Gold: " <<characters[i].gold << " " << endl;
        cout << "Candies: \n";
        int candyCount = 0;
        for(int j = 0; j < characters[i].candies.size(); j++){
            cout << "[" << characters[i].candies[j] << "]   ";
            candyCount++;
            if(candyCount % 3 == 0 && j < characters[i].candies.size() - 1){
                cout << endl;
            }
        }
        cout << "\n----------------------------------------------\n";
    }
}


void visit1CandyStore(bool canVisitStatus, Player &player, Store &store){
    bool storeFound = false;
    if(canVisitStatus == false){
        return;
    } else{
        string storeChoice = "reset";
        cin.ignore(1000,'\n');
        store.displayCandies();
        getline(cin, storeChoice);
        if(storeChoice == store.findCandy(storeChoice).name){
            storeFound = true;
            player.addCandy(store.findCandy(storeChoice));
             cout << "Player 1 inventory is now\n";
            player.printInventory();
            player.setGold(player.getGold() - player.findCandy(storeChoice).price);
            cout << endl;
        
        }
        while(storeFound == false){
            cin.clear();
            cout << "Invalid input. Please try again\n";
            getline(cin, storeChoice);
            if(storeChoice == store.findCandy(storeChoice).name){
                player.addCandy(store.findCandy(storeChoice));
                storeFound = true;
            }
            
        }
        cout << "Player 1 inventory is now\n";
        player.printInventory();
        player.setGold(player.getGold() - player.findCandy(storeChoice).price);
        cout << endl;

    }
}
void visit2CandyStore(bool canVisitStatus, Player &player, Store &store){
    bool storeFound = false;
    if(canVisitStatus == false){
        return;
    } else{
        string storeChoice = "reset";
        cin.ignore(1000,'\n');
        store.displayCandies();
        getline(cin, storeChoice);
        if(storeChoice == store.findCandy(storeChoice).name){
            storeFound = true;
            player.addCandy(store.findCandy(storeChoice));
             cout << "Player 2 inventory is now\n";
            player.printInventory();
            player.setGold(player.getGold() - player.findCandy(storeChoice).price);
            cout << endl;
        
        }
        while(storeFound == false){
            cin.clear();
            cout << "Invalid input. Please try again\n";
            getline(cin, storeChoice);
            if(storeChoice == store.findCandy(storeChoice).name){
                player.addCandy(store.findCandy(storeChoice));
                storeFound = true;
            }
            
        }
        cout << "Player 2 inventory is now\n";
        player.printInventory();
        player.setGold(player.getGold() - player.findCandy(storeChoice).price);
        cout << endl;

    }
}


void removeCharacter(vector<Character> &characters, string name){
    for(int i = 0; i < characters.size(); i++){
        if(characters[i].name == name){
            for(int j = i; j < characters.size() - 1; j++){
                characters[j] = characters[j + 1];
            }
            characters.pop_back();
            return;
        }
    }
}

void sameTileCheck(Player &movedPlayer, Player &initialPlayer, string initialPlayerName, int movedPlayerPos, int initialPlayerPos){
    if(movedPlayerPos == initialPlayerPos && movedPlayerPos > 0){
        char useRepel;
        int goldLost = rand() & 25 + 5;
        cout << "You have landed on the same tile as " << initialPlayerName << "!\n";
        if(movedPlayer.hasRobbersRepel() == true){
            cout << "You have the Robber's Repel candy! Would you like to lose it to avoid being robbed by " << initialPlayerName << "?\n";
            cin >> useRepel;
            while(useRepel != 'y' && useRepel != 'Y' && useRepel != 'n' && useRepel != 'N'){
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Invalid option. Please try again\n";
                cin >> useRepel;
            }
            if(useRepel == 'y' || useRepel == 'Y'){
                cout << "You have used Robber's Repel to avoid being robbed and move " << initialPlayerName << " back one spot!\n";
                movedPlayer.removeCandy("Robber's Repel");
            }
            else{
                cout << "You willingly chose to be robbed by " << initialPlayerName << ", losing " << goldLost << " gold\n";
                initialPlayer.setGold(initialPlayer.getGold() + goldLost);
                if(initialPlayer.getGold() > 100){
                    initialPlayer.setGold(100);
                }
                movedPlayer.setGold(movedPlayer.getGold() - goldLost);
                if(movedPlayer.getGold() < 0){
                    movedPlayer.setGold(0);
                }
            }
        }
        else{
            cout << "Unfortunately you do not have the Robber's Repel candy, and " << initialPlayerName << " has taken " << goldLost << " gold from you\n";
            initialPlayer.setGold(initialPlayer.getGold() + goldLost);
            if(initialPlayer.getGold() > 100){
                initialPlayer.setGold(100);
            }
        }
    }
}

void menu2Option(Player &player, Player &opponent,Board &board, int gummyTile, string candyToUse, vector<Riddle> allRiddles){
    bool candyFound = false;
    cin.ignore(1000,'\n');
    cout << "Here is a list of your candies:\n";
    player.printInventory();
    cout << "\nEnter a candy you wish to use\n";
    getline(cin, candyToUse);
    if(candyToUse == player.findCandy(candyToUse).name){
        candyFound = true;
    }
    while(candyFound == false){
        cin.clear();
        cout << "Not a valid candy in your inventory. Please try again\n";
        getline(cin, candyToUse);
        if(candyToUse == player.findCandy(candyToUse).name){
            candyFound = true;
        }
    }
    if(player.findCandy(candyToUse).candy_type == "magical"){//magical candies

        int staminaRefill = player.findCandy(candyToUse).effect_value;
        int initialStamina = player.getStamina();
        player.setStamina(player.getStamina() + staminaRefill);
        if(player.getStamina() > 100){
            int stamOverflow = player.getStamina() - 100;
            player.setStamina(100);  //cap the stamina at 100
            int actualRefill = staminaRefill - stamOverflow;//actual amount replenished by
            cout << "You have used " << candyToUse << ". Your stamina is increased by " << actualRefill << " points.\n";
        } 
        else{
            cout << "You have used " << candyToUse << ". Your stamina is increased by " << staminaRefill << " points.\n";
        }
        player.removeCandy(candyToUse);
    }
    else if(player.findCandy(candyToUse).candy_type == "poison"){//poison candies
        char useCandy;
        cout << "Do you want to use " << candyToUse << " against your opponent?\n";
        cin >> useCandy;
        if(useCandy == 'y' || useCandy == 'y'){//checks if opponents immunity candy is stronger than player's poison candy
            if(opponent.hasImmunityCandy() == true){
                int poisonStrength = player.determinePoisonStrength(player.findCandy(candyToUse));
                int immunityStrength = opponent.determineImmunityStrength(opponent.findImmunityCandy());
                string opponentCandy = opponent.findImmunityCandy().name;
                if(immunityStrength >= poisonStrength){
                    cout << "You have used " << candyToUse << " but your opponent has " << opponentCandy << " to protect against your poison candy\n";
                    player.removeCandy(candyToUse);
                    opponent.removeCandy(opponentCandy);
                }
                else{
                    cout << "You have used " << candyToUse << " and your opponent has lost " << player.findCandy(candyToUse).effect_value * -1 << " points of stamina.\n";
                    player.removeCandy(candyToUse);
                    opponent.setStamina(opponent.getStamina() - player.findCandy(candyToUse).effect_value);
                    if(opponent.getStamina() < 0){
                        opponent.setStamina(0);
                    }
            }
            }
            else{
                cout << "You have used " << candyToUse << " and your opponent has lost " << player.findCandy(candyToUse).effect_value << " points.\n";
                player.removeCandy(candyToUse);
                opponent.setStamina(opponent.getStamina() - player.findCandy(candyToUse).effect_value);
                if(opponent.getStamina() < 0){
                    opponent.setStamina(0);
                }
            }
        }
        else{
            cout << "You chose mercy and decided not to inflict harm on your opponent\n";
        }
    }
    else if(player.findCandy(candyToUse).candy_type == "gummy"){//gummy candies
        cout << "Which tile do you want to place " << candyToUse << " - gummy candy?\n";
        cin >> gummyTile;
        while(gummyTile < 0 || gummyTile > 83){
            cin.clear();
            cout << "Invalid input. Please try again\n";
            cin >> gummyTile;
        }
        cout << "You have successfully placed a gummy candy on tile " << gummyTile << ". Any player that lands on the gummy tile will be obstructed from advancing past the tile for two moves.\n";
        player.removeCandy(candyToUse);
    }
    else if(player.findCandy(candyToUse).candy_type == "immunity"){//immunity candies, not actually used here
        cout << "Immunity candies are used when they need to be, so you don't need to use them here\n";
    }
    else if(player.findCandy(candyToUse).candy_type == "jellybean"){//jellybean candy
        int staminaRefill = rand() % 20 + 10;
        int initialStamina = player.getStamina();
        player.setStamina(player.getStamina() + staminaRefill);

        if(player.getStamina() > 100){
            int stamOverflow = player.getStamina() - 100;
            player.setStamina(100);  //cap the stamina at 100
            int actualRefill = staminaRefill - stamOverflow;//actual amount replenished by
            cout << "You have used " << candyToUse << ". Your stamina is increased by " << actualRefill << " points.\n";
        } 
        else{
            cout << "You have used " << candyToUse << ". Your stamina is increased by " << staminaRefill << " points.\n";
        }
        player.removeCandy(candyToUse);
    }
    else if(player.findCandy(candyToUse).candy_type == "treasure"){//treasure hunter's truffle
        player.removeCandy(candyToUse);
        hiddenTreasures(player,100,allRiddles);//acts as though player has found a hidden treasure
    }
    else if(player.findCandy(candyToUse).candy_type == "repel"){
        cout << "You can only use this if you land on the same tile as another player!\n";
    }
    else if(player.findCandy(candyToUse).name == "Empty"){
        cout << "You gain the magical powers of empty, where nothing happens\n";
    }
}

void menu3Option(Player player, string playerName, string characterName){
    cout << "Here are your stats:\n";
    cout << "Player name: " << playerName << endl;
    cout << "Character: " << characterName << endl;
    cout << "Stamina: " << player.getStamina() << endl;
    cout << "Gold: " << player.getGold() << endl;
}


void menu1Option1(Player &mainPlayer, Player &otherPlayer, string mainPlayerName, string otherPlayerName, string character1Name, Board &game_board, bool &hasTurn, vector<Riddle> allRiddles, int gummyTile, string candyToUse){
    int movePlayer1;
    int specialTileResult;
    int menu1Choice;
    movePlayer1 = determineMoveAmount(game_board.getPlayer1Position(), mainPlayer.drawCard());
    game_board.movePlayer1(movePlayer1);
    game_board.displayBoard();
    sameTileCheck(mainPlayer,otherPlayer,otherPlayerName,game_board.getPlayer1Position(),game_board.getPlayer2Position());
    mainPlayer.setStamina(mainPlayer.getStamina() - 1);
    hasTurn = Calamities(mainPlayer);
    hiddenTreasures(mainPlayer, game_board.getPlayer1Position(), allRiddles);
    specialTileResult = specialTiles(mainPlayer,game_board.getPlayer1Position());
    if(specialTileResult == 1){
        game_board.movePlayer1(4);
    }
    else if(specialTileResult == 2){//might need to make each menu item a function
        cout << "It's " << mainPlayerName << "'s turn\nPlease select a menu option\n";//begins menu choices
        cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
        cin >> menu1Choice;
        while(menu1Choice != 1 && menu1Choice != 2 && menu1Choice != 3){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid choice, try again\n";
            cin >> menu1Choice;
        }
        while(menu1Choice != 1){//only drawing a card ends the turn
            if(menu1Choice == 2){
                menu2Option(mainPlayer,otherPlayer,game_board,gummyTile,candyToUse, allRiddles);
                cout << "It's " << mainPlayerName << "'s turn\nPlease select a menu option\n";
                cout << "1.  Draw a card\n2.  Use candy\n3.  Show mainPlayer stats\n";
                cin >> menu1Choice;
                while(menu1Choice != 1 && menu1Choice != 2 && menu1Choice != 3){
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cout << "Invalid choice, try again\n";
                    cin >> menu1Choice;
                }
            }
            else if(menu1Choice == 3){
                menu3Option(mainPlayer,mainPlayerName,character1Name);
                cout << "It's " << mainPlayerName << "'s turn\nPlease select a menu option\n";
                cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
                cin >> menu1Choice;
                while(menu1Choice != 1 && menu1Choice != 2 && menu1Choice != 3){
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cout << "Invalid choice, try again\n";
                    cin >> menu1Choice;
                }
            }
        }
        if(menu1Choice == 1){
            menu1Option1(mainPlayer,otherPlayer,mainPlayerName,otherPlayerName, character1Name,game_board,hasTurn,allRiddles, gummyTile, candyToUse);
        }
    }
    else if(specialTileResult == 3){
        game_board.movePlayer1(-4);
    }
    else if(specialTileResult == 4){
        game_board.movePlayer1(movePlayer1 * -1);
    }
}

void menu2Option1(Player &mainPlayer, Player &otherPlayer, string mainPlayerName, string otherPlayerName, string character2Name, Board &game_board, bool &hasTurn, vector<Riddle> allRiddles, int gummyTile, string candyToUse){
    int movePlayer2;
    int specialTileResult;
    int menu2Choice;
    movePlayer2 = determineMoveAmount(game_board.getPlayer2Position(), mainPlayer.drawCard());
    game_board.movePlayer2(movePlayer2);
    game_board.displayBoard();
    sameTileCheck(otherPlayer,mainPlayer,otherPlayerName,game_board.getPlayer2Position(),game_board.getPlayer1Position());
    mainPlayer.setStamina(mainPlayer.getStamina() - 1);
    hasTurn = Calamities(mainPlayer);
    hiddenTreasures(mainPlayer, game_board.getPlayer2Position(), allRiddles);
    specialTileResult = specialTiles(mainPlayer,game_board.getPlayer2Position());
    if(specialTileResult == 1){
        game_board.movePlayer2(4);
    }
    else if(specialTileResult == 2){//might need to make each menu item a function
        cout << "It's " << mainPlayerName << "'s turn\nPlease select a menu option\n";//begins menu choices
        cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
        cin >> menu2Choice;
        while(menu2Choice != 1 && menu2Choice != 2 && menu2Choice != 3){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid choice, try again\n";
            cin >> menu2Choice;
        }
        while(menu2Choice != 1){//only drawing a card ends the turn
            if(menu2Choice == 2){
                menu2Option(otherPlayer,mainPlayer,game_board,gummyTile,candyToUse, allRiddles);
                cout << "It's " << otherPlayerName << "'s turn\nPlease select a menu option\n";
                cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
                cin >> menu2Choice;
                while(menu2Choice != 1 && menu2Choice != 2 && menu2Choice != 3){
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cout << "Invalid choice, try again\n";
                    cin >> menu2Choice;
                }
            }
            else if(menu2Choice == 3){
                menu3Option(otherPlayer,otherPlayerName,character2Name);
                cout << "It's " << otherPlayerName << "'s turn\nPlease select a menu option\n";
                cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
                cin >> menu2Choice;
                while(menu2Choice != 1 && menu2Choice != 2 && menu2Choice != 3){
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cout << "Invalid choice, try again\n";
                    cin >> menu2Choice;
                }
            }
        }
        if(menu2Choice == 1){
            menu2Option1(mainPlayer,otherPlayer,mainPlayerName,otherPlayerName, character2Name,game_board,hasTurn,allRiddles, gummyTile, candyToUse);
        }
    }
    else if(specialTileResult == 3){
        game_board.movePlayer2(-4);
    }
    else if(specialTileResult == 4){
        game_board.movePlayer2(movePlayer2 * -1);
    }
}


int main(){//finish making player 2 functional
    srand((unsigned) time(NULL));
    Board game_board; //game prep variables
    Player player1;
    Player player2;
    string candyFileName = "candy.txt";
    string characterFileName = "characters.txt";
    string riddleFileName = "riddles.txt";
    vector<Candy> allCandies;
    vector<Character> allCharacters;
    vector<Riddle> allRiddles;
    allCandies = readCandy(candyFileName, allCandies);
    allCharacters = readCharacter(characterFileName, allCharacters);
    allRiddles = readRiddles(riddleFileName, allRiddles);
    bool rpsStatus;
    bool endOfGame = false;
    bool hasTurn1 = true;
    bool hasTurn2 = true;


    int numParticipants;//player creation variables
    string player1Name;
    string player2Name;
    string character1Name;
    string character2Name;
    bool character1Found = false;
    bool character2Found = false;

    char candyStore1Visit;//starting store variables
    char candyStore2Visit;
    string startingStore1Choice;
    string startingStore2Choice;
    bool startingCandy1Found = false;
    bool startingCandy2Found = false;
    bool visitCandy1Store = false;
    bool visitCandy2Store = false;

    Store store1;//create the stores here, populate and display them later
    Store store2;
    Store store3;
    int store1Pos = rand() % 27 + 1;
    if(store1Pos % 3 == 1){
        store1Pos += 2;
    } else if(store1Pos % 3 == 2){
        store1Pos += 1;
    }
    int store2Pos = rand() % 27 + 28;
     if(store2Pos % 3 == 1){
        store2Pos -= 1;
    } else if(store2Pos % 3 == 2){
        store2Pos += 1;
    }
    int store3Pos = rand() % 27 + 55;
    if(store3Pos % 3 == 1){
        store3Pos -= 1;
    } else if(store3Pos % 3 == 2){
        store3Pos += 1;
    }
    game_board.addCandyStore(store1Pos);
    game_board.addCandyStore(store2Pos);
    game_board.addCandyStore(store3Pos);

    ////////////Beginning of game prep//////////////////
    cout << "Welcome to the game of Candyland. Please enter the number of participants\n";
    cin >> numParticipants;
    while(numParticipants != 2){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Please choose 2 participants\n";
        cin >> numParticipants;
    }
    
    cout << "Enter Player 1 name:\n";
    cin >> player1Name;
    cout << "Awesome! Here is a list of characters a player can select from\n";
    displayCharacters(allCharacters);
    cout << "The selected character is\n";
    cin >> character1Name;
    
    for(int i = 0; i < allCharacters.size(); i++){//find the character, then the candies, then the candies in the candies file
        if(character1Name == allCharacters[i].name){
            character1Found = true;
            for(int j = 0; j < allCharacters[i].candies.size(); j++){//k is needed
                for(int k = 0; k < allCandies.size(); k++){
                    if(allCharacters[i].candies[j] == allCandies[k].name){
                        player1.addCandy(allCandies[k]);
                    }
                }
            }
        }
    }
    while(character1Found == false){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Not a valid character, try again:\n";
        cin >> character1Name;
        for(int i = 0; i < allCharacters.size(); i++){
            if(character1Name == allCharacters[i].name){
                for(int j = 0; j < allCharacters[i].candies.size(); j++){
                    for(int k = 0; k < allCandies.size(); k++){
                        if(allCharacters[i].candies[j] == allCandies[k].name){
                            player1.addCandy(allCandies[k]);
                        }
                    }
                }
                character1Found = true;
            }

        }
    }
    cout << "Player 1 inventory is now \n";
    player1.printInventory();
    player1.populatePlayer(character1Name);
    removeCharacter(allCharacters,character1Name);

    cout << "\nDo you want to visit the candy store?\n";
    cin >> candyStore1Visit;
    while((candyStore1Visit != 'y' && candyStore1Visit != 'Y') && (candyStore1Visit != 'n' && candyStore1Visit != 'N')){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid option, try again\n";
        cin >> candyStore1Visit;
    }
    if(candyStore1Visit == 'y' || candyStore1Visit == 'Y'){
        cin.ignore(1000,'\n');
        Store startingStore1;
        startingStore1.populateStore(candyFileName, allCandies);
        startingStore1.displayCandies();
        getline(cin, startingStore1Choice);
        if(startingStore1Choice == startingStore1.findCandy(startingStore1Choice).name){
            startingCandy1Found = true;
            visitCandy1Store = player1.addCandy(startingStore1.findCandy(startingStore1Choice));
        }
        while(startingCandy1Found == false){
            cin.clear();
            cout << "Invalid input. Please try again\n";
            getline(cin, startingStore1Choice);
            if(startingStore1Choice == startingStore1.findCandy(startingStore1Choice).name){
                player1.addCandy(startingStore1.findCandy(startingStore1Choice));
                startingCandy1Found = true;
            }
        }
        cout << "Player 1 inventory is now\n";
        player1.printInventory();
        player1.setGold(player1.getGold() - player1.findCandy(startingStore1Choice).price);
        cout << endl;
    }
        
        

    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////

    cout << "Enter Player 2 name:\n";
    cin >> player2Name;
    cout << "Awesome! Here is a list of characters a player can select from\n";
    displayCharacters(allCharacters);
    cout << "The selected character is\n";
    cin >> character2Name;
    while(character1Name == character2Name){
        cout << "Cannot be the same character as " << player1Name << ". Please choose a different character\n";
        cin >> character2Name;
    }
    
    for(int i = 0; i < allCharacters.size(); i++){//find the character, then the candies, then the candies in the candies file
        if(character2Name == allCharacters[i].name){
            character2Found = true;
            for(int j = 0; j < allCharacters[i].candies.size(); j++){//k is needed
                for(int k = 0; k < allCandies.size(); k++){
                    if(allCharacters[i].candies[j] == allCandies[k].name){
                        player2.addCandy(allCandies[k]);
                    }
                }
            }
        }
    }
    while(character2Found == false){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Not a valid character, try again:\n";
        cin >> character2Name;
        for(int i = 0; i < allCharacters.size(); i++){//find the character, then the candies, then the candies in the candies file
            if(character2Name == allCharacters[i].name){
                for(int j = 0; j < allCharacters[i].candies.size(); j++){//k is needed
                    for(int k = 0; k < allCandies.size(); k++){
                        if(allCharacters[i].candies[j] == allCandies[k].name){
                            player2.addCandy(allCandies[k]);
                        }
                    }
                }
                character2Found = true;
            }

        }
    }
    cout << "Player 2 inventory is now \n";
    player2.printInventory();
    player2.populatePlayer(character2Name);

    cout << "\nDo you want to visit the candy store?\n";
    cin >> candyStore2Visit;
    while((candyStore2Visit != 'y' && candyStore2Visit != 'Y') && (candyStore2Visit != 'n' && candyStore2Visit != 'N')){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid option, try again\n";
        cin >> candyStore2Visit;
    }
    if(candyStore2Visit == 'y' || candyStore2Visit == 'Y'){
        cin.ignore(1000,'\n');
        Store startingStore2;
        startingStore2.populateStore(candyFileName, allCandies);
        startingStore2.displayCandies();
        getline(cin, startingStore2Choice);
        if(startingStore2Choice == startingStore2.findCandy(startingStore2Choice).name){
            startingCandy2Found = true;
            visitCandy2Store = player2.addCandy(startingStore2.findCandy(startingStore2Choice));
        }
        
        while(startingCandy2Found == false){
            cin.clear();
            cout << "Invalid input. Please try again\n";
            getline(cin, startingStore2Choice);
            if(startingStore2Choice == startingStore2.findCandy(startingStore2Choice).name){
                player2.addCandy(startingStore2.findCandy(startingStore2Choice));
                startingCandy2Found = true;
            }
        }
        cout << "Player 2 inventory is now\n";
        player2.printInventory();
        player2.setGold(player2.getGold() - player2.findCandy(startingStore2Choice).price);
        cout << endl;

    }


    //////////////////Actual Gameplay/////////////////////////////////////////////
    //////////////////Actual Gameplay/////////////////////////////////////////////
    //////////////////Actual Gameplay/////////////////////////////////////////////
    //////////////////Actual Gameplay/////////////////////////////////////////////
    //////////////////Actual Gameplay/////////////////////////////////////////////


    cout << "Let's begin the game. Here is the board:\n";
    game_board.displayBoard();
    int menu1Choice;
    int menu2Choice;
    int movePlayer1;
    int movePlayer2;
    int gummyTile = -1;
    bool p1Lose2Turns = false;
    bool p2Lose2Turns = false;
    bool storeFound = false;
    bool store2Found = false;
    bool store3Found = false;
    bool can1UseStore1 = true;
    bool can1UseStore2 = true;
    bool can1UseStore3 = true;
    bool can2UseStore1 = true;
    bool can2UseStore2 = true;
    bool can2UseStore3 = true;
    int turnMissed1 = 0;
    int turnMissed2 = 0;
    int specialTileResult;


    bool can2UseStore = true;
    string candyToUse;

    
    game_board.resetBoard();

    while(endOfGame == false){  
        
       
        if(can1UseStore1 == true && game_board.getPlayer1Position() == store1Pos){
            store1.populateStore(candyFileName, allCandies);
            visit1CandyStore(can1UseStore1,player1,store1);
            can1UseStore1 = false;
        }
        else if(can1UseStore2 == true && game_board.getPlayer1Position() == store2Pos){
            store2.populateStore(candyFileName, allCandies);
            visit1CandyStore(can1UseStore2,player1,store2);
            can1UseStore2 = false;
        }
        else if(can1UseStore3 == true && game_board.getPlayer1Position() == store3Pos){
            store3.populateStore(candyFileName, allCandies);
            visit1CandyStore(can1UseStore3,player1,store3);
            can1UseStore3 = false;
        }
         if(can2UseStore1 == true && game_board.getPlayer2Position() == store1Pos){
            store1.populateStore(candyFileName, allCandies);
            visit2CandyStore(can2UseStore1,player2,store1);
            can2UseStore1 = false;
        }
        else if(can2UseStore2 == true && game_board.getPlayer2Position() == store2Pos){
            store2.populateStore(candyFileName, allCandies);
            visit2CandyStore(can2UseStore2,player2,store2);
            can2UseStore2 = false;
        }
        else if(can2UseStore3 == true && game_board.getPlayer2Position() == store3Pos){
            store3.populateStore(candyFileName, allCandies);
            visit2CandyStore(can2UseStore3,player2,store3);
            can2UseStore3 = false;
        }
        // check if player has 0 stamina
        if(player1.getStamina() <= 0 || game_board.getPlayer1Position() == gummyTile){
            p1Lose2Turns = true;
        }
        if(player2.getStamina() <= 0 || game_board.getPlayer2Position() == gummyTile){
            p2Lose2Turns = true;
        }
        if(p1Lose2Turns == true){
            if(turnMissed1 == 2){
                hasTurn1 = true;
                p1Lose2Turns = false;
                player1.setStamina(20);
                turnMissed1 = 0;
                continue;
            }
            cout << player1Name << " has no stamina and must miss two turns to regain stamina\n";
            hasTurn1 = false;
            turnMissed1++; 
        }
        if(p2Lose2Turns == true){
           if(turnMissed2 == 2){
                hasTurn2 = true;
                p2Lose2Turns = false;
                player2.setStamina(20);
                turnMissed2 = 0;
                continue;
            }
            cout << player1Name << " has no stamina and must miss two turns to regain stamina\n";
            hasTurn1 = false;
            turnMissed1++; 
        }
        

        if(hasTurn1 == false){//checking if player has their turn, put before player 1
            cout << "It's " << player2Name << "'s turn\nPlease select a menu option\n";//begins menu choices
            cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
            cin >> menu2Choice;
            while(menu2Choice != 1 && menu2Choice != 2 && menu2Choice != 3){
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Invalid choice, try again\n";
                cin >> menu2Choice;
            }
        
            while(menu2Choice != 1){//only drawing a card ends the turn
                if(menu2Choice == 2){//need to make hidden treasure candies work
                    menu2Option(player2,player1,game_board,gummyTile,candyToUse, allRiddles);
                    cout << "It's " << player2Name << "'s turn\nPlease select a menu option\n";
                    cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
                    cin >> menu2Choice;
                    while(menu2Choice != 1 && menu2Choice != 2 && menu2Choice != 3){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Invalid choice, try again\n";
                        cin >> menu2Choice;
                    }
                }
                else if(menu2Choice == 3){
                    menu3Option(player2,player2Name,character2Name);
                    cout << "It's " << player2Name << "'s turn\nPlease select a menu option\n";
                    cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
                    cin >> menu2Choice;
                    while(menu2Choice != 1 && menu2Choice != 2 && menu2Choice != 3){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Invalid choice, try again\n";
                        cin >> menu2Choice;
                    }
                }
            }
            if(p1Lose2Turns == false){
                hasTurn1 = true;
            }
            else{
                hasTurn1 = false;
            }
        }
        
        if(hasTurn1 == true){
            cout << "It's " << player1Name << "'s turn\nPlease select a menu option\n";//begins menu choices
            cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
            cin >> menu1Choice;
            while(menu1Choice != 1 && menu1Choice != 2 && menu1Choice != 3){
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Invalid choice, try again\n";
                cin >> menu1Choice;
            }
        
            while(menu1Choice != 1){//only drawing a card ends the turn
                if(menu1Choice == 2){//need to make hidden treasure candies work
                    menu2Option(player1,player2,game_board,gummyTile,candyToUse, allRiddles);
                    cout << "It's " << player1Name << "'s turn\nPlease select a menu option\n";
                    cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
                    cin >> menu1Choice;
                    while(menu1Choice != 1 && menu1Choice != 2 && menu1Choice != 3){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Invalid choice, try again\n";
                        cin >> menu1Choice;
                    }
                }
                else if(menu1Choice == 3){
                    menu3Option(player1,player1Name,character1Name);
                    cout << "It's " << player1Name << "'s turn\nPlease select a menu option\n";
                    cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
                    cin >> menu1Choice;
                    while(menu1Choice != 1 && menu1Choice != 2 && menu1Choice != 3){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Invalid choice, try again\n";
                        cin >> menu1Choice;
                    }
                }
            }
            
            if(menu1Choice == 1){
                menu1Option1(player1,player2,player1Name,player2Name,character1Name,game_board,hasTurn1,allRiddles,gummyTile,candyToUse);
            }
        }

        //////////then do player 2//////////
        //////////then do player 2//////////
        //////////then do player 2//////////
        //////////then do player 2//////////
        //////////then do player 2//////////
        //////////then do player 2//////////
        //////////then do player 2//////////

        
         if(hasTurn2 == false){//checking if player has their turn, put before player 2
            cout << "It's " << player1Name << "'s turn\nPlease select a menu option\n";//begins menu choices
            cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
            cin >> menu1Choice;
            while(menu1Choice != 1 && menu1Choice != 2 && menu1Choice != 3){
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Invalid choice, try again\n";
                cin >> menu1Choice;
            }
        
            while(menu1Choice != 1){//only drawing a card ends the turn
                if(menu1Choice == 2){//need to make hidden treasure candies work
                    menu2Option(player1,player2,game_board,gummyTile,candyToUse, allRiddles);
                    cout << "It's " << player1Name << "'s turn\nPlease select a menu option\n";
                    cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
                    cin >> menu1Choice;
                    while(menu1Choice != 1 && menu1Choice != 2 && menu1Choice != 3){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Invalid choice, try again\n";
                        cin >> menu1Choice;
                    }
                }
                else if(menu1Choice == 3){
                    menu3Option(player1,player1Name,character1Name);
                    cout << "It's " << player1Name << "'s turn\nPlease select a menu option\n";
                    cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
                    cin >> menu1Choice;
                    while(menu1Choice != 1 && menu1Choice != 2 && menu1Choice != 3){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Invalid choice, try again\n";
                        cin >> menu1Choice;
                    }
                }
            }
            if(p2Lose2Turns == false){
                hasTurn2 = true;
            }
            else{
                hasTurn2 = false;
            }
        }
        
        if(hasTurn2 == true){
            cout << "It's " << player2Name << "'s turn\nPlease select a menu option\n";//begins menu choices
            cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
            cin >> menu2Choice;
            while(menu2Choice != 1 && menu2Choice != 2 && menu2Choice != 3){
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Invalid choice, try again\n";
                cin >> menu2Choice;
            }
        
            while(menu2Choice != 1){//only drawing a card ends the turn
                if(menu2Choice == 2){//need to make hidden treasure candies work
                    menu2Option(player2,player1,game_board,gummyTile,candyToUse, allRiddles);
                    cout << "It's " << player2Name << "'s turn\nPlease select a menu option\n";
                    cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
                    cin >> menu2Choice;
                    while(menu2Choice != 1 && menu2Choice != 2 && menu2Choice != 3){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Invalid choice, try again\n";
                        cin >> menu2Choice;
                    }
                }
                else if(menu2Choice == 3){
                    menu3Option(player2,player2Name,character2Name);
                    cout << "It's " << player2Name << "'s turn\nPlease select a menu option\n";
                    cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
                    cin >> menu2Choice;
                    while(menu2Choice != 1 && menu2Choice != 2 && menu2Choice != 3){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Invalid choice, try again\n";
                        cin >> menu2Choice;
                    }
                }
            }
            if(menu2Choice == 1){
                menu2Option1(player2,player1,player2Name,player1Name, character2Name, game_board,hasTurn2,allRiddles, gummyTile, candyToUse);
            }
        }
        
    
    }
}
    /*
    ---------------------------------
    Same tile constraints

    if two players have some pos, first player on there can rob second of 5-30 coins
    UNLESS second player has Robber's Repel, which blocks the robbery and send the first player back one
    -------------------------------------


    ------------------------
    the end
    congradulate the player who won and print their stats
    Name of the player and their character
    Amount of Gold Left
    Stamina Left
    Candies in the player’s possession

    fout to the results.txt file, ill choose how to format it
    ------------------------------


    make sure to close every file
    
    */
