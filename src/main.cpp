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

    // First establish the size of the business. Each is exponentially bigger
    std::cout << std::endl << "How big is your business based on projected volume?" <<  std::endl; // ***** Adjust below for volume
    std::cout << "1 - Corner Store (~10-25 units on hand)" <<  std::endl;
    std::cout << "2 - Major Retailer (~50-125 units on hand)" <<  std::endl;
    std::cout << "3 - Wholesaler (~250-625 units on hand)" <<  std::endl;

    // This equation will determine to multiplier for sales. 5^(0, 1, or 2)
    sellMod = pow(5,(sterilizeInput(3)-1));

    // Set the target for on hand product
    std::cout << std::endl << "What is your target stock on hand?" <<  std::endl;
    target = sterilizeInput(0);

    // Set the strat and then determine the threshhold/interval respective to the strat selected
    std::cout << std::endl << "What restock startegy would you like to use?" <<  std::endl;
    std::cout << "1 - Threshold (Reorder triggered by dipping below a threshold)" <<  std::endl;
    std::cout << "2 - Persistent (Reorders are triggered by a revolving timer)" <<  std::endl;
    
    // If threshold strat is selected
    if (sterilizeInput(2) == 1) {
      std::cout << "Please enter the reorder threshold. EX. Low end number of items that will trigger a reorder." <<  std::endl;
      threshold = sterilizeInput(target-1);
    }
    // If persistent strat is selected
    else {
      persistent = true;
      std::cout << std::endl <<  "Enter the order interval in days." ;
      std::cout << std::endl <<  "Reorder will trigger automatically at the end of every interval." <<  std::endl;
      interval = sterilizeInput(0);
    }

    // Finally determine the number of days it should run
    std::cout << "Please enter the number of days *MAX 365*" << std::endl;
    numRuns = sterilizeInput(365);

    // HERE IT IS. The obsessive thing that made me create this messy bunch of code.
    // The idea was simply to make sure all of the random number generation happened
    // together and only once. Aaaand of course to make a vector of classes. lol
    std::vector<Day> day(numRuns);

// Begin the sim loop

    // Demand scenario loop
    for (x = 0; x < 3; x ++) {
      writeHeader(numRuns, demand[x]);
      onHand = target;                  // Set onHand with the stock target to begin

      // Day loop
      for (i = 0; i < day.size(); i ++) {

        day[i].dayNum = i + 1;                       // Set the day number in the class element
        int lostSale = 0;                           // Temp variable for lost sales due to oos

        // Receive a delivery
          // Cleanup vector for if one or more deliveries arrive. This scenario can only 
          // happen during persitent strat. I discovered too late that there was a possibility
          // that deliveries may stack on threshold strat as well and did not have time to implement.
        std::vector<int> cleanUp;                    
        for (y = 0; y < deliveryIn.size(); y ++) {
            if (deliveryIn[y] > 0) {                 // Is the deliv timer at 0?
                deliveryIn[y] --;                   // No? Decrement the timer by 1
            }
            else if (deliveryIn[y] == 0) {         // Yes? Add it to on-hand
                onHand += delivery[y];
                cleanUp.insert(cleanUp.begin(), y);  // Mark the index of the completed delivery
            }
        }
        for (auto& index : cleanUp) {               // Removed the completed delivery
            deliveryIn.erase(deliveryIn.begin() + index);
            delivery.erase(delivery.begin() + index);
        }

        // Reorder and set delivery
        if (!persistent) {                                    // Threshold strat
          if (onHand < threshold && delivery.size() == 0) {  // Has the threshold been met?
            deliveryIn.push_back(day[i].delivTime);         // Create a delivery
            delivery.push_back(target - onHand);           // For the amount missing
          }
        }
        else {                                        // Persistent strat
          if (day[i].dayNum % interval == 0) {       // Use mod to check against the current day num
            deliveryIn.push_back(day[i].delivTime); // Create delivery
            delivery.push_back(target - onHand);
          }
        }

        // Record stock values and sell product. Record loss/waste.
        if (onHand < 1) {
          oosDays ++;
        }
        
        day[i].onHand_morn += (onHand*day[i].fire);       // Record AM stock modified by fire value
        day[i].lossWaste += onHand - day[i].onHand_morn;  // Add anything destroyed in the fire to loss/waste
        day[i].sold = (day[i].sale * demand[x] * sellMod);// Calculate what was sold
        onHand = day[i].onHand_morn - day[i].sold;        // Determine whats left
        if (onHand < 1) {         // Handling for fractions of 1 or lower stock remainder
          if (onHand < 0) {
            lostSale += (onHand * (-1)); // Added a new trap for OOS sale scenarios
          }
          onHand = 0;
        }

        // Update the summary variables, set the PM on hand, and write the info to file.
        totalLosswaste += day[i].lossWaste;    
        totalLostSales += lostSale;
        totalSales += (day[i].sold - lostSale);
        day[i].onHand_eod = onHand;
        totalOnhand += day[i].onHand_eod;
        append_File(day[i].get_rowData(), day[i].surprised, day[i].event);
      }

      // End of day loop. Write summary to file
      avgOnhand = totalOnhand/numRuns;
      writeSummary(oosDays, totalSales, avgOnhand, totalLosswaste, totalLostSales, numRuns, demand[x], target);
    }

    // End of demand scenario loop. Ask if user would like to run again.
    cout << "\nAll three scenarios have run and the results have been appended to .\\doc\\Sim_Results.txt" << endl;
    cout << "Enter anything to run another 3 scenarios or enter 'quit' to terminate the program." << endl;
    std::getline(std::cin, rerun);
    std::cin.ignore(1000,'\n'); // Clears the buffer
  }    
}