#include "catch.hpp"
#include "node.h"
#include "stack.h"
#include "dsstring.h"
#include "flightplanner.h"
#include "adjnode.h"

using namespace std;

TEST_CASE("Linked list"){
    SECTION("push front"){
        llist<DSSTRING> a = llist<DSSTRING>();
        DSSTRING abc = "abc";
        DSSTRING def = "def";
        DSSTRING ghi = "ghi";
        a.pushFront(abc);
        a.pushFront(def);
        a.pushFront(ghi);
        a.iteratorToHead();
        REQUIRE ((a.getIteratorData() == ghi) == true);
        a.stepForward();
        REQUIRE ((a.getIteratorData() == def) == true);
        a.stepForward();
        REQUIRE ((a.getIteratorData() == abc) == true);
    }

    SECTION("push back"){
        llist<DSSTRING> a = llist<DSSTRING>();
        DSSTRING abc = "abc";
        DSSTRING def = "def";
        DSSTRING ghi = "ghi";
        a.pushBack(abc);
        a.pushBack(def);
        a.pushBack(ghi);
        a.iteratorToTail();
        REQUIRE ((a.getIteratorData() == ghi) == true);
        a.stepBackwards();
        REQUIRE ((a.getIteratorData() == def) == true);
        a.stepBackwards();
        REQUIRE ((a.getIteratorData() == abc) == true);
    }
}

TEST_CASE("Stack tests"){
    SECTION("push, pop, isempty"){
        Stack<DSSTRING> stacker = Stack<DSSTRING>();
        DSSTRING abc = "abc";
        DSSTRING def = "def";
        DSSTRING ghi = "ghi";

        stacker.push(abc);
        stacker.push(def);
        stacker.push(ghi);


        REQUIRE ((stacker.pop() == ghi) == true);
        REQUIRE ((stacker.peek() == def) == true);
        REQUIRE ((stacker.pop() == def) == true);
        REQUIRE (stacker.isEmpty() == false);
        REQUIRE ((stacker.pop() == abc) == true);
    }

}
TEST_CASE("Adjacency list tests"){
    SECTION("3x3 graph"){
        //declaring data
        adjacencyList<DSSTRING> aj;
        DSSTRING abc = "abc";
        DSSTRING def = "def";
        DSSTRING ghi = "ghi";

        //adding elements to the graph
        aj.addElement(abc, def);
        aj.addElement(def, ghi);
        aj.addElement(abc, ghi);
        aj.iteratorToHead();

        //creating the sublist
        llist<DSSTRING> list = aj.getIteratorData();

        //testing the first row of the graph
            //setting the list iterator
            list.iteratorToHead();
            REQUIRE ((list.getIteratorData() == ghi) == true);
            //moving to the right one
            list.stepForward();
            REQUIRE ((list.getIteratorData() == def) == true);
            //moving to the right one
            list.stepForward();
            REQUIRE ((list.getIteratorData() == abc) == true);

        //iterating one down in the graph
        aj.stepForward();

        //testing the second row of the graph
            //setting the list iterator
            list = aj.getIteratorData();
            list.iteratorToHead();
            REQUIRE ((list.getIteratorData() == def) == true);
            //moving to the right one
            list.stepForward();
            REQUIRE ((list.getIteratorData() == abc) == true);
            //moving to the right one
            list.stepForward();
            REQUIRE ((list.getIteratorData() == ghi) == true);

        //iterating one down in the graph
        aj.stepForward();

        //testing the third row of the graph
            //setting the list iterator
            list = aj.getIteratorData();
            list.iteratorToHead();
            REQUIRE ((list.getIteratorData() == abc) == true);
            //moving to the right one
            list.stepForward();
            REQUIRE ((list.getIteratorData() == def) == true);
            //moving to the right one
            list.stepForward();
            REQUIRE ((list.getIteratorData() == ghi) == true);
    }
}

