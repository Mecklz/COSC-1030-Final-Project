#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
// #include "..\header\dice.h"
// #include "..\header\day.h"
using namespace std;


template<typename... Dice> // This template is set to accept a pack of ints
double roll(Dice... dice) {  // The pack of ints is unpacked as arguments
    int bag[] = { dice... };  // The arguments are constructed into an array
    int length = 0;         // the length of the array
    double temp = 0;          // Multi-purpose int      
    int x;

    for (int param : bag) {
        length ++;
        cout << param << endl; // DEBUG
        cout << length << endl;
    }

    if (length == 1) {             
        cout << "Branch one." << endl;
        return (rand() % (bag[0] + 1));  
    }

    else if (length == 2) {
        cout << "Branch two." << endl;
        for (x = 0; x < bag[1]; x ++) {
            temp += (rand() % (bag[0] + 1));
            cout << temp << endl;
        }
        cout << temp << "/" << bag[1] << endl;
        double result = temp / bag[1];
        return result;          // This is still not returning doubles........
    }

    else if (length == 3) {
        cout << "Branch three." << endl;
        if (bag[2] == 1) {
            for (x = 0; x < bag[1]; x ++) {
                temp += (rand() % (bag[0] + 1));
                cout << temp << endl;
            }
            return ((temp / bag[1]) / bag[0]);
        }

        else if (bag[2] == 0) {
            temp = (rand() % (bag[0] + 1)) + (rand() % (bag[1] + 1));
            return std::floor(temp / 2);
        }
    }

    return 0;
};

int main(){

    srand(time(0));

    cout << setprecision(2);

    double one = roll(100);
    cout << one << endl;

    double two = roll(45,2);
    cout << two << endl;

    double three = roll(100,2,1);
    cout << three << endl;

    double four = roll(100,45,0);
    cout << four << endl;
    
    



}
    