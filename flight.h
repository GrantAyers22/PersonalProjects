#ifndef FLIGHT_H
#define FLIGHT_H
#include "dsstring.h"

class flight
{
public:
    flight();
    void setData(DSSTRING oCity, DSSTRING dCity, int cost, int time, DSSTRING airline);
    DSSTRING getOrigin();
    DSSTRING getDestination();
    int getCost();
    int getTime();
    DSSTRING getAirline();
    flight& operator=(flight* f);
private:
   DSSTRING origin;
   DSSTRING destination;
   int cost;
   int time;
   DSSTRING airline;
};

#endif // FLIGHT_H
