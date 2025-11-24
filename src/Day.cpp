#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include "..\header\dice.h"
#include "..\header\day.h"


Day::Day() {
    sold = roll(6);
    delivTime = roll(4);
    unforeseen();
}

void Day::unforeseen() {
    int check;

    check = roll(30);
    if (check == 13) {
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
            event = "Someone made off with product today."
        }
    }
}
