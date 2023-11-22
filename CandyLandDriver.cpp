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
    /*void displayCharacter(vector<Character> characters){
        for(int i = 0; i < characters.size(); i++){
            cout << "Name: " << characters[i].name << endl;
            cout << "Stamina: " << characters[i].stamina << endl;
            cout << "Gold: " << characters[i].gold << endl;
            cout << "Candies:\n";
            for(int j = 0; j < characters[i].candies[j].size(); i++){
                cout << "[" << characters[i].candies[j] << "]";
                if(j == 2 || j == 5){
                    cout << endl;
                }
            }

        }
    }*/
};

/*
what questions for reciation this week:
how much does stamina deplete and increase by each turn

In the first 27 tiles, a candy store will be on a magenta-colored tile. 
Between tiles 28 and 54, a candy store will appear on a green-colored tile. 
And from tile 55 to 82, a candy store will be on a blue tile.
*/

/*
steps: push after each step
1. make board - done
2. make store class - done
3. make player class
4. make card drawing function
5. define data members, getters and setters
6. create necessary functions
7. populate necessary functions
8. 
9. 
10.  
*/





/*
things to do: 
vector of possible characters
make characters, sour saul, haribo heisenburg, chocolate charlie, toffee todd
game class that keeps track of players, characters, properties, etc

player class, neccessary member is an array of candies
candy array has max size of nine, if player has nine, they have to substitue a candy



fout to a finsihed stats file called results.txt    
*/



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
                        //just the candy name in file, gotta find name from allcandies then add it?
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




void Calamities(Player player){
    srand((unsigned) time(NULL));
    char bandits;
    char labyrinth;
    char avalanche;
    bool trap = false;
    bool rpsStatus;
    int random = rand() % 100 + 1;
    if(random >=1 && random <=12){
        cout << "candy bandits! do you wanna play rock paper scissors to see if you actually lose or not?\n";
        cin >> bandits;
        while((bandits != 'y' && bandits != 'Y') && (bandits != 'n' && bandits != 'N')){
        cin.clear();
        cout << "Invalid option, try again\n";
        cin >> bandits;
        
    }
    if(bandits == 'y' || bandits == 'Y'){
            rpsStatus = player.playRockPaperScissors();
            if(rpsStatus == true){
                cout << "Congrats on winning, you dodged those bandits, king\n";
            }
            else{
                cout << "Because you lost against them in rps, they just kicked you harder\n";
            }
        }
        else if(bandits == 'n' || bandits == 'N'){
            cout << "take the L\n";
        }
    
    }
    else if(random >12 && random <= 26){
            cout << "labyrinth! do you wanna play rock paper scissors to see if you actually lose or not?\n";
            cin >> labyrinth;
            while((labyrinth != 'y' && labyrinth != 'Y') && (labyrinth != 'n' && labyrinth != 'N')){
            cin.clear();
            cout << "Invalid option, try again\n";
            cin >> labyrinth;
            
        }
        if(labyrinth == 'y' || labyrinth == 'Y'){
                rpsStatus = player.playRockPaperScissors();
                if(rpsStatus == true){
                    cout << "you made it out the labyrinth\n";
                } else{
                    cout << "you got lost and basically died\n";
                }
            }
            else if(labyrinth == 'n' || labyrinth == 'N'){
                cout << "take the L\n";
            }
    }
    else if(random >26 && random <= 32){
            cout << "avalanche! do you wanna play rock paper scissors to see if you actually lose or not?\n";
            cin >> avalanche;
            while((avalanche != 'y' && avalanche != 'Y') && (avalanche != 'n' && avalanche != 'N')){
            cin.clear();
            cout << "Invalid option, try again\n";
            cin >> avalanche;
            
        }
        if(avalanche == 'y' || avalanche == 'Y'){
                rpsStatus = player.playRockPaperScissors();
                if(rpsStatus == true){
                    cout << "you surfed the avalanche down the hill\n";
                }
                else{
                    cout << "you got buried for a bit\n";
                }
            }
            else if(avalanche == 'n' || avalanche == 'N'){
                cout << "take the L\n";
            }
    }
    else if(random >32 && random <= 40){
        cout << "candy trap! do you wanna have a magical candy?\n";
        //check for the candy with .find
        if(trap == false){
            cout << "tough luck loser\n";
        }
        else{
            cout << "hey nice job\n";
        }
    }
    else{
        cout << "normal\n";
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



int main(){
    srand((unsigned) time(NULL));
    Board game_board;
    Player player1;
    Player player2;
    string candyFileName = "candy.txt";
    string characterFileName = "characters.txt";
    vector<Candy> allCandies;
    vector<Character> allCharacters;
    allCandies = readCandy(candyFileName, allCandies);
    allCharacters = readCharacter(characterFileName, allCharacters);
    bool rpsStatus;

    //actual main:
    bool endOfGame = false;
    int numParticipants;
    string player1Name;
    string player2Name;
    string character1Name;
    string character2Name;
    char candyStore1Visit;
    char candyStore2Visit;
    bool character1Found = false;
    bool character2Found = false;

    string startingStore1Choice;
    string startingStore2Choice;

    bool startingCandy1Found = false;
    bool startingCandy2Found = false;

    bool visitCandy1Store = false;
    bool visitCandy2Store = false;



    cout << "Welcome to the game of Candyland. Please enter the number of participants\n";
    cin >> numParticipants;
    while(numParticipants != 2){//this works
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Please choose 2 participants\n";
        cin >> numParticipants;
    }
    
    cout << "Enter player name:\n";
    cin >> player1Name;
    cout << "Awesome! Here is a list of characters a player can select from\n";
    displayCharacters(allCharacters);
    cout << "The selected character is\n";
    cin >> character1Name;
    
    for(int i = 0; i < allCharacters.size(); i++){//gotta find the character, then the candies, then the candies in the candies file
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
        for(int i = 0; i < allCharacters.size(); i++){//gotta find the character, then the candies, then the candies in the candies file
            if(character1Name == allCharacters[i].name){
                for(int j = 0; j < allCharacters[i].candies.size(); j++){//k is needed
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

    // everything works up to here
    
    
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
            cin.ignore(1000,'\n');
            cout << "Invalid input. Please try again\n";
            getline(cin, startingStore1Choice);
            for(int i = 0; i < 4; i++){
                if(startingStore1Choice == startingStore1.findCandy(startingStore1Choice).name){
                    player1.addCandy(startingStore1.findCandy(startingStore1Choice));
                    startingCandy1Found = true;
                }
            } 
        }
    }
    player1.printInventory();

    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////
    //////////////////////////////////Player 2 land///////////////////////////////////



    cout << "\nEnter player name:\n";
    cin >> player2Name;
    cout << "Awesome! Here is a list of characters a player can select from\n";
    displayCharacters(allCharacters);
    cout << "The selected character is\n";
    cin >> character2Name;
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

    // everything works up to here
    
    //player2
    
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
            cin.ignore(1000,'\n');
            cout << "Invalid input. Please try again\n";
            getline(cin, startingStore2Choice);
            for(int i = 0; i < 4; i++){
                if(startingStore2Choice == startingStore2.findCandy(startingStore2Choice).name){
                    player2.addCandy(startingStore2.findCandy(startingStore2Choice));
                    startingCandy2Found = true;
                }
            } 
        }
    }
    player2.printInventory();

    while(game_board.getPlayer1Position() < 83 && game_board.getPlayer2Position() < 83)

    while(endOfGame == false){  










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