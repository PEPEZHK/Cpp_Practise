//
// Created by perha on 10.05.2024.
//

#ifndef C_STACK_H
#define C_STACK_H
#include "Node.h"
#include <string>
class Stack {

public:
    Stack() ;
    void push(std::string data) ;
    bool isEmpty() ;
    std::string peek() ;
    std::string pop() ;
    void display() ;
    int getX() ;
    int getY() ;
    ~Stack() ;
private:
    Node* top;
};
#include "Stack.cpp"
#endif //C_STACK_H
