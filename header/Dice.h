#ifndef DICEH
#define DICEH

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// Function call requires at least one parameter and no more than three.
// roll(<side_count>, <dice_count (side_count2 for skew)>, <proportion(1)/skew(0) switch>)

template<typename... Dice> // This template is set to accept a pack of ints
double roll(Dice... dice) {  // The pack of ints is unpacked as arguments
    int bag[] = { dice... };  // The arguments are constructed into an array
    int length = 1;         // the length of the array
    int temp = 0;          // Multi-purpose int      
    
    for (int param : bag) {
        length ++;
    }

// A simple roll of a variable sided die
    if (length == 1) {             
        return (rand() % (bag[0] + 1));  
    }

// An average of two similar, variable sided dice to create a more normal
// distribtuion of probabilities. 
    else if (length == 2) {
        for (x = 0; x < bag[1]; x ++) {
            temp += (rand() % (bag[0] + 1));
        }
        return std::floor(temp / bag[1]);
    }

    else if (length == 3) {
// Same as above but further divided by the side count to create a proportion.
        if (bag[2] == 1) {
            for (x = 0; x < bag[1]; x ++) {
                temp += (rand() % (bag[0] + 1));
            }
            return ((temp / bag[1]) / bag[0]);
        }

// two disimilar dice averaged out to create a skewed distribution. Been trying to 
// find a way to keep the entire range of the larger die. A d10 and a d4 will yield 
// nothing above 7 and so cuts out the range leaving a regular distribution over the
// new range 1-7
        else if (bag[2] == 0) {
            temp = (rand() % (bag[0] + 1)) + (rand() % (bag[1] + 1))
            return std::floor(temp / 2);
        }
    }

    return 0;
};

#endif