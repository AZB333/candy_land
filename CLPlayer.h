#ifndef CLPLAYER_H
#define CLPLAYER_H
#include <iostream>
#include "Store.h"
using namespace std;


class Player{
    private:
        const static int _MAX_CANDY_AMOUNT = 9;
        int _stamina;
        double _gold;
        string _effect;
        Candy _inventory[9];
        int _candy_amount;
    public:
        Player();
        Player(int, double, string, Candy[], const int);

        int getCandyAmount() const;
        int getStamina() const;
        double getGold() const;
        string getEffect() const;

        void setCandyAmount(int);
        void setStamina(int);
        void setGold(double);
        void setEffect(string);

        void printInventory();
        Candy findCandy(string);
        bool addCandy(Candy); 
        bool removeCandy(string);

        int drawCard();
        bool playRockPaperScissors();
        void populatePlayer(string);
        //need like a player candy type scanner
        //loop through inventory, find if its magical
        bool hasMagicCandy();

};

#endif
