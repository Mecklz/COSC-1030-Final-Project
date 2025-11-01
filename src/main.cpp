#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
// #include "header\dice.hpp"

/*
main() will be the structure of the sim loop. In it will reside either: one loop
for the passing of a day and one loop to describe normal business hours of a
physical stores open hours. OR One single loop describing hours and conditionals
to denote hours in a day and the average happenings at those times.
*/

// This template is set to accept a pack of ints
// The pack of ints is unpacked as arguments
// The arguments are constructed into an array
// i to count the number of arguments in the pack
// running total of all rolls
// for each roll : in the 'bag' of dice
// roll
// increment i
template <typename... Dice> 
int roll(Dice... dice) {  
    int bag[] = { dice... };  
    int i = 0;                
    int total = 0;            
    
    for (int roll : bag) {
      if (roll == 0){
        
      }   
        total += rand() % roll;    
        i ++;                      
    }
    return total/i;
}

int reorder(int i) {
  return i+4; // or whatever number of days it takes
}

int main() {
  std::cout << "Stock Simulation!\n";
  std::string rerun = "play";

  while (rerun != "quit") {
    int numRuns;
    int reOrder;
    int i;
    int SKU = 0;
    srand(time(0));

    //std::vector<int> catalogue;

    std::cout << "Please enter the number of simulations *MAX 10,000*" << std::endl;
    std::cin >> numRuns;

    std::cout << "Please enter the reorder threshold. EX. Low end number of items that will trigger a reorder." <<  std::endl;
    std::cin >> reOrder;
    
    // while (true){
    //   std::cout << "Enter SKUs one by one followed by 'x' to continue" << endl;
    //   std::cin >> SKU;
    //   if (SKU == 'x'){
    //     break;
    //   }
    //   else {
    //     catalogue.push_back(SKU);
    //   }
    // }

    for (i = 0; i < numRuns; i++){
      int stock = 18;
      //if (i is equal to reorder/restock day){
      //  if (roll(TBD) > TBD) {
      //    sell 1 monitor.
      //}
      //  else if (roll(TBD) > TBD){
      //    sell 2 monitors
      //}
      //}
      if (stock < 1) {
        // int dayNum = reorder(i);
      }
    }
  }
    

}