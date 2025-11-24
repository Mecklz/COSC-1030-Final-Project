#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <fstream>

#include "..\header\functions.h"
#include "..\header\dice.h"
#include "..\header\day.h"

int main() {

  std::cout << "Stock Simulation!\n";
  std::string rerun = "play";
  
// Begin the play loop

  while (rerun != "quit") {

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
      threshold = sterilizeInput(target-1);
    }
    else {
      persistent = true;
      std::cout << std::endl <<  "Enter the order interval in days." <<  std::endl;
      std::cout << std::endl <<  "Reorder will trigger automatically at the end of every interval." <<  std::endl;
      interval = sterilizeInput(0);
    }

    std::cout << "Please enter the number of days *MAX 365*" << std::endl;
    numRuns = sterilizeInput(365);

    std::vector<Day> day(numRuns);

// Begin the sim loop

    // Demand scenario loop
    for (x = 0; x < 3; x ++) {
      writeHeader(numRuns, demand[x]);

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

        // Record stock values and sell product. Record loss/waste.
        if (onHand < 1) {
          oosDays ++;
        }
        day[i].onHand_morn = onHand;
        onHand -= (day[i].sold * demand[x]);
        if (onHand < 1) {
          if (onHand < 0) {
            day[i].lossWaste += (onHand*(-1));
            totalLosswaste += day[i].lossWaste;
            totalSales += ((day[i].sold * demand[x]) - (day[i].lossWaste));
          }
          onHand = 0;
        }
        day[i].onHand_eod = onHand;
        totalOnhand += day[i].onHand_eod;
      }
      avgOnhand = totalOnhand/numRuns;
      writeSummary(oosDays, totalSales, avgOnhand, totalLosswaste, target, numRuns, demand[x]);
    }
    cout << "\nAll three scenarios have run and the results have been appended to Sim_Results.txt" << endl;
    cout << "Enter anything to run another 3 scenarios or enter 'quit' to terminate the program." << endl;
    std::getline(std::cin, rerun);
    std::cin.ignore(1000,'\n'); // Clears the buffer
  }    
}