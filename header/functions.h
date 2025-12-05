#ifndef FUNCH
#define FUNCH

using namespace std;

// Declare a mess of variables

    std::vector<int> deliveryIn;  // Time till delivery
    std::vector<int> delivery;    // Amount delivered

    int numRuns;                  // Number of variables
    int onHand;                   // Stock on hand at any given time
    int lostSale;                 // Temp variable for lost sales due to oos
    int target;                   // Target stock level
    int threshold;                // Re-order threshold
    int interval;
    int i;                        // Day iterator
    int x;                        // Demand iterator
    int y;                        // Delivery iterator
    int sellMod;                  // Factor of 5 to modify sales numbers for bigger companies
    const double demand[3] = {0.5, 1.0, 1.5};                // Progressive modifier for each run. Low, normal, high demand scenarios.

    bool persistent;              // True if persistent re-order strat is selected

// And now the summary variables

    int oosDays = 0;
    int totalSales = 0;
    int totalOnhand = 0;
    int avgOnhand = 0;
    int totalLosswaste = 0;
    int totalLostSales = 0;

// Start the file with a stylish header
void writeHeader(int totalDays, double demand) {
  std::fstream file("doc\\Sim_Results.txt", std::ios::app);

  std::string header = "\n\n\n_________________________________________________________________\n"
                        "_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_\n"
                        "|This scenario conducted for " + std::to_string(totalDays) + " days at a demand modifier of " + std::to_string(demand) + ".\n" 
                        "|    DAY    | ON HAND AM | ON HAND PM | UNITS SOLD | WASTE/LOSS |\n"
                        "|___________|____________|____________|____________|____________|\n";
  if (file.is_open()) {  
    file << header;
    file.close();
  }
}

void writeSummary(int& oosDays, int& totalSales, int& avgOnhand, int& totalLosswaste, int& totalLostSales, int days, double demand, int target) {
  std::fstream file("doc\\Sim_Results.txt", std::ios::app);

  std::string summary = "-----------------------------------------------------------------\n"
                        "Simulation ran for " + std::to_string(days) + "days with a demand mod of " + std::to_string(demand) + "\n"
                        "   and a target inventory on-hand of " + std::to_string(target) + "\n"
                        "\n  Total sales: " + std::to_string(totalSales) + "\n"
                        "  Average stock on hand: " + std::to_string(avgOnhand) + "\n"
                        "  Target sales lost due to OOS: " + std::to_string(totalLostSales) + "\n"
                        "  Total days out of stock: " + std::to_string(oosDays) + "\n"
                        "  Total loss/waste: " + std::to_string(totalLosswaste) + "\n"
                        "__________________________________________________________________\n"
                        "|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|\n\n";

  if (file.is_open()) {
    file << summary;
    file.close();
  }

  oosDays = 0;
  totalSales = 0;
  avgOnhand = 0;
  totalLosswaste = 0;
  totalLostSales = 0;

}

int sterilizeInput(int maxSelection) {
    int input;
    while (true) {

        std::cin >> input;  // Fills input buffer with the guess and a damned \n

        // check to see cin failbit set to 1
        if (std::cin.fail()) {
            std::cout << "\nYour entry contained invalid characters. Try again: ";
            std::cin.clear(); // Sets failbit to 0
            std::cin.ignore(1000,'\n'); // Clears the buffer
        } 
        else {
            if (maxSelection < 1) {
                std::cin.ignore(1000,'\n');
                return input;
            }
            else {
                if (input > 0 && input <= maxSelection) {
                    std::cin.ignore(1000,'\n');
                    return input;
                }
                else {
                    cout << "Your selection was out of range. Try Again: ";
                }
            }
        }
    }
}

std::vector<std::string> parseData(std::string fullStr) {

    std::string current;
    std::vector<std::string> datum;

    for (auto& character : fullStr) {
        if (character != 44) {
            current += character;
        }
        else {
            datum.push_back(current);
            current = "";
        }
    }
    datum.push_back(current);

    return datum;
}

std::string makeRow(std::string row, std::string alignment) {

    int x;
    int colWidth = 12;

    const char pipe = 124;
    const char space = 32;

    std::vector<std::string> datum = parseData(row);
    std::string fullStr = "";

    for (x = 0; x < datum.size(); x ++) {

        int indent = 0;
        int tail = 0;
        int negSpace = colWidth - (datum[x].length());

        if (alignment == "center") {            
            indent = negSpace / 2;
            tail = negSpace % 2;
            tail += indent;
        }
        else if (alignment == "left") {
                tail = negSpace;
        }
        else if (alignment == "right") {
                indent = negSpace;
        }
        
        for (int y = 0; y < indent; y ++) {
            fullStr += space;
        }
        fullStr += datum[x];

        for (int y = 0; y < tail; y ++) {
            fullStr += space;
        }

        fullStr += pipe;            
    }

    fullStr += "\n";
    return fullStr;
}


void append_File(std::string row_data, bool surprised, std::string event) {
    std::fstream file("doc\\Sim_Results.txt", std::ios::app);

    std::string line = makeRow(row_data, "center");
    if (surprised) {
        line = line + "* * * * * " + event + " * * * * *\n";
    }

    if (file.is_open()) {
        file << line;
        file.close();
    }
}

#endif