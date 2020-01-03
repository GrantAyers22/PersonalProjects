#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "flightplanner.h"
#include "dsstring.h"
#include "adjnode.h"
#include "flight.h"


using namespace std;

int main(int argc, char** argv){

    if (argc==1){
        //return Catch :: Session().run();
    }

    //creating DSSTRINGS with the proper file extension
    DSSTRING flightData = argv[1];
    DSSTRING flightPlan = argv[2];
    DSSTRING outputFile = argv[3];

    flightPlanner fp;
    fp.paths(flightData, flightPlan, outputFile);
    fp.fillAdjacencyList();
    fp.destination();
    fp.printStack();


}


