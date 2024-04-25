#ifndef C_PATHWAY_H
#define C_PATHWAY_H
#include "protein.h"
class Pathway
{
private:
    int ID ;
    std::string name ;
    protein* headPtr ;
    Pathway* next ;
    int prots ; 
    int genes ;
public:
    bool containsGene(const int id) ;
    int amountOfGenes() ;
    protein* place_to_(const int id) ;
    protein* getAt(const int id) ;
    Pathway* getNext() ;
    void setNext(Pathway* next) ;
    void clear() ;
    Pathway() ;
    Pathway(const int ID , const std::string name) ;
    void add(const int id) ;
    void remove(const int id_to_remove) ;
    void print() ;
    void toString() ;
    int getID() ;
    std::string getName() ;
    ~Pathway();
};
#endif
