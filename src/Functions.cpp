#include <iostream>
#include <vector>
#include <cstdlib>
// #include <sstream>
#include <ctime>
#include <cmath>
#include <string>
#include <fstream>

// #include "..\header\functions.h"
// #include "..\header\dice.h"
// #include "..\header\day.h"

using namespace std;

void writeHeader(int totalDays, double demand) {
  std::fstream file("doc\\Sim_Results.txt", std::ios::app);

  std::string header = "\n\n\n_______________________________________________________________________\n"
                        "_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|\n"
                        "|This scenario conducted for " + std::to_string(totalDays) + " days at a demand modifier of " + std::to_string(demand) + ".\n" 
                        "|  DAY  | ON HAND AM | ON HAND PM | UNITS SOLD | WASTE/LOSS | STRATEGY |\n"
                        "|_______|____________|____________|____________|____________|__________|\n";
  if (file.is_open()) {
    file << header;
    file.close();
  }
  
}

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

// Reorder and set delivery
        if (!persistent) {                          // Threshold strat
          if (onHand < threshold) {
            deliveryIn.push_back(day[i].delivTime);
            delivery.push_back(target - onHand);
          }
        }
        else {                                      // Persistent strat
          if (day[i].dayNum % interval == 0) {
            deliveryIn.push_back(day[i].delivTime);
            delivery.push_back(target - onHand);
          }
        }