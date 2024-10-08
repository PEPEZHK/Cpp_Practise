//
// Created by perha on 10.05.2024.
//

#include "Cubicle.h"
#include <iostream>
#include <string>
void Cubicle::clear()
{

}
void Cubicle::add(Cubicle* ptr)
{
    if (!headPtr)
    {
        headPtr = ptr ;
        return ;
    }
    Cubicle* prev = nullptr ;
    Cubicle* cur = headPtr ;
    if (!headPtr->getNext())
    {
        if (headPtr->getID() > id)
        {
            ptr->setNext(headPtr) ;
            headPtr = ptr ;
        }
        else
            headPtr->setNext(ptr);
        genes++ ;
        std::cout << "Added gene " << id
                  << " to protein " << getID() << "."
                  << std::endl;
        return ;
    }
    while (cur && cur->getID() < id)
    {
        prev = cur ;
        cur = cur->getNext() ;
    }
    genes++ ;
    std::cout << "Added gene " << id
              << " to protein " << getID() << "."
              << std::endl;
    if (!prev)
    {
        ptr->setNext(headPtr);
        headPtr = ptr;
    } else
    {
        prev->setNext(ptr);
        ptr->setNext(cur);
    }
}
Cubicle* Cubicle::getNext()
{
    return  ;
}
void Cubicle::remove(Cubicle* ptr) {}
std::string Cubicle::listAdj() {}
Cubicle::Cubicle(int x , int y)
{
    setX(x) ;
    setY(y) ;
    headPtr = nullptr ;
}
Cubicle::~Cubicle()
{
    if (headPtr)
        clear() ;
}
int Cubicle::getX()
{
    return  x ;
}
int Cubicle::getY()
{
    return  y ;
}
void Cubicle::setX(const int x)
{
    this->x = x ;
}
void Cubicle::setY(const int y)
{
    this->y = y ;
}