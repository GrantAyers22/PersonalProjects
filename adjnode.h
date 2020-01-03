#ifndef ADJNODE_H
#define ADJNODE_H
#include <iostream>
#include "node.h"
#include "dsstring.h"

template<class T>
class adjNode{
private:
    adjNode<T>* nextNode;
    adjNode<T>* lastNode;
    T firstElement;
    llist<T> list;
    template<typename U> friend class adjacencyList;
public:
    adjNode(){
        nextNode = nullptr;
        lastNode = nullptr;
    }
    adjNode& operator=(adjNode<T>* NodeToEqual){
        lastNode = NodeToEqual->lastNode;
        nextNode = NodeToEqual->nextNode;
        firstElement = NodeToEqual->firstElement;
        list = NodeToEqual->list;

    }

};

template <class T>
class adjacencyList{
private:
    adjNode<T>* headList;
    adjNode<T>* tailList;
    adjNode<T>* iterator;

public:   
    adjacencyList(){
        headList = nullptr;
        tailList = nullptr;
        iterator = nullptr;
    }

    void iteratorToHead(){
        iterator = new adjNode<T>();
        iterator = headList;
    }

    void stepForward(){
        iterator = iterator->nextNode;
    }

    void stepBackwards(){
        iterator = iterator ->lastNode;
    }

    llist<T> getIteratorData(){
        return iterator->list;
    }

    T getIteratorHead(){
        return iterator->firstElement;
    }

    void addElement(T element1, T element2){
        if (headList == nullptr){
            //initializing headList
            headList = new adjNode<T>();
            llist<T> tempList1;
            tempList1.pushFront(element1);
            tempList1.pushBack(element2);
            headList->list = tempList1;
            headList->firstElement = element1;


            //creating a newHeadList
            adjNode<T>* newHeadList = new adjNode<T>();
            adjNode<T>* tempHeadList = headList;

            llist<T> tempList2;
            tempList2.pushFront(element2);
            tempList2.pushBack(element1);

            newHeadList->nextNode = tempHeadList;
            newHeadList->list = tempList2;
            newHeadList->firstElement = element2;

            headList = newHeadList;

            //linking lists
            tempHeadList->lastNode = headList;
            tailList = tempHeadList;
        }
        else if (headList != nullptr){
            if (outerExists(element1)){
                //creating a temporary head
                adjNode<T>* tempHead = headList;

                //navigating to the correct node
                while (tempHead->firstElement != element1)
                    tempHead = tempHead->nextNode;
                llist<T> tempHeadList = tempHead->list;
                tempHeadList.pushBack(element2);
                tempHead->list = tempHeadList;
            }

            if (outerExists(element2)){
                //creating a temporary head
                adjNode<T>* tempHead = headList;

                //navigating to the correct node
                while (tempHead->firstElement != element2)
                    tempHead = tempHead->nextNode;
                llist<T> tempHeadList = tempHead->list;
                tempHeadList.pushBack(element1);
                tempHead->list = tempHeadList;
            }

            if (!outerExists(element1)){
                //creating a temporary head
                adjNode<T>* tempHead = headList;

                //creating a new node
                adjNode<T>* newNode = new adjNode<T>();
                newNode->firstElement = element1;

                //creating new nodes list
                llist<T> newNodeList;
                newNodeList.pushFront(element1);
                newNodeList.pushBack(element2);
                newNode->list = newNodeList;

                newNode->nextNode = tempHead;
                headList = newNode;
                tempHead->lastNode = headList;
            }

            if (!outerExists(element2)){
                //creating a temporary head
                adjNode<T>* tempHead = headList;

                //creating a new node
                adjNode<T>* newNode = new adjNode<T>();
                newNode->firstElement = element2;

                //creating new nodes list
                llist<T> newNodeList;
                newNodeList.pushFront(element2);
                newNodeList.pushBack(element1);
                newNode->list = newNodeList;

                newNode->nextNode = tempHead;
                headList = newNode;
                tempHead->lastNode = headList;
            }
        }
    }

    bool outerExists(T val){
        adjNode<T>* tempHead = headList;
        while (tempHead != nullptr){
            if (tempHead->firstElement == val)
                return true;
            tempHead = tempHead->nextNode;
        }
        return false;
    }
};
#endif // ADJNODE_H
