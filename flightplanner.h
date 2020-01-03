#ifndef FLIGHTPLANNER_H
#define FLIGHTPLANNER_H
#include "dsstring.h"
#include "stack.h"
#include "adjnode.h"
#include "flight.h"
#include "fstream"

class flightPlanner{
public:
    flightPlanner();
    void paths(DSSTRING FPD, DSSTRING FRP, DSSTRING OFP);
    void solve(DSSTRING origin, DSSTRING destination, char key);
    void fillAdjacencyList();
    void destination();
    int convertToInt(char * a);
    void calculateTimeAndHours(Stack<DSSTRING> stack);
    bool containsDestination(DSSTRING destination, llist<DSSTRING> listOfCities);
    void printStack();
    void setFlightData(DSSTRING origin, DSSTRING destination, char key);


private:
    DSSTRING flightDataPath;
    DSSTRING flightRequestPath;
    DSSTRING outputFilePath;
    adjacencyList<DSSTRING> AJ;
    llist<flight> flightList;
    llist<Stack<DSSTRING>> listOfStacks;
    int totalHours;
    int totalCost;
    DSSTRING O;
    DSSTRING D;
    char optKey;

};

#endif // FLIGHTPLANNER_H
