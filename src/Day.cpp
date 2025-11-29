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

    check = roll(30);
    if (check == 13) {
        surprised = true;
        check = roll(4);

        // Massive order
        if (check == 1) {
            sold = sold * roll(3);
            event = "Someone placed a massive order today.";
        }

        // Delayed Delivery
        else if (check == 2) {
            delivTime = delivTime + roll(7,4,0); // Don't forget to repair dice.h for this roll
            event = "Our delivery was delayed today.";
        }

        // Fire
        else if (check == 3) {
            onHand_morn = onHand_morn * roll(100,1,1);
            event = "There was a fire in the stock room today.";
        }

        // Theft
        else if (check == 4) {
            onHand_morn = onHand_morn - 1;
            event = "Someone made off with product today.";
        }
    }
}

void Day::append_File() {
    std::fstream file("doc\\Sim_Results.txt", std::ios::app);

    std::string line =   "   " + std::to_string(dayNum) + "       " + std::to_string(onHand_morn) + "          " + std::to_string(onHand_eod) + "           " + std::to_string(sold) + "           " + std::to_string(lossWaste) + "          " + strat + "\n";
    if (surprised) {
        line = line + "* * * * * " + event + " * * * * *\n";
    }
    if (file.is_open()) {
        file << line;
        file.close();
    }
}

Day::Day() {
    onHand_morn = 0;
    sold = roll(6);
    delivTime = roll(4);
    unforeseen();
}
