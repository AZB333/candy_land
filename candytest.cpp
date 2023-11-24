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



bool Calamities(Player &player){//need to do setters
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
                    //setter
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
    Board game_board; //game prep variables
    Player player1;
    Player player2;
    string candyFileName = "candy.txt";
    string characterFileName = "characters.txt";
    vector<Candy> allCandies;
    vector<Character> allCharacters;
    allCandies = readCandy(candyFileName, allCandies);
    allCharacters = readCharacter(characterFileName, allCharacters);
    bool rpsStatus;
    bool endOfGame = false;
    bool hasTurn1;
    bool hasTurn2;


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
        cout << "Player 1 inventory is now\n";
        player1.printInventory();
        while(startingCandy1Found == false){
            cin.clear();
            cout << "Invalid input. Please try again\n";
            getline(cin, startingStore1Choice);
            if(startingStore1Choice == startingStore1.findCandy(startingStore1Choice).name){
                player1.addCandy(startingStore1.findCandy(startingStore1Choice));
                startingCandy1Found = true;
            }
            cout << "Player 1 inventory is now\n";
            player1.printInventory();
        }
    }

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
    player1.populatePlayer(character2Name);

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
        cout << "Player 2 inventory is now\n";
        player2.printInventory();

        while(startingCandy2Found == false){
            cin.clear();
            cout << "Invalid input. Please try again\n";
            getline(cin, startingStore2Choice);
            if(startingStore2Choice == startingStore2.findCandy(startingStore2Choice).name){
                player2.addCandy(startingStore2.findCandy(startingStore2Choice));
                startingCandy2Found = true;
            }
            cout << "Player 2 inventory is now\n";
            player2.printInventory();
        }
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
    string candyToUse;
    game_board.resetBoard();
    hasTurn1 = true;
    hasTurn2 = true;
    while(endOfGame == false){  //make sure players lose their turn or not
        if(hasTurn1 == false){
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
        if(menu1Choice == 1){//add check for stores, add calamities(fix calamities first)
            movePlayer1 = determineMoveAmount(game_board.getPlayer1Position(), player1.drawCard());
            game_board.movePlayer1(movePlayer1);
            game_board.displayBoard();
            hasTurn1 = Calamities(player1);
        }
        else if(menu1Choice == 2){
            cin.ignore(1000,'\n');
            cout << "Here is a list of your candies:\n";
            player1.printInventory();
            cout << "Enter a candy you wish to use\n";
            getline(cin, candyToUse);
            //check if its right, use it

            cout << "You have used the "; // << candy name << " candy. This has "
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