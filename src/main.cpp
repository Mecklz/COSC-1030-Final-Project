#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "..\header\dice.h"
#include "..\header\day.h"

int main() {
  std::cout << "Stock Simulation!\n";
  std::string rerun = "play";
  

  while (rerun != "quit") {
    int numRuns;
    int reOrder;
    int i;
    int SKU = 0;
    srand(time(0));

    std::cout << "Please enter the number of simulations *MAX 10,000*" << std::endl;
    std::cin >> numRuns;

    std::cout << "Please enter the reorder threshold. EX. Low end number of items that will trigger a reorder." <<  std::endl;
    std::cin >> reOrder;
    
    std::vector<Day> day(numRuns);

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