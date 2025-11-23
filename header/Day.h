#ifndef DAYH
#define DAYH

using namespace std;



class Day {
   public:
    int delivTime;
    int sold;
    int onHand_morn;
    int onHand_eod;
    int thresholdUsed;
    int dayNum;
   
   private:
    void unforeseen();
       

};

#endif