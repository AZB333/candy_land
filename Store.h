#ifndef STORE_H
#define STORE_H
#include <iostream>
#include <vector>
using namespace std;

struct Candy
{
    string name;
    string description;
    string effect;
    int effect_value;
    string candy_type;
    int price;
};


class Store{
    private:
        vector<Candy> all_candy;
        Candy _store_inventory[4];
        const static int _MAX_STORE_CANDY = 4;
    public:
        Store();
        void displayCandies();
        void populateStore(string, vector<Candy>);
        Candy findCandy(string);
};


#endif