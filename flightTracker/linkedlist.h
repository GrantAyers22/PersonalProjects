#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include "node.h"
template <class T>
class LinkedList{
public:
    LinkedList(){
        head = nullptr;
        tail = nullptr;
    }

    void pushFront(T val){
        Node<T>* tempNode = new Node<T>(val);
        if (head == nullptr)
            head = tempNode;
        if(tail == nullptr)
            tail = tempNode;

    }

    void printNodes(){
        Node<T>* temp = head;
        while (head != nullptr){
            std::cout << temp-> data << std::endl;
            temp = temp->nextNode;
        }

    }

private:
    Node<T>* head;
    Node<T>* tail;

};

#endif // LINKEDLIST_H
