// sec1-Perhat-Amanlyyev-22201007
#include "protein.h"
#include <iostream>
protein::protein() 
{
    headPtr = nullptr ;
    next = nullptr ;
}
protein::protein(const int ID) 
{
    this->ID = ID ;
    headPtr = nullptr ;
    next = nullptr ;
    genes = 0 ;
}
void protein::add(const int id , const std::string& name)
{
    gene* ptr = new gene(id , name) ;
    if (!headPtr)
    {
        headPtr = ptr ;
        genes++ ;
        std::cout << "Added gene " << id
                  << " to protein " << getID() << "."
                  << std::endl;
    }
    else
    {
        gene* prev = nullptr ;
        gene* cur = headPtr ;
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
}
void protein::remove(const int id_to_remove) 
{
    gene* to_delete = getAt(id_to_remove) ;
    if (!to_delete)
    {
        std::cout<< "Cannot remove gene. There is no gene " << id_to_remove << 
                    " encoding protein " << getID() << "." << 
                    std::endl ; 
        return ;
    }
    if (headPtr->getID()==id_to_remove)
    {
        headPtr = to_delete->getNext() ;
        delete to_delete ;
    }
    else
    {
        gene* cur = to_delete->getNext() ;
        gene* prev = to_delete;
        prev->setNext(cur->getNext()) ;
        delete cur ;
    }
    genes-- ;
    std::cout<< "Removed gene " << id_to_remove << 
                " from protein " << getID() << "." << 
                std::endl ;
}
void protein::print() 
{
    if (!headPtr)
    {
        std::cout << "There are no genes to show in protein " << getID() << "." << std::endl ; 
    }
    else 
    {
        gene* cur = headPtr ;
        std::cout << "Genes in protein " << getID() <<":" << std::endl ;
        while (cur != nullptr) 
        {
            std::cout << "GENE " << cur->getID() << " : " << 
                      cur->getName() << std::endl ; 
            cur = cur->getNext() ;
        }  
    }
}
int protein::getID() const 
{
    return ID ;
}
int protein::getGenes() const
{
    return genes ;
}
protein* protein::getNext() const 
{
    return next ;
}
gene* protein::getAt(const int id) 
{
    gene* cur = headPtr ;
    gene* to_return = cur ;
    while (cur != nullptr)
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
std::string protein::listGenes() 
{
    if (!headPtr)
        return  "None" ;
    std::string str = "[";
    gene* cur = headPtr ;
    while (cur != nullptr) 
    {
        if (!cur->getNext())
            str += std::to_string(cur->getID()) + "]" ;
        else 
            str += std::to_string(cur->getID()) + ", " ;
        cur = cur->getNext() ;
    }
    return str ;
}
void protein::clear() 
{
    while (headPtr)
    {
        gene* cur = headPtr ;
        headPtr = cur->getNext() ;
        delete cur ;
    }
}
void protein::setNext(protein* next) 
{
    this->next = next ;
}
protein::~protein()
{
    if (headPtr)
        clear() ;
}
