//
// Created by perha on 10.05.2024.
//

#include "Stack.h"
#include <iostream>
Stack::Stack()
{
    top = nullptr ;
}
void Stack::push(std::string data)
{
    Node* temp = new Node(data) ;
    if (!top) {
        top = temp ;
        return ;
    }
    temp->setNext(top) ;
    top = temp;
}
bool Stack::isEmpty()
{
    return  top == nullptr ;
}
std::string Stack::peek()
{
    if (!isEmpty())
        return top->getData();
    else
        return  "" ;
}
std::string Stack::pop()
{
    std::string data ;
    Node* temp ;
    if (!top)
        return "" ;
    temp = top ;
    data = temp->getData() ;
    top = top->getNext() ;
    delete temp ;
    return data ;
}
int Stack::getX()
{
    if (!isEmpty())
    {
        std::string data = peek() ;
        int size = data.find_first_of(',') ;
        std::string xx = data.substr(0,size) ;
        int x = std::stoi(xx) ;
        return x ;
    }
    return 0 ;
}
int Stack::getY()
{
    if (!isEmpty())
    {
        std::string data = peek() ;
        int size = data.find_first_of(',') ;
        int size1 = data.size() ;
        std::string yy = data.substr(size+1,size1) ;
        int y = std::stoi(yy) ;
        return y ;
    }
    return 0 ;
}
void Stack::display()
{
    Node* cur = top ;
    std::string to_print = "" ;
    int c = 0 ;
    while(cur)
    {
        to_print = "("+cur->getData()+")" + " -> " + to_print ;
        c++ ;
        cur = cur->getNext() ;
    }
    if (c > 0)
        to_print = to_print.substr(0 , to_print.size() - 4) ;
    else
        to_print = "None" ;
    std::cout << to_print << std::endl ;
}
Stack::~Stack()
{
    if (top)
        while(!top)
            pop() ;
}