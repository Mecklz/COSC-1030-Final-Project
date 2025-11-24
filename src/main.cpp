#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include "..\header\dice.h"
#include "..\header\day.h"

int sterilizeInput(int maxSelection) {

}

void printTo_file(int dayNum, string path) {

}

bool atThreshold(int onHand, int threshold) {
  if (onHand < threshold) {
    return true;
  }
}

void restock(int dayNum) {
  // We're gonna start this as lines in the main loop since we want to access the
  // restock vectors.
}

int main() {

  std::cout << "Stock Simulation!\n";
  std::string rerun = "play";
  
// Begin the play loop

  while (rerun != "quit") {

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

    bool persistent;              // True if persistent re-order strat is selected

    srand(time(0));               // Magic BEANS for a cow? WTH, Jack?!

// Menu selections

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
      threshold = sterilizeInput(0);
    }
    else {
      persistent = true;
      std::cout << std::endl <<  "Enter the order interval in days." <<  std::endl;
      std::cout << std::endl <<  "Reorder will trigger automatically at the end of every interval." <<  std::endl;
      interval = sterilizeInput(0);
    }

    std::cout << "Please enter the number of simulations *MAX 10,000*" << std::endl;
    numRuns = sterilizeInput(0);

    std::vector<Day> day(numRuns);

// Begin the sim loop

    // Demand scenario loop
    for (x = 0; x < 3; x ++) {

      // Day loop
      for (i = 0; i < day.size(); i ++) {

        // Receive a delivery
        try {
          for (y = 0; y < deliveryIn.size(); y ++){
            if (deliveryIn[y] > 0) {
              deliveryIn[y] --;
            }
            else if (deliveryIn[y] == 0){
              onHand += delivery[y];
              deliveryIn.erase(deliveryIn.begin() + y);
              delivery.erase(delivery.begin() + y);
            }
          }
        }
        catch (...){}

        // Reorder and set delivery
        if (!persistent) {
          if (onHand < threshold) {
            deliveryIn.push_back(day[i].delivTime);
            delivery.push_back(target - onHand);
          }
        }
        else {
          if (day[i].dayNum % interval == 0) {
            deliveryIn.push_back(day[i].delivTime);
            delivery.push_back(target - onHand);
          }
        }
        day[i].onHand_morn = onHand;
        onHand += day[i].sold * demand[x];
        day[i].onHand_eod = onHand;

      }
    }

  }
    

}