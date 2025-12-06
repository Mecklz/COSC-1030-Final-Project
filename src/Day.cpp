#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

// #include "..\header\functions.h"
#include "..\header\dice.h"
#include "..\header\day.h"


void Day::unforeseen() {
    int check;
    surprised = false;
    fire = 1.0;

    // 1 in 30 has been giving me good results so I stuck with it.
    check = roll(30);
    if (check == 13) {
        surprised = true;
        check = roll(4);

        // Massive order
            // Just a quick multiplication of the sold value and a D3 
            // increased by 1 so 1 isn't a possible result
        if (check == 1) {
            sold = sold * (roll(3) + 1);
            event = "Someone placed a massive order today.";
        }

        // Delayed Delivery
            // A delay in the supply chain. The roll should produce a possiblility of 1-5 with
            // the highest probability being a roll of 2. 
        else if (check == 2) {       
            delivTime = delivTime + roll(8,3,0);  
            event = "Any deliveries were delayed today.";
        }

        // Fire
            // Sets fire to a random proportion in order to
            // divide the remaining stock and simulate loss
        else if (check == 3) {       
            fire = roll(100,1,1);    
            event = "There was a fire in the stock room today.";
        }

        // Theft
            // Someone took a monitor off my shelf while I was looking down
        else if (check == 4) {       
            onHand_morn = onHand_morn - 1;
            event = "Someone made off with product today.";
        }
    }
}

/* This never came to fruition by I'm too sentimental to delete it
The intention was to try and remove some global variables to clean things up
by having the classes extract data from one another. Ran out of time debugging.

void Day::start_ofDay(std::vector<int>& deliveryIn, std::vector<int>& delivery, int onHand) {
    std::vector<int> cleanUp;                    // Cleanup vector for if one or more deliveries arrive
    int y;

    for (y = 0; y < deliveryIn.size(); y ++) {
        if (deliveryIn[y] > 0) {
            deliveryIn[y] --;
        }
        else if (deliveryIn[y] == 0) {
            onHand += delivery[y];
            cleanUp.insert(cleanUp.begin(), y);
        }
    }
    for (auto& index : cleanUp) {
        deliveryIn.erase(deliveryIn.begin() + index);
        delivery.erase(delivery.begin() + index);
    }
}
*/

// Returns a string with all of the collected and modified data of the day in a csv type string
std::string Day::get_rowData() {
    std::string line;
    line = std::to_string(dayNum) + "," + std::to_string(onHand_morn) + "," + std::to_string(onHand_eod) + "," + std::to_string(sold) + "," + std::to_string(lossWaste);
    reset();
    return line;
}

// Reset these values to zero for the next demand scenario
void Day::reset() {
    onHand_morn = 0;
    onHand_eod = 0;
    lossWaste = 0;    
}

Day::Day() {
    fire = 1.0;
    onHand_morn = 0;       // Set these values to zero so they can be interacted with immediately
    onHand_eod = 0;
    lossWaste = 0;
    sale = (roll(6) - 1);  // The minus one here jsut allows 0 sales to be a legitiment result for a day.
    delivTime = roll(4);   // Sets the delivery time
    unforeseen();          // Fun random occurrences
}
