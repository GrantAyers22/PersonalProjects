#include "flight.h"
#include "dsstring.h"

flight::flight(){

}
void flight:: setData(DSSTRING oCity, DSSTRING dCity, int c, int t, DSSTRING a){
    origin = oCity;
    destination = dCity;
    cost = c;
    time = t;
    airline = a;
}
DSSTRING flight :: getOrigin(){
    return origin;
}
DSSTRING flight :: getDestination(){
    return destination;
}
int flight :: getCost(){
    return cost;
}
int flight ::  getTime(){
    return time;
}
DSSTRING flight :: getAirline(){
    return airline;
}
flight& flight:: operator=(flight* f){
    origin = f->origin;
    destination = f->destination;
    cost = f->cost;
    time = f->time;
    airline = f->airline;
}
