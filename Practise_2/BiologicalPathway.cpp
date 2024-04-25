#include "BiologicalPathway.h"
#include <iostream>
#include <string>
BiologicalPathway::BiologicalPathway()
{
    headPtr = nullptr ;
    next = nullptr ;
}
BiologicalPathway::~BiologicalPathway()
{
    if (headPtr)
        clear() ;
}
void BiologicalPathway::addPathway( const int pathwayId, const std::string pathwayName )
{
    Pathway* ptr = new Pathway(pathwayId , pathwayName) ;
    if (!headPtr)
    {
        headPtr = ptr ;
        std::cout << "Added pathway " << pathwayId << "."
                  << std::endl;
    }
    else
    {
        if (getAt(pathwayId))
        {
            std::cout << "Cannot add pathway. There is already a pathway with ID "
                      << pathwayId << "." << std::endl ;
            delete ptr ;
        }
        else
        {
            Pathway* prev = nullptr ;
            Pathway* cur = headPtr ;
            if (!headPtr->getNext())
            {
                if (headPtr->getID() > pathwayId)
                {
                    ptr->setNext(headPtr) ;
                    headPtr = ptr ;
                }
                else
                {
                    headPtr->setNext(ptr);
                }
                std::cout << "Added pathway " << pathwayId << "."
                          << std::endl;
                return ;
            }
            while (cur && cur->getID() < pathwayId)
            {
                prev = cur ;
                cur = cur->getNext() ;
            }
            std::cout << "Added pathway " << pathwayId << "."
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
    }
}
void BiologicalPathway::removePathway( const int pathwayId )
{
    Pathway* to_delete = getAt(pathwayId) ;
    if (!to_delete || !headPtr)
    {
        std::cout<< "Cannot remove pathway. There is no pathway with ID " << pathwayId << "." <<
                    std::endl ; 
        return ;
    }
    if (headPtr->getID() == pathwayId)
    {
        headPtr = headPtr->getNext() ;
        delete to_delete ;
        std::cout<< "Removed pathway " << pathwayId << "." <<
                 std::endl ;
        return ;
    }
    Pathway* cur = to_delete->getNext() ;
    to_delete->setNext(cur->getNext()) ;
    delete cur ;
    std::cout<< "Removed pathway " << pathwayId << "." <<
                std::endl ;
}
void BiologicalPathway::printPathways() const
{
    if (!headPtr)
    {
        std::cout << "There are no pathways to show." << std::endl ;
        return ;
    }
    Pathway* cur = headPtr ;
    std::cout << "Pathways in the system:" << std::endl ;
    while (cur != nullptr)
    {
        cur->toString() ;
        cur = cur->getNext() ;
    }
}
void BiologicalPathway::addProtein( const int proteinId, const int pathwayId )
{
    Pathway* to_pathway = getAt(pathwayId) ;
    if (!to_pathway)
    {
        std::cout << "Cannot add protein. There is no pathway with ID " 
                  << pathwayId << "." << std::endl ;
        return ;
    }
    Pathway* cur = headPtr ;
    while (cur != nullptr)
    {
        if (cur->getAt(proteinId))
        {
            std::cout << "Cannot add protein. There is a pathway having a protein with ID "
                      << proteinId << "."  << std::endl ;
            return ;
        }
        cur = cur->getNext() ;
    }
    if (to_pathway->getID() == headPtr->getID() && headPtr->getID() == pathwayId)
        to_pathway->add(proteinId) ;
    else
        to_pathway->getNext()->add(proteinId) ;

}
void BiologicalPathway::removeProtein( const int proteinId, const int pathwayId )
{
    if (headPtr->getID() == pathwayId)
    {
        headPtr->remove(proteinId) ;
        return ;
    }
    Pathway* to_pathway = getAt(pathwayId) ;
    if (!to_pathway)
    {
        std::cout << "Cannot remove protein. There is no pathway with ID " 
                  << pathwayId << "." << std::endl ;
        return ;
    }
    to_pathway->getNext()->remove(proteinId) ;
}
void BiologicalPathway::printProteinsInPathway( const int pathwayId ) const
{
    if (!headPtr)
    {
        std::cout << "Cannot print proteins. There is no pathway with ID "
                  << pathwayId << "." << std::endl ;
        return ;
    }
    if (headPtr->getID() == pathwayId)
    {
        headPtr->print() ;
        return ;
    }
    Pathway* to_print = getAt(pathwayId) ;
    if (!to_print)
    {
        std::cout << "Cannot print proteins. There is no pathway with ID "
                 << pathwayId << "." << std::endl ;
        return ;
    }
    to_print->getNext()->print() ;
}
void BiologicalPathway::addGene( const int geneID, const std::string geneName, const int proteinId )
{
    Pathway* cur = headPtr ;
    while (cur)
    {
        if (cur->containsGene(geneID))
        {
           std::cout << "Cannot add gene. Gene " << geneID
                      << " is already in use." << std::endl;
            return ;
        }
        cur = cur->getNext() ;
    }
    protein* to_check = nullptr ;
    cur = headPtr ;
    while (cur && !to_check)
    {
        to_check = cur->place_to_(proteinId) ;
        cur = cur->getNext() ;
    }
    if (!to_check)
        std::cout << "Cannot add gene. There is no protein with ID "
                 << proteinId << "." << std::endl ;
    else
    {
        to_check->add(geneID , geneName) ;
    }
}
void BiologicalPathway::removeGene( const int geneID, const int proteinId )
{
    Pathway* cur = headPtr ;
    protein* to_check = nullptr ;
    while (cur && !to_check)
    {
        to_check = cur->place_to_(proteinId) ;
        cur = cur->getNext() ;
    }
    if (!to_check)
        std::cout << "Cannot remove gene. There is no protein with ID "
                  << proteinId << "." << std::endl ;
    else
    {
        to_check->remove(geneID) ;
    }
}
void BiologicalPathway::printGenesOfProtein( const int proteinId ) const
{
    Pathway* cur = headPtr ;
    protein* to_check = nullptr ;
    while (cur != nullptr && !to_check)
    {
        to_check = cur->place_to_(proteinId) ;
        cur = cur->getNext() ;
    }
    if (!to_check)
        std::cout << "Cannot print genes. There is no protein with ID "
                  << proteinId << "." << std::endl ;
    else
    {
        to_check->print() ;
    }
}

Pathway* BiologicalPathway::getAt(const int id) const
{
    Pathway* cur = headPtr ;
    Pathway* to_return = headPtr ;
    while (cur)
    {
        if (cur->getID() == id)
        {
            return to_return ;
        }
        to_return = cur ;
        cur = cur->getNext() ;
    }
    return nullptr ;
}

void BiologicalPathway::setNext(Pathway* next)
{
    this->next = next ;
}

void BiologicalPathway::clear()
{
    while (headPtr)
    {
        Pathway* cur = headPtr ;
        headPtr = cur->getNext() ;
        delete cur ;
    }
}

Pathway* BiologicalPathway::getNext() 
{
    return next ;
}
