#pragma once
#include <iostream>

template<int... Dice>
int roll() {
    int i = 0;
    int total = 0;
    int bag[] = { Dice... };
    for (int roll : bag) {
        total += rand() % roll;
        i++;
    }
    return total / i;
}
