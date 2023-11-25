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

vector<Candy> readCandy(string file_name, vector<Candy> candies){ //add extra candy members
    cout << fixed << setprecision(2);
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
            candies.push_back(current_candy);
            }
        }
    }
    candyFile.close();
    return candies;
}

vector<Character> readCharacter(string fileName, vector<Character> characters){
    ifstream characterFile;
    characterFile.open(fileName);
    if(characterFile.fail()){
        cout << "Failed to open text file\n";
        return characters;
    }
    else{
        //character name ,stamina, gold,candies
        string name = "";
        string stamina = "";
        int actualStamina = 0;
        string gold = "";
        int actualGold = 0;
        string candyLine;
        string line;
        getline(characterFile, line);
        while(getline(characterFile, line)){
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
                    while(getline(candySS, line, ',')){
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

    //     while(getline(riddleFile, line)){
    //         stringstream ss(line);
    //         int iterator = 0;
    //         Riddle current_riddle;
    //         if(line.size() != 0){
    //         while(getline(ss, line, '|')){
    //             if(iterator == 0){
    //                 iterator ++;
    //                 current_riddle.question = line;
    //                 // question = line;
    //             } else if(iterator == 1){
    //                 // answer = line;
    //                 current_riddle.question = line;
    //         }
    //         // current_riddle.question = question;
    //         // current_riddle.answer = answer;
    //         riddles.push_back(current_riddle);
    //         }
    //     }
    // }
        while(getline(riddleFile, line)){//this works i guess
        stringstream ss(line);
        string question;
        string answer;
        if(getline(ss, question, '|') && getline(ss, answer)){
            Riddle current_riddle;
            current_riddle.question = question;
            current_riddle.answer = answer;
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
                player.printInventory();
                string freeingCandy;
                bool removedCandy;
                cin.ignore(1000,'\n');
                cout << "\nSelect the magical candy from your inventory to free yourself\n";
                getline(cin, freeingCandy);
                while(player.findCandy(freeingCandy).candy_type != "magical"){
                    cin.clear();
                    cout << "Please choose a magical candy type\n";
                    getline(cin, freeingCandy);
                }
                removedCandy = player.removeCandy(freeingCandy);


                cout << "removedCandy result is " << removedCandy << endl;

                cout << "You have used " << freeingCandy << " to free yourself!\n";

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

int specialTiles(Player &player){
    int randomTile = rand() % 100 + 1;
    if(randomTile ==96){
        cout << "You landed on a Shortcut Tile! You've been given the golden opportunity to leap ahead four tiles!\n";
        return 1;
    }
    else if(randomTile == 97){
        cout << "You landed on an Ice Cream Shop Tile! You've been given an additional turn!\n";
        return 2;
    }
    else if(randomTile == 98){
        int goldLost = rand() % 5 + 10;
        cout << "Uh oh, a Gumdrop Forest Tile! You have lost " << goldLost << " gold, and were moved back 4 tiles\n";
        return 3;
    }
    else if(randomTile == 99){
        cout << "You've landed on a Gingerbread House Tile! You've been moved back to your previous position, and you've lost an immunity candy!\n";
        return 4;
    }
    return 0;
}

bool answerRiddle(vector<Riddle> riddles){
    cin.ignore(1000,'\n');
    const int riddleRandom = rand() % riddles.size();
    int riddleIndex = riddleRandom;
    string riddleToSolve = riddles[riddleIndex].question;
    string riddleAnswer;
    cout << "To earn the hidden treasure, you must answer this riddle\n";
    cout << riddles[riddleIndex].question;
    cout << endl;
    getline(cin, riddleAnswer);
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

void hiddenTreasures(Player &player,vector<Riddle> riddles){
    cout << "You have discovered a hidden treasure! ";
    bool riddleSolved = answerRiddle(riddles); //getting the treasure is determined by the answerRiddle function
    cout << "Riddle solved value is " << riddleSolved << endl;
    int treasureType = rand() % 100 + 1;
    if(riddleSolved == true){
        if(treasureType > 0 && treasureType <= 30){
            int staminaRefill = rand() % 20 + 10;
            cout << "You found a hidden treasure! Your stamina has been replenished by " << staminaRefill << " units!\n";
            player.setStamina(player.getStamina() + staminaRefill);
        }
        else if(treasureType > 30 && treasureType <= 40){
            int goldGain = rand() % 20 + 20;
            cout << "You found a hidden treasure! You have found " << goldGain << " gold!\n";
            player.setGold(player.getGold() + goldGain);
            if(player.getGold() > 100){
                player.setGold(100);
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
                Candy vigorBean = {"Jellybean of Vigor","","stamina",50,"stamina",0};
                cout << "You found the Jellybean of Vigor! Using it boosts stamina by 50 points!\n";
                player.addCandy(vigorBean);
                cout << "Player inventory is now \n";
                player.printInventory();
                cout << endl;
            }
            else{
                Candy treasureTruffle = {"Treasure Hunter's Truffle","allows the player to unlock a hidden treasure","",0,"",0};
                cout << "You found the Treasure Hunter's Truffle! If you use it, you have the ability to solve a riddle for another hidden treasure!\n";
                player.addCandy(treasureTruffle);
                cout << "Player inventory is now \n";
                player.printInventory();
                cout << endl;
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
        cout << characters[i].name << " " << endl;
        cout <<characters[i].stamina << " " << endl;
        cout <<characters[i].gold << " " << endl;
        for(int j = 0; j < characters[i].candies.size(); j++){
            cout << "[" << characters[i].candies[j] << "]   ";
            if(j > 0 && j % 3 == 2){
                cout << endl;
            }
        }
        
        cout << "------------------------------------------\n";
    }
}


void visitCandyStore(bool canVisitStatus, Player &player, Store &store){
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
            cout << "Player 1 inventory is now\n";
            player.printInventory();
            player.setGold(player.getGold() - player.findCandy(storeChoice).price);
            cout << endl;
        }


    }
}



int main(){
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

    ////////////////Creation of stores in the game//////////////////////
    Store store1;//create the stores here, populate and display them later
    Store store2;
    Store store3;
    int store1Pos = rand() % 27 + 1;
    if(store1Pos % 3 == 1){
        store1Pos -= 1;
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
    /////////////////////////////////////////////////////////////////////

    cout << "Welcome to the game of Candyland. Please enter the number of participants\n";
    // cin >> numParticipants;
    numParticipants = 2;
    while(numParticipants != 2){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Please choose 2 participants\n";
        cin >> numParticipants;
    }
    
    cout << "Enter Player 1 name:\n";
    // cin >> player1Name;
    player1Name = "Aleqz";
    cout << "Awesome! Here is a list of characters a player can select from\n";
    displayCharacters(allCharacters);
    cout << "The selected character is\n";
    // cin >> character1Name;
    character1Name = "Sour_Saul";
    
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

    cout << "\nDo you want to visit the candy store?\n";
    // cin >> candyStore1Visit;
    candyStore1Visit = 'n';
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
    }
        cout << "Player 1 inventory is now\n";
        player1.printInventory();
        player1.setGold(player1.getGold() - player1.findCandy(startingStore1Choice).price);
        cout << endl;
        

    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////



    cout << "Enter Player 2 name:\n";
    // cin >> player2Name;
    player2Name = "Sam";
    cout << "Awesome! Here is a list of characters a player can select from\n";
    displayCharacters(allCharacters);
    cout << "The selected character is\n";
    // cin >> character2Name;
    character2Name = "Honey_Harold";
    while(character1Name == character2Name){
        cout << "Cannot be the same character as " << player1Name << ". Please choose a different character\n";
        cin >> character2Name;
    }
    
    for(int i = 0; i < allCharacters.size(); i++){//gotta find the character, then the candies, then the candies in the candies file
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
        for(int i = 0; i < allCharacters.size(); i++){//gotta find the character, then the candies, then the candies in the candies file
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
    // cin >> candyStore2Visit;
    candyStore2Visit = 'n';
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


    int hiddenTreasure1 = rand() % 27 + 1;//make the hidden treasure locations
    int hiddenTreasure2 = rand() % 27 + 28;
    int hiddenTreasure3 = rand() % 27 + 55;
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


    bool can2UseStore = true;
    string candyToUse;

    
    game_board.resetBoard();
    cout << hiddenTreasure1 << " "<< hiddenTreasure2 << " " << hiddenTreasure3 << endl;

    while(endOfGame == false){  
        int test;
        game_board.movePlayer1(1);
        if(game_board.getPlayer1Position() == hiddenTreasure1 || game_board.getPlayer1Position() == hiddenTreasure2 || game_board.getPlayer1Position() == hiddenTreasure3)
        hiddenTreasures(player1,allRiddles);
        cin >> test;
        
        
       
        /*if(can1UseStore1 == true && game_board.getPlayer1Position() == store1Pos){
            store1.populateStore(candyFileName, allCandies);
            visitCandyStore(can1UseStore1,player1,store1);
            can1UseStore1 = false;
        }
        else if(can1UseStore2 == true && game_board.getPlayer1Position() == store2Pos){
            store2.populateStore(candyFileName, allCandies);
            visitCandyStore(can1UseStore2,player1,store2);
            can1UseStore2 = false;
        }
        else if(can1UseStore3 == true && game_board.getPlayer1Position() == store3Pos){
            store3.populateStore(candyFileName, allCandies);
            visitCandyStore(can1UseStore3,player1,store3);
            can1UseStore3 = false;
        }


         if(can2UseStore1 == true && game_board.getPlayer2Position() == store1Pos){
            store1.populateStore(candyFileName, allCandies);
            visitCandyStore(can2UseStore1,player2,store1);
            can2UseStore1 = false;
        }
        else if(can2UseStore2 == true && game_board.getPlayer2Position() == store2Pos){
            store2.populateStore(candyFileName, allCandies);
            visitCandyStore(can2UseStore2,player2,store2);
            can2UseStore2 = false;
        }
        else if(can2UseStore3 == true && game_board.getPlayer2Position() == store3Pos){
            store3.populateStore(candyFileName, allCandies);
            visitCandyStore(can2UseStore3,player2,store3);
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
            int turnMissed = 0;
            cout << player1Name << " has no stamina and must miss two turns to regain stamina\n";
            hasTurn1 = false;
            turnMissed++;
            if(turnMissed == 2){
                hasTurn1 = true;
            }
        }
        if(p2Lose2Turns == true){
            int turnMissed = 0;
            cout << player2Name << " has no stamina and must miss two turns to regain stamina\n";
            hasTurn2 = false;
            turnMissed++;
            if(turnMissed == 2){
                hasTurn2 = true;
            }
        }
        

        if(hasTurn1 == false){//checking if player has their turn, put before player 1
            cout << player1Name << " has lost their turn, it is now " << player2Name << "'s turn\n";
            cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
            cin >> menu2Choice;
            hasTurn1 = true;
        }
        
        cout << "It's " << player1Name << "'s turn\nPlease select a menu option\n";
        cout << "1.  Draw a card\n2.  Use candy\n3.  Show player stats\n";
        cin >> menu1Choice;
        while(menu1Choice != 1 && menu1Choice != 2 && menu1Choice != 3){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid choice, try again\n";
            cin >> menu1Choice;
        }
        if(menu1Choice == 1){
            movePlayer1 = determineMoveAmount(game_board.getPlayer1Position(), player1.drawCard());
            game_board.movePlayer1(movePlayer1);
            game_board.displayBoard();
            player1.setStamina(player1.getStamina() - 1);
            hasTurn1 = Calamities(player1);
            hiddenTreasures(player1, game_board.getPlayer1Position(), allRiddles);
        }
        else if(menu1Choice == 2){//need to do conditionals depending on players candy type
            bool candyFound = false;
            cin.ignore(1000,'\n');
            cout << "Here is a list of your candies:\n";
            player1.printInventory();
            cout << "\nEnter a candy you wish to use\n";
            getline(cin, candyToUse);
            if(candyToUse == player1.findCandy(candyToUse).name){
                candyFound = true;
            }
            while(candyFound == false){
                cin.clear();
                cout << "Not a valid candy in your inventory. Please try again\n";
                getline(cin, candyToUse);
                if(candyToUse == player1.findCandy(candyToUse).name){
                    candyFound = true;
                }
            }
            if(player1.findCandy(candyToUse).candy_type == "magical"){
                cout << "You have used " << candyToUse << ". Your stamina is increased by " << player1.findCandy(candyToUse).effect_value << " points.\n";
                player1.setStamina(player1.getStamina() + player1.findCandy(candyToUse).effect_value);
                player1.removeCandy(candyToUse);
                
                // if(player1.getStamina() > 100){ not sure if this is needed, instructions are unclear
                //     player1.setStamina(100);
                // }
            }
            else if(player1.findCandy(candyToUse).candy_type == "poison"){
                char useCandy;
                cout << "Do you want to use " << candyToUse << " against your opponent?\n";
                cin >> useCandy;
                if(useCandy == 'y' || useCandy == 'y'){
                    if(player2.hasImmunityCandy()){
                        cout << "You have used " << candyToUse << " but your opponent has " << player2.findImmunityCandy().name << " to protect against your poison candy\n";
                        player1.removeCandy(candyToUse);
                        player2.removeCandy(player2.findImmunityCandy().name);
                    }
                    else{
                        cout << "You have used " << candyToUse << " and your opponent has lost " << player1.findCandy(candyToUse).effect_value << " points.\n";
                        player1.removeCandy(candyToUse);
                        player2.setStamina(player2.getStamina() - player1.findCandy(candyToUse).effect_value);
                    }
                }
            }
            else if(player1.findCandy(candyToUse).candy_type == "gummy"){
                cout << "Which tile do you want to place " << candyToUse << " - gummy candy?\n";
                cin >> gummyTile;
                while(gummyTile < 0 || gummyTile > 83){
                    cin.clear();
                    cout << "Invalid input. Please try again\n";
                    cin >> gummyTile;
                }
                cout << "You have successfully placed a gummy candy on tile " << gummyTile << ". Any player that lands on the gummy tile will be obstructed from advancing past the tile for two moves.\n";
                player1.removeCandy(candyToUse);
            }
            else if(player1.findCandy(candyToUse).candy_type == "immunity"){
                cout << "Immunity candies are used when they need to be, so you don't need to use them here\n";
            }
        }
        else if(menu1Choice == 3){
            cout << "Here are your stats:\n";
            cout << "Player name: " << player1Name << endl;
            cout << "Character: " << character1Name << endl;
            cout << "Stamina: " << player1.getStamina() << endl;
            cout << "Gold: " << player1.getGold() << endl;
        }


        //////////then do player 2//////////
        //////////then do player 2//////////
        //////////then do player 2//////////

    */

    // cout << game_board.getPlayer1Position() << " " << game_board.getPlayer2Position() << endl;
        if(game_board.getPlayer1Position() >= 83 || game_board.getPlayer2Position() >= 83){
            endOfGame = true;
        }

    }


    

    /*

    once both players have chosen their characters, its time to start the game

    while(endOfGame == false){
        say its current player's turn, ask to draw card, use candy, or show player stats
        if draw card
            board.drawcard, cout card color, show updated position board.display
        if use candy
            display current player's candies, ask which one to use, update stats with setters
        if show stats
            display player stats (stamina, gold, and candy)
        else
            invalid
        
        ------------------------------------------------------------------
        calamities
        40% change for a calamity to occur, out of those 40%
        30% candy bandits - lose between 1-10 gold
        35% lost in labyrinth - lose turn unless win rps, then gain turn back, bool hasTurn
        15% avalanche - lose 5-10 stamina, unless win rps, then fine, bool hasTurn
        20% taffy trap - lose next turn, unless magical candy in inventory, bool hasTurn
        ------------------------------------------------------------------

        ---------------------------------------
        candy store
        use boarddriver stuff, add three candies to the players inventory
        display store
        set candies appropriately
        -------------------------------ne

        if(player is at tile 83){
            endOfGame = true;
        }
    }


        ---------------------------------------------------------------------
        Special tiles

        Shortcut tile - move up four tiles, unless close enough to beat game, then beat game, ez conditional

        Ice cream shop tile - draw another card. if ice cream, draw card

        Gumdrop forest tile - go back for tiles, lose between 5-10 gold, if less than 4 from start, reset player pos

        gingerbread house tile - get booted to last position, lose an immunity candy, need candy remove function
        ------------------------------------------------------------------------

        ---------------------------------
        Same tile constraints

        if two players have some pos, first player on there can rob second of 5-30 coins
        UNLESS second player has Robber's Repel, which blocks the robbery and send the first player back one
        -------------------------------------


        ------------------------------------
        hidden treasures

        three hidden treasures randomly across the map

        30% for stamina refill: recover 10-30 units of stamina, capped at 100 if player stamina > 70, now its 100

        10% for gold windfall: gain 20-40 gold, capped at 100. ez conditionals 

        30% for robber's repel: is a candy, blocks another player from robbing. does it take inventory space?

        30% for candy aquisition: two parter 

            70% for Jellybean of Vigor: restore 50 units of stamina, capped at 100

            30% for Treasure Hunter's Truffle: you can unlock a hidden treasure by solving a riddle, same as others

        ---------------------------------------------


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
}