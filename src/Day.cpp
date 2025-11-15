#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "..\header\dice.h"
#include "..\header\day.h"

Day::Day() {
    demand = roll(100,2,1);
    sale = demand * level;
}

int get_morn_stock() {
    
}