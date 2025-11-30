#ifndef DAYH
#define DAYH

using namespace std;



class Day {
   public:
    int delivTime;
    int sale;

    int sold;
    int onHand_morn;
    int onHand_eod;
    int lossWaste;
    int dayNum;
    double fire;
    
    std::string event;

    bool surprised;
    

    void append_File();
    // void start_ofDay();

    Day();
    
   private:
    void unforeseen();
    void reset();
    

};

#endif