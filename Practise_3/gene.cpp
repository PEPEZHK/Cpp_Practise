// sec1-Perhat-Amanlyyev-22201007
#include "gene.h"
gene::gene() : next(nullptr) {} 

gene::gene(const int ID , const std::string& name)
{
    this->name = name ; 
    this->ID = ID ;
    next = nullptr ; 
}
int gene::getID() const 
{
    return ID ;
}
std::string gene::getName() const 
{
    return name ;
} 
gene* gene::getNext() const 
{
    return next ;
}
gene::~gene(){}
void gene::setNext(gene* next) 
{
    this->next = next ;
}