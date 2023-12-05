#ifndef CLPLAYER_H
#define CLPLAYER_H
#include <iostream>
#include "Store.h"
using namespace std;

struct Card{
    string color;
    bool x2;
};


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

        int getCandyAmount() const;//getters
        int getStamina() const;
        double getGold() const;
        string getEffect() const;

        void setCandyAmount(int);//setters
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

        bool hasMagicCandy();//functions to determine if a player has a certain candy
        bool hasImmunityCandy();
        bool hasRobbersRepel();

        Candy findImmunityCandy();//returns desired candy types
        Candy findMagicalCandy();

        int determineImmunityStrength(Candy);//used for menu option 2 using poison candy
        int determinePoisonStrength(Candy);

};

#endif
