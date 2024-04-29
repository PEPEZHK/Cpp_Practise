// sec1-Perhat-Amanlyyev-22201007
#include <iostream>
#include "Pathway.h"
Pathway::Pathway() 
{
    headPtr = nullptr ;
    next = nullptr ;
}
Pathway::Pathway(const int ID , const std::string name)
{
    this->ID = ID ;
    this->name = name ;
    headPtr = nullptr ;
    next = nullptr ;
    prots = 0 ;
    genes = 0 ;
}
void Pathway::add(const int id) 
{
    protein* ptr = new protein(id) ;
    if (!headPtr)
    {
        headPtr = ptr ;
        prots++ ;
        std::cout << "Added protein " << id
                  << " to pathway " << getID() << "."
                  << std::endl;
    }
    else
    {
        protein* prev = nullptr ;
        protein* cur = headPtr ;
        if (!headPtr->getNext())
        {
            if (headPtr->getID() > id)
            {
                ptr->setNext(headPtr) ;
                headPtr = ptr ;
            }
            else
            {
                headPtr->setNext(ptr);
            }
            prots++ ;
            std::cout << "Added protein " << id
                      << " to pathway " << getID() << "."
                      << std::endl;
            return ;
        }
        while (cur && cur->getID() < id)
        {
            prev = cur ;
            cur = cur->getNext() ;
        }
        std::cout << "Added protein " << id
                  << " to pathway " << getID() << "."
                  << std::endl;
        prots++ ;
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
}
void Pathway::remove(const int id_to_remove) 
{
    if (headPtr->getID() == id_to_remove)
    {
        protein* cur = headPtr ;
        headPtr = cur->getNext() ;
        prots-- ;
        delete cur ;
        std::cout<< "Removed protein " << id_to_remove <<
                 " from pathway " << getID() << "." <<
                 std::endl ;
        return ;
    }
    protein* to_delete = getAt(id_to_remove) ;
    if (!to_delete)
    {
        std::cout<< "Cannot remove protein. Pathway " << getID() << " does not have a protein with ID " << id_to_remove << "." <<
                    std::endl ; 
        return ;
    }
    prots-- ;
    protein* cur = to_delete->getNext() ;
    to_delete->setNext(cur->getNext()) ;
    delete cur ;
    std::cout<< "Removed protein " << id_to_remove << 
                " from pathway " << getID() << "." <<  
                std::endl ;
}
protein* Pathway::getAt(const int id)
{
    protein* cur = headPtr ;
    protein* to_return = cur ;
    while (cur != nullptr)
    {
        if (cur->getID() == id)
        {
            return to_return ;
        }
        else
        {
            to_return = cur ;
            cur = cur->getNext() ;
        }
    }
    return nullptr ;
}
int Pathway::getID() 
{
    return ID ;
}
void Pathway::print() 
{
    if (!headPtr)
    {
        std::cout << "There are no proteins to show in pathway " << getID() << "." <<std::endl ;
    }
    else
    {
        std::cout << "Proteins in pathway " << getID() << ":" << std::endl ;
        protein* cur = headPtr ;
        while (cur != nullptr) 
        {
            std::cout << "Protein ID : " << cur->getID() << ", Gene IDs : " <<
                         (*cur).listGenes() << std::endl ;
            cur = cur->getNext() ;
        }  
    }
}

void Pathway::toString() 
{
    std::cout << "Pathway " << getID() << " : " << getName() << " (" 
                            << prots << " Proteins) (" 
                            << amountOfGenes() << " Genes)" << std::endl ;
}

void Pathway::clear()
{
    while (headPtr)
    {
        protein* cur = headPtr ;
        headPtr = cur->getNext() ;
        delete cur ;
    }
}
int Pathway::amountOfGenes() 
{
    if (!headPtr)
        return 0 ;
    protein*cur = headPtr ;
    int c = 0 ;
    while (cur != nullptr) 
    {
        c += cur->getGenes() ;
        cur = cur->getNext() ;
    }
    return c ;
}

std::string Pathway::getName()
{
    return  name ;
}

Pathway* Pathway::getNext()
{
    return  next ;
}

void Pathway::setNext(Pathway* next)
{
    this->next = next ;
}

bool Pathway::containsGene(const int id)
{
    if (!headPtr)
        return false ;
    protein* cur = headPtr ;
    while (cur != nullptr)
    {
        if (cur->getAt(id))
            return  true ;
        cur = cur->getNext() ;
    }
    return false ;
}

protein* Pathway::place_to_(const int id)
{
    protein* cur = headPtr ;
    while (cur != nullptr)
    {
        if (cur->getID() == id)
        {
            return cur ;
        }
        cur = cur->getNext() ;
    }
    return nullptr ;
}
Pathway::~Pathway()
{
    if(headPtr)
        clear() ;
}
