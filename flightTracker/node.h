#ifndef NODE_H
#define NODE_H
#include <iostream>
#include "dsstring.h"
#include "flight.h"

template<class T>
class Node {
private:
    Node<T>* nextNode;
    Node<T>* lastNode;
    template<typename U> friend class llist;
    T data;

public:
    Node(){
        nextNode = nullptr;
        lastNode = nullptr;
    }
    Node(T val){
        data = val;
        nextNode = nullptr;
        lastNode = nullptr;

    }
    Node(const Node<T>& d){
        nextNode = d.nextNode;
        lastNode = d.lastNode;
        data = d.data;
    }

    Node& operator=(Node<T>* NodeToEqual){
        lastNode = NodeToEqual->lastNode;
        nextNode = NodeToEqual->nextNode;
        data = NodeToEqual->data;
    }
    bool operator==(Node<T>* NodeToCheck){
        if (lastNode == NodeToCheck->lastNode && nextNode == NodeToCheck->nextNode && data == NodeToCheck->data){
            return true;
        }
        return false;
    }
};

template <class T>
class llist{
private:
    Node<T>* head;
    Node<T>* tail;
    Node<T>* iterator;
public:
    llist(){
        head = nullptr;
        tail = nullptr;
        iterator = nullptr;
    }
    llist& operator=(llist<T>* listToEqual){
        if (head != nullptr){
            delete head;
        }
        if (tail != nullptr){
            delete tail;
        }
        if (iterator != nullptr){
            delete iterator;
        }
        head = listToEqual->head;
        tail = listToEqual->tail;
        Node<T>* tempTail = tail;
        while (tempTail->lastNode != nullptr){
            pushFront(tempTail->data);
            tempTail = tempTail->lastNode;
        }
    }
    void updateHead(){
        Node<T>* tempHead = tail;
        while(tempHead->lastNode != nullptr){
            tempHead = tempHead->lastNode;
        }
        head = tempHead;
    }

    void updateTail(){
        Node<T>* tempTail = head;
        while (tempTail->nextNode != nullptr){
            tempTail = tempTail->nextNode;
        }
        tail = tempTail;
    }

    void pushFront(T val){
        //if head doesn't exist
        if (head == nullptr){
            //making head exist
            head = new Node<T>(val);
        }
        else if (head != nullptr){

            //creating a new head
            Node<T>* newHead = new Node<T>(val);

            //creating a node to store all of head's data
            Node<T>* tempHead = head;

            //setting the new head's next node to the old head
            newHead->nextNode = tempHead;

            //setting the head to the new head
            head = newHead;

            //changing the lastnode of the temp head equal to the new head
            tempHead->lastNode = head;
        }

        //update tail
        updateTail();
    }

    void pushBack(T val){
        //if tail doesn't exist
        if(tail == nullptr){
            //making tail exist
            tail = new Node<T>(val);
        }
        else if (tail != nullptr){
           //creating a new tail
            Node<T>* newTail = new Node<T>(val);

            //creating a node to store all of tail's data
            Node<T>* tempTail = tail;

            //changing the next node of the temporary tail to equal the new tail
            tempTail->nextNode = newTail;

            //setting the new tail's last node to equal the old head
            newTail->lastNode = tempTail;
            newTail->nextNode = nullptr;

            //setting the tail to the new tail
            tail = newTail;
        }
        //update head
        updateHead();
    }
    T pop(){
        T headData = head -> data;
        if (head->nextNode == nullptr){
            head = nullptr;
        }
        else {
            head = head ->nextNode;
            head -> lastNode = nullptr;
        }
        return headData;
    }
    T peek(){
        return head->data;
    }
    void iteratorToHead(){
        if (head != nullptr){
            iterator = head;
        }
    }
    void stepForward(){
        if (iterator->nextNode != nullptr){
            iterator = iterator->nextNode;
        }
    }
    void stepBackwards(){
        if (iterator->lastNode != nullptr){
            iterator = iterator->lastNode;
        }
    }
    void iteratorToTail(){
        if (tail != nullptr){
            iterator = tail;
        }
    }
    T getIteratorData(){
        T a;
        if (iterator!=nullptr){
            return iterator->data;
        }

        else{
            return a;
        }
    }

    bool isIteratorTail(){
        return (iterator == tail);
    }


};

#endif // NODE_H
