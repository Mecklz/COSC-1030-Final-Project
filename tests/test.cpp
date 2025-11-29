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
// Declare a mess of variables

    std::vector<int> deliveryIn;  // Time till delivery
    std::vector<int> delivery;    // Amount delivered

    int numRuns;                  // Number of variables
    int onHand;                   // Stock on hand at any given time
    int target;                   // Target stock level
    int threshold;                // Re-order threshold
    int interval;
    int i;                        // Day iterator
    int x;                        // Demand iterator
    int y;                        // Delivery iterator
    int sellMod;                  // Factor of 5 to modify sales numbers for bigger companies
    const double demand[3] = {0.5, 1.0, 1.5};                // Progressive modifier for each run. Low, normal, high demand scenarios.

    bool persistent = false;              // True if persistent re-order strat is selected

// And now the summary variables

    int oosDays = 0;
    int totalSales = 0;
    int totalOnhand = 0;
    int avgOnhand = 0;
    int totalLosswaste = 0;
    
    std::cout << std::endl << "How big is your business based on projected volume?" <<  std::endl; // ***** Adjust below for volume
    std::cout << "1 - Corner Store (~10-25 units on hand)" <<  std::endl;
    std::cout << "2 - Major Retailer (~50-125 units on hand)" <<  std::endl;
    std::cout << "3 - Wholesaler (~250-625 units on hand)" <<  std::endl;
    sellMod = pow(5,(sterilizeInput(3)-1)); 

    std::cout << std::endl << "What is your target stock on hand?" <<  std::endl;
    target = sterilizeInput(0);
    onHand = target;               // Set onHand with the stock target to begin

    std::cout << std::endl << "What restock startegy would you like to use?" <<  std::endl;
    std::cout << "1 - Threshold (Reorder triggered by dipping below a threshold)" <<  std::endl;
    std::cout << "2 - Persistent (Reorders are triggered by a revolving timer)" <<  std::endl;
    if (sterilizeInput(2) == 1) {
      std::cout << "Please enter the reorder threshold. EX. Low end number of items that will trigger a reorder." <<  std::endl;
      threshold = sterilizeInput(target-1);
    }
    else {
      persistent = true;
      std::cout << "\nEnter the order interval in days." ;
      std::cout << "\nReorder will trigger automatically at the end of every interval.\n";
      interval = sterilizeInput(0);
    }

    std::cout << "Please enter the number of days *MAX 365*" << std::endl;
    numRuns = sterilizeInput(365);


    // deliveryIn.push_back(3);
    // delivery.push_back(14);

    // deliveryIn.push_back(0);
    // delivery.push_back(10);

    // deliveryIn.push_back(1);
    // delivery.push_back(30);

    // deliveryIn.push_back(0);
    // delivery.push_back(10);

    
    // std::string header = "\n\n\n_______________________________________________________________________\n"
    //                      "_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_\n"
    //                      " This scenario conducted for " + std::to_string(totalDays) + " days at a demand modifier of " + std::to_string(demand) + ".\n" 
    //                      "|  DAY  | ON HAND AM | ON HAND PM | UNITS SOLD | WASTE/LOSS | STRATEGY |\n"
    //                      "|_______|____________|____________|____________|____________|__________|\n";
    // std::string line =   "   " + std::to_string(day) + "       " + std::to_string(ohAM) + "          " + std::to_string(ohPM) + "           " + std::to_string(sold) + "           " + std::to_string(waste) + "          " + strat;

    // cout << "Variables complete" << endl;

    // // try {
    //     std::vector<int> cleanUp;
    //     for (y = 0; y < deliveryIn.size(); y ++) {
    //         cout << "\n Pre block\n";
            
    //         cout << "\ndeliveryIn index: " << y << " >> " << deliveryIn[y] << endl;
    //         cout << "delivery index: " << y << " >> " << delivery[y] << endl;

    //         if (deliveryIn[y] > 0) {
    //             deliveryIn[y] --;

    //             cout << "\ndeliveryIn decremented >> " << deliveryIn[y] << endl;
    //         }
    //         else if (deliveryIn[y] == 0) {

    //             cout << "\n Delivery arrived. onHand start: " << ohAM << endl;

    //             ohAM += delivery[y];

    //             cout << "\n Delivery arrived. onHand end: " << ohAM << endl;

    //             cleanUp.insert(cleanUp.begin(), y);
    //         }

    //         cout << "\n Post block\n";
    //         cout << "\ndeliveryIn index: " << y << " >> " << deliveryIn[y] << endl;
    //         cout << "delivery index: " << y << " >> " <<delivery[y] << endl;
    //     }

    //     cout << "\nPre-cleanup deliveryIn size: " << deliveryIn.size() << "\ndelivery size: " << delivery.size() << endl;

    //     for (auto& index : cleanUp) {
    //         deliveryIn.erase(deliveryIn.begin() + index);
    //         delivery.erase(delivery.begin() + index);
    //     }

    //     cout << "\nPost-cleanup deliveryIn size: " << deliveryIn.size() << "\ndelivery size: " << delivery.size() << endl;

    //     for (y = 0; y < deliveryIn.size(); y ++) {
    //         cout << "\ndeliveryIn index: " << y << " >> " << deliveryIn[y] << endl;
    //         cout << "delivery index: " << y << " >> " <<delivery[y] << endl;
    //     }
    // }
    // catch (...){
    //     cout << "Catch~!" << endl;
    // }

    return 0;

}
    