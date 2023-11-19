#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Board.h"
#include "Store.h"
#include "CLPlayer.h"

using namespace std;

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

/*    just holding this here just in case
if((playerPos % 3 == 0 && cardResult == 2) || (playerPos % 3 == 1 && cardResult == 3) || (playerPos % 3 == 2 && cardResult == 1)){//pos two less than result
        game_board.movePlayer1(1);
    }
    else if((playerPos % 3 == 0 && cardResult == 3) || (playerPos % 3 == 1 && cardResult == 1) || (playerPos % 3 == 2 && cardResult == 2)){//pos equals result
        game_board.movePlayer1(2);
    }
    else if((playerPos % 3 == 0 && cardResult == 1) || (playerPos % 3 == 1 && cardResult == 2) || (playerPos % 3 == 2 && cardResult == 3)){//pos is one less than result
        game_board.movePlayer1(3);
    }
    else if((playerPos % 3 == 0 && cardResult == 5) || (playerPos % 3 == 1 && cardResult == 6) || (playerPos % 3 == 2 && cardResult == 4)){//pos five less than result
        game_board.movePlayer1(4);
    }
    else if((playerPos % 3 == 0 && cardResult == 6) || (playerPos % 3 == 1 && cardResult == 4) || (playerPos % 3 == 2 && cardResult == 5)){//pos five less than result
        game_board.movePlayer1(5);
    }
    else if((playerPos % 3 == 0 && cardResult == 4) || (playerPos % 3 == 1 && cardResult == 5) || (playerPos % 3 == 2 && cardResult == 6)){//pos four less than result
        game_board.movePlayer1(6);
    }*/
int main(){
    srand((unsigned) time(NULL));
    Board game_board;
    Player player1;
    Player player2;
    string candyFileName = "candy.txt";
    string characterFileName = "characters.txt";
    vector<Candy> allCandies;
    // game_board.movePlayer1(1);
    game_board.movePlayer2(50);

    //////Drawing cards test///////////
    int cardResult = -1;
    
    //if tree for moving correctly, gonna be massive, maybe make a function in main for it
    //if position % 3 = 0 its magenta, if 1 its green, if 2 its blue

    cardResult = player1.drawCard();
    int playerPos = game_board.getPlayer1Position();
    //how to make this a function
    int moveAmount = determineMoveAmount(playerPos, cardResult);
    game_board.movePlayer1(moveAmount);
    game_board.displayBoard();
    cout << game_board.getPlayer1Position();
}


/*just throwing this here in case its needed

vector<Candy> readCandy(string file_name, vector<Candy> candies){ //add extra candy members
    cout << fixed << setprecision(2);
    ifstream candyFile;
    string line;
    candyFile.open(file_name);
    if(candyFile.fail()){
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
                    price = line;
                    actualPrice = stoi(price);
                } else if(iterator == 3){
                    iterator++;
                    candyType = line;
                }
               
            }
            current_candy.name = name;
            current_candy.description = description;
            current_candy.price = actualPrice;
            current_candy. candy_type = candyType;
            candies.push_back(current_candy);
            }
           
        }
    return candies;
}
}

*/


/*throwing rock paper scissors here
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
*/