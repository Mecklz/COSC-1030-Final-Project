#pragma once
#include <iostream>

template<int... Dice> // This template is set to accept a pack of ints
int roll(Dice... dice) {  // The pack of ints is unpacked as arguments
    int bag[] = { dice... };  // The arguments are constructed into an array
    int i = 0;                // i to count the number of arguments in the pack
    int total = 0;            // running total of all rolls
    
    for (int roll : bag) {         // for each roll : in the 'bag' of dice
        total += rand() % roll;    // roll
        i ++;                      // increment i
    }
    return total/i;
};