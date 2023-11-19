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
        vector<string> candyNames;
        string line;
        string candyLine;
        getline(characterFile, line);
        while(getline(characterFile, line)){
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
                    iterator++;
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
            for(int i = 0; i < candyNames.size(); i++){//runs once then breaks
                current_character.candies.push_back(candyNames[i]);
            }
            characters.push_back(current_character);
            }
        }
    }
    characterFile.close();
    return characters;

}



void playRockPaperScissors(Player players[]){ //change to one player
    string player1bet;
    string player2bet;
    string lowerP1B;
    string lowerP2B;
    string lowerFind;
    bool betStatus = false;
    char p1c;
    char p2c;
   
    for(int i = 0; i < 2; i++){
        if(players[i].getCandyAmount() == 0 || players[i].getCandyAmount() == 9){
            cout << "Not enough candy!\n";
            return;
        }
    }
    cout << "Player 1 Inventory\n";
    players[0].printInventory();
    cout << "Player 1: Select candy to bet\n";
    getline(cin, player1bet);
    lowerP1B = player1bet;
    while(player1bet.length() == 0){ //makes sure it isnt empty
            cin.clear();
            cout << "Invalid Selection!" << endl;
            cin.clear();
            getline(cin, player1bet);
    }
    for(int i = 0; i < player1bet.length(); i++){ //makes everything lowercase
        lowerP1B[i] = tolower(player1bet[i]);
    }
    lowerFind = lowerP1B;
    for(int i = 0; i < players[0].findCandy(lowerP1B).name.length(); i++) {
        lowerFind[i] = tolower(players[0].findCandy(lowerP1B).name[i]);
    }
    if(lowerFind == lowerP1B){ //if name is found, proceed
        betStatus = true;
    }
    while(betStatus == false){
        cout << "Invalid Selection!\n"; //this is the problem
        cin.clear();
        getline(cin, player1bet);
        while(player1bet.length() == 0){ //makes sure it isnt empty
            cin.clear();
            cout << "Invalid Selection!" << endl;
            cin.clear();
            getline(cin, player1bet);
        }
        lowerP1B = player1bet;
        for(int i = 0; i < player1bet.length(); i++){ //makes everything lowercase
        lowerP1B[i] = tolower(player1bet[i]);
        }
        if(players[0].findCandy(lowerP1B).name == lowerP1B){
            betStatus = true;
        }
        else{
            betStatus = false;
        }
    }
    cout << "Player 2 Inventory\n";
    players[1].printInventory();
    cout << "Player 2: Select candy to bet\n";
    getline(cin, player2bet);
    lowerP2B = player2bet;
    while(player2bet.length() == 0){ //makes sure it isnt empty
            cin.clear();
            cout << "Invalid Selection!" << endl;
            cin.clear();
            getline(cin, player2bet);
    }
    for(int i = 0; i < player2bet.length(); i++){ //makes everything lowercase
        lowerP2B[i] = tolower(player2bet[i]);
    }
    lowerFind = lowerP2B;
    for(int i = 0; i < players[1].findCandy(lowerP2B).name.length(); i++) {
        lowerFind[i] = tolower(players[1].findCandy(lowerP2B).name[i]);
    }
    if(lowerFind == lowerP2B){ //if name is found, proceed
        betStatus = true;
    }
    while(betStatus == false){
        cout << "Invalid Selection!\n"; //this is the problem
        cin.clear();
        getline(cin, player2bet);
        while(player2bet.length() == 0){ //makes sure it isnt empty
            cin.clear();
            cout << "Invalid Selection!" << endl;
            cin.clear();
            getline(cin, player2bet);
        }
        lowerP2B = player2bet;
        for(int i = 0; i < player2bet.length(); i++){ //makes everything lowercase
        lowerP2B[i] = tolower(player2bet[i]);
        }
        if(players[1].findCandy(lowerP2B).name == lowerP2B){
            betStatus = true;
        }
        else{
            betStatus = false;
        }
    }
    cout << "Player 1: Enter r, p, or s\n";
    cin >> p1c;
    while(p1c != 'r' && p1c != 'p' && p1c != 's'){
        cout << "Invalid selection!\n";
        cin >> p1c;
    }
    cout << "Player 2: Enter r, p, or s\n";
    cin >> p2c;
    while(p2c != 'r' && p2c != 'p' && p2c != 's'){
        cout << "Invalid selection!\n";
        cin >> p2c;
    }
   
    while(p1c == p2c){
        cout << "Tie! Play again\n";
        cout << "Player 1: Enter r, p, or s\n";
        cin >> p1c;
        cout << "Player 2: Enter r, p, or s\n";
        cin >> p2c;
    }
    if((p1c == 'r' && p2c == 's') || (p1c == 'p' && p2c == 'r') || (p1c == 's' && p2c == 'p')){
        cout << "Player 1 has won " << player2bet << " from player 2!\n";
        Candy addedCandy = players[1].findCandy(lowerP2B);
        players[0].addCandy(addedCandy);
        players[1].removeCandy(player2bet);
        return;
    }
    else if((p2c == 'r' && p1c == 's') || (p2c == 'p' && p1c == 'r') || (p2c == 's' && p1c == 'p')){
        cout << "Player 2 has won " << player1bet << " from player 1!\n";
        Candy addedCandy = players[0].findCandy(lowerP1B);
        players[1].addCandy(addedCandy);
        players[0].removeCandy(lowerP1B);
        return;
    }

}


void Calamities(){
    srand((unsigned) time(NULL));
    char bandits;
    char labyrinth;
    char avalanche;
    bool trap = false;
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
            cout << "play rock paper scissors here\n";
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
                cout << "play rock paper scissors here\n";
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
                cout << "play rock paper scissors here\n";
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
    //////Drawing cards test/////////// it works
    int cardResult = player1.drawCard();
    int playerPos = game_board.getPlayer1Position();
    int moveAmount = determineMoveAmount(playerPos, cardResult);
    game_board.movePlayer1(moveAmount);
    // game_board.displayBoard();
    cout << game_board.getPlayer1Position();
    
    // Calamities();
    //start by opening every file needed and declaring all necessary variables
    //loading candy and character files
    //readCandy() and readCharacters()
    /*
    actual main:
    bool endOfGame = false;
    int numParticipants;
    string player1name;
    string player2name;
    char candyStore1Visit;
    cout << "Welcome to the game of Candyland. Please enter the number of participants\n";
    cin >> numParticipants;
    while(numParticipants != 2){
        cin.clear();
        cout << "Please choose 2 participants\n";
        cin >> numParticipants;
    }
    
    cout << "Enter player name:\n";
    cin >> player1Name;
    cout << "Awesome! Here is a list of characters a player can select from\n";
    for(int i = 0; i < 4; i++){
        player[i].displayInventory();
    }
    cout << endl << "The selected character is\n";
    cin >> player1name;
    while(player1name != FOUND IN CHARACTER FILE){
        cin.clear();
        cout << "Not a valid character, try again\n";
        cin >> player1name;
    }
    cout << "Do you want to visit the candy store?\n";
    cin >> candyStore1Visit;
    while((candyStore1Visit != 'y' || candyStore1Visit != 'Y') && (candyStore1Visit != 'n' || candyStore1Visit != 'N')){
        cin.clear();
        cout << "Invalid option, try again\n";
        cin >> candyStore1Visit;
    }
    if(candyStore1Visit == 'y' || candyStore1Visit == 'Y'){
        display candy store
    }

    --------------------------------------
    ***do the same thing for player two***
    --------------------------------------

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
        -------------------------------

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