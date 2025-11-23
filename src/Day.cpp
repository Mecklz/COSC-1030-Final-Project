#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
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
        }

        // Delayed Delivery
        else if (check == 2) {
            delivTime = delivTime + roll(7,4,0); // Don't forget to repair dice.h for this roll
        }

        // Fire
        else if (check == 3) {
            onHand_morn = onHand_morn * roll(100,1,1);
        }

        // Theft
        else if (check == 4) {
            onHand_morn = onHand_morn - 1;
        }
    }
}
