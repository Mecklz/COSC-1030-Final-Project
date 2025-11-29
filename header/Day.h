#ifndef DAYH
#define DAYH

using namespace std;



class Day {
   public:
    int delivTime;
    int sold;
    int onHand_morn;
    int onHand_eod;
    int lossWaste;
    std::string strat;
    int dayNum;
    std::string event;
    bool surprised;
    void append_File();
    Day();
    
   private:
    void unforeseen();

};

#endif