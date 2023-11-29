#include <iostream>
using namespace std;

int main(){
    bool canGo1 = true;
    bool canGo2 = true;
    int stopper;
    int turnMissed1 = 0;
    bool p1Lose2Turns = false;
    while(stopper != 5){
        if(stopper == 1){
            canGo1 = false;
        }
        else if(stopper == 2){
            p1Lose2Turns = true;
        }
        if(p1Lose2Turns == true){
            if(turnMissed1 == 2){
                canGo1 = true;
                p1Lose2Turns = false;
                turnMissed1 = 0;
                continue;
            }
            cout <<"1 cant go, missed turns is " << turnMissed1 << endl;
            canGo1 = false;
            
            turnMissed1++;
            cout << "missed turns after loop run is " << turnMissed1 << endl;
        }
        if(canGo1 == true){
            cout << "can go 1 is true\n";
        }
        else{
            cout << "can go 1 is false\n";
        }
        if(canGo2 == true){
            cout << "can go 2 is true\n";
        }
         else{
            cout << "can go 2 is false\n";
        }
       


        cin >> stopper;
    }



    return 0;
}