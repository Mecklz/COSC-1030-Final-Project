#include <iostream>
#include <vector>
#include <cstdlib>
// #include <sstream>
#include <ctime>
#include <cmath>
#include <string>
#include <fstream>
#include "..\header\dice.h"
#include "..\header\day.h"
using namespace std;


// template<typename... Dice> // This template is set to accept a pack of ints
// double roll(Dice... dice) {  // The pack of ints is unpacked as arguments
//     int bag[] = { dice... };  // The arguments are constructed into an array
//     int length = 0;         // the length of the array
//     double temp = 0.0;          // Multi-purpose int      
//     double rando;            // Random number holder
//     int x;                  // for loop iterator

//     for (int param : bag) {
//         length ++;
//         cout << param << endl; // DEBUG
//         cout << length << endl;
//     }

//     if (length == 1) {             
//         cout << "Branch one." << endl;
//         return (rand() % (bag[0] + 1));  
//     }

//     else if (length == 2) {
//         cout << "Branch two." << endl;
//         for (x = 0; x < bag[1]; x ++) {
//             rando = (rand() % (bag[0] + 1));
//             temp += rando;

//             cout << "rando: " << rando << " temp: " << temp << endl;
//         }
//         cout << temp << "/" << bag[1] << endl;
//         return temp / bag[1];
//     }

//     else if (length == 3) {
//         cout << "Branch three." << endl;
//         cout << setprecision(2);
//         if (bag[2] == 1) {
//             for (x = 0; x < bag[1]; x ++) {
//                 rando = (rand() % (bag[0] + 1));
//                 temp += rando;

//                 cout << setprecision(2);
//                 cout << "rando: " << rando << " temp: " << temp << endl;
                
//             }
//             return ((temp / bag[1]) / bag[0]);
//         }

//         else if (bag[2] == 0) {
//             temp = (rand() % (bag[0] + 1)) + (rand() % (bag[1] + 1));
//             return std::floor(temp / 2);
//         }
//     }

//     return 0;
// };
// void writeHeader(int totalDays, double demand) {
//   std::fstream file("doc\\Sim_Results.txt", std::ios::app);

//   std::string header = "\n\n\n_______________________________________________________________________\n"
//                         "_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|\n"
//                         "|This scenario conducted for " + std::to_string(totalDays) + " days at a demand modifier of " + std::to_string(demand) + ".\n" 
//                         "|  DAY  | ON HAND AM | ON HAND PM | UNITS SOLD | WASTE/LOSS | STRATEGY |\n"
//                         "|_______|____________|____________|____________|____________|__________|\n";
//   if (file.is_open()) {
//     file << header;
//     file.close();
//   }
  
// }

int sterilizeInput(int maxSelection) {
    int input;
    while (true) {

        std::cin >> input;  // Fills input buffer with the guess and a damned \n

        // check to see cin failbit set to 1
        if (std::cin.fail()) {
            std::cout << "\nYour entry contained invalid characters. Try again: ";
            std::cin.clear(); // Sets failbit to 0
            std::cin.ignore(1000,'\n'); // Clears the buffer
        } 
        else {
            if (maxSelection < 1) {
                std::cin.ignore(1000,'\n');
                return input;
            }
            else {
                if (input > 0 && input <= maxSelection) {
                    std::cin.ignore(1000,'\n');
                    return input;
                }
                else {
                    cout << "Your selection was out of range. Try Again: ";
                }
            }
        }
    }
}

int main(){

//     srand(time(0));

//     cout << setprecision(2);

//     double one = roll(100);
//     cout << one << endl << "---------" << endl;

//     double two = roll(45,2);
//     cout << two << endl << "---------" << endl;

//     double three = roll(100,2,1);
//     cout << three << endl << "---------" << endl;

//     double four = roll(100,45,0);
//     cout << four << endl << "---------" << endl;
    int totalDays = 300;
    double demand = 0.75;
    int day = 3;
    int ohAM = 23;
    int ohPM = 20;
    int sold = 2;
    int waste = 1;
    std::string strat = "THRE";

    // std::string header = "\n\n\n_______________________________________________________________________\n"
    //                      "_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_\n"
    //                      " This scenario conducted for " + std::to_string(totalDays) + " days at a demand modifier of " + std::to_string(demand) + ".\n" 
    //                      "|  DAY  | ON HAND AM | ON HAND PM | UNITS SOLD | WASTE/LOSS | STRATEGY |\n"
    //                      "|_______|____________|____________|____________|____________|__________|\n";
    // std::string line =   "   " + std::to_string(day) + "       " + std::to_string(ohAM) + "          " + std::to_string(ohPM) + "           " + std::to_string(sold) + "           " + std::to_string(waste) + "          " + strat;

    
    cout << "Output: " << sterilizeInput(3);

    return 0;

}
    