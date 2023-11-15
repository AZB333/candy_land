#include "Board.h"
#include <iostream>

using namespace std;

int main()
{
    string fileName = "candy.txt";
    vector<Candy> allCandies;
    Candy storeCandies[4];
    Board board;
    int iterator = 1;
    board.addCandyStore(27);
    board.addCandyStore(56);
    board.addCandyStore(71);
    for(int i = 0; i < 83; i++){
        board.movePlayer(1);
        if(board.isPositionCandyStore(i)){
            cout << "Welcome to Store " << iterator << ". Here's our selection!\n";
            Store store;
            store.populateStore(fileName);
            store.displayCandies();
            iterator++;
            cout << endl << endl;
        }
    }

    board.displayBoard();

    //go across entire map, if current position has a candy store, display store's candies

    return 0;
}