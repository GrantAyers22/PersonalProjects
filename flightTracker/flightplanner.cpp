#include "flightplanner.h"
#include "dsstring.h"
#include "stack.h"
#include "adjnode.h"
#include <fstream>
#include "flight.h"

using namespace std;

flightPlanner::flightPlanner(){
    totalHours = 0;
    totalCost = 0;
    optKey = 't';
}
void flightPlanner:: paths(DSSTRING FDP, DSSTRING FRP, DSSTRING OFP){
    flightDataPath = FDP;
    flightRequestPath = FRP;
    outputFilePath = OFP;
}

void flightPlanner :: solve(DSSTRING origin, DSSTRING destination, char optimizationKey){
    AJ.iteratorToHead();
    Stack<DSSTRING> s = Stack<DSSTRING>();
    //find origin city
    while (AJ.getIteratorHead() != origin){
        AJ.stepForward();
    }
    //push iterator to stack
    s.push(AJ.getIteratorHead());

    //creating a list of cities to go from origin
    llist<DSSTRING> flightOptions = llist<DSSTRING>();
    flightOptions = AJ.getIteratorData();

    while (s.peek() != destination){
        if (containsDestination(destination, flightOptions)){
            s.push(destination);
        }
        else {
            flightOptions.iteratorToHead();
            flightOptions.stepForward();
            DSSTRING cityToGoTo = flightOptions.getIteratorData();
            s.push(cityToGoTo);
            AJ.iteratorToHead();
            while (AJ.getIteratorHead() != cityToGoTo){
                AJ.stepForward();
            }
            flightOptions = AJ.getIteratorData();
        }
    }
    listOfStacks.pushBack(s);
}

bool flightPlanner :: containsDestination(DSSTRING destination, llist<DSSTRING> listOfCities){
    listOfCities.iteratorToHead();
    do{
       listOfCities.stepForward();
        if (destination == listOfCities.getIteratorData()){
            return true;
        }
    } while(!listOfCities.isIteratorTail());
    return false;
}

int flightPlanner :: convertToInt(char *a){
    int counter = 0;
    int final = 0;
    int c = 0;
    int * num = new int[10];
    int * temp = new int[10];
    int nombre = 1;
    while (a[counter] != '\0'){
        num[counter] = a[counter] - 48;
        counter++;
    }

    while (counter !=0){

        for (int i = 1; i < counter; i++){
            nombre *= 10;
        }

        final+=(num[c]*nombre);
        counter--;
        c++;
        nombre = 1;
    }
    delete[] temp;
    delete[] num;
    return final;
}
void flightPlanner :: fillAdjacencyList(){
    ifstream inFile;
    int numFlightPaths;
    char* buffer;
    DSSTRING city1 = DSSTRING();
    DSSTRING city2 = DSSTRING();

    inFile.open(flightDataPath.c_str());
    if (inFile.is_open()){
        //finding the number of paths
        inFile >> numFlightPaths;

        //clearing the new line
        buffer = new char[20];
        inFile.getline(buffer, 2, '\n');
        delete[] buffer;

        //going through the list the number of paths long
        for (int i =0 ; i< numFlightPaths; i++){

            //creating city 1
            buffer = new char[20];
            inFile.getline(buffer, 19, '|');
            city1 = buffer;
            delete[] buffer;

            //creating city 2
            buffer = new char[20];
            inFile.getline(buffer, 19, '|');
            city2 = buffer;
            delete[] buffer;

            //creating cost
            buffer = new char[20];
            inFile.getline(buffer, 19, '|');
            int cost = convertToInt(buffer);
            delete[] buffer;

            //creating time
            buffer = new char[20];
            inFile.getline(buffer, 19, '|');
            int time = convertToInt(buffer);
            delete[] buffer;

            //creating airline
            buffer = new char[20];
            inFile.getline(buffer, 19, '\n');
            DSSTRING airline = buffer;
            delete[] buffer;

            //adding items to linklist
            flight f;
            flight g;
            f.setData(city1, city2, cost, time, airline);
            g.setData(city2, city1, cost, time, airline);
            flightList.pushFront(f);
            flightList.pushFront(g);

            //adding the elements to the adjacency list
            AJ.addElement(city1, city2);
        }
        //closing inFile
        inFile.close();
    }
}
void flightPlanner :: destination(){
    ifstream inFile;
    int numberOfPaths;
    DSSTRING origin = DSSTRING();
    DSSTRING destination = DSSTRING();
    char optimizationKey;
    char * buffer;

    inFile.open(flightRequestPath.c_str());
    if (inFile.is_open()){
        //finding the number of paths
        inFile >> numberOfPaths;

        //going to the next line
        buffer = new char[20];
        inFile.getline(buffer, 3, '\n');
        delete[] buffer;

        for (int i = 0; i < numberOfPaths; i++){
            //finding origin city
            buffer = new char[20];
            inFile.getline(buffer, 19, '|');
            origin = buffer;
            delete[] buffer;

            //finding destination city
            buffer = new char[20];
            inFile.getline(buffer, 19, '|');
            destination = buffer;
            delete[] buffer;

            //finding the optimization key
            inFile >> optimizationKey;

            //clearing next line
            buffer = new char[2];
            inFile.getline(buffer, 1, '\n');
            delete[] buffer;

            //solving
            solve(origin, destination, optimizationKey);
        }
    }
}
void flightPlanner :: calculateTimeAndHours(Stack<DSSTRING> stack){
    DSSTRING * airline = new DSSTRING[2];
    int counter = 0;
    totalCost = 0;
    totalHours = 0;
    DSSTRING city1;
    DSSTRING city2;
    while(!stack.isEmpty()){
        city1 = stack.pop();
        if (!stack.isEmpty())
            city2 = stack.pop();
        flightList.iteratorToHead();
        flight f = flightList.getIteratorData();
        while (f.getOrigin() != city1 || f.getDestination() != city2){
            flightList.stepForward();
            f = flightList.getIteratorData();
            airline[counter] = f.getAirline();
            counter = 1 - counter;
            if (!(airline[0].isEmpty()) && !(airline[1].isEmpty()) && airline[0] != airline[1]){
                totalCost += 19;
                totalHours += 43;
            }
        }
        totalCost += f.getCost();
        totalHours += f.getTime();
    }

}
void flightPlanner :: printStack(){
    ofstream outFile;
    int counter = 1;
    int pathCounter = 1;
    int tailCondition = 1;

    outFile.open(outputFilePath.c_str());
    if (outFile.is_open()){

        //getting the first stack
        listOfStacks.iteratorToHead();

        while(!(listOfStacks.isIteratorTail()) || tailCondition == 1){

           if (listOfStacks.isIteratorTail())
               tailCondition = 0;

           Stack<DSSTRING> s = Stack<DSSTRING>();
           Stack<DSSTRING> stackForCalculation = Stack<DSSTRING>();
           Stack<DSSTRING> reversedS = Stack<DSSTRING>();



            //creating the necessary stack objects
            s = listOfStacks.getIteratorData();
            stackForCalculation = s;

            //reversing the stack for printing
            DSSTRING Destination = s.pop();
            DSSTRING Origin;
            reversedS.push(Destination);
            while(!s.isEmpty()){
                Origin = s.pop();
                reversedS.push(Origin);
            }
            //printing the header for flight counter
            outFile << "Flight " << counter << ": " << Origin << ", " << Destination;
            if (optKey == 'T' || optKey == 't'){
                outFile << " (Time)" << endl;
            }
            else if (optKey == 'C' || optKey == 'c'){
                outFile << " (Cost)" << endl;
            }

            outFile << "Path " << pathCounter << ": ";
            while (reversedS.peek() != Destination)
                outFile << reversedS.pop() << " -> ";
            outFile << Destination << ". ";
            calculateTimeAndHours(stackForCalculation);
            outFile << "Time: " << totalHours << " Cost: " << totalCost << endl;
            outFile << endl;
            counter++;
            listOfStacks.stepForward();
        }
    }
}

