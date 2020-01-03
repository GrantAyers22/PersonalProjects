#ifndef STACK_H
#define STACK_H
#include "node.h"
#include "dsstring.h"

template <class T>

class Stack{
private:
    llist<T> list;
    int size;

public:
    Stack(){
        list = llist<T>();
        size = 0;
    }
    void push(T val){
        list.pushFront(val);
        size++;
    }
    T pop(){
        size--;
        return list.pop();
    }

    bool isEmpty(){
        return (size == 0);
    }
    T peek(){
        return list.peek();
    }
    Stack& operator=(Stack<T>* listToEqual){
        list = listToEqual->list;
    }
};
#endif // STACK_H
