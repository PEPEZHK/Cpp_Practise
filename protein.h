// sec1-Perhat-Amanlyyev-22201007
#ifndef C_PROTEIN_H
#define C_PROTEIN_H
#include <string>
#include "gene.h"
class protein
{
private:
    int ID ;
    gene* getAt(int pos) const ;
    gene* headPtr ;
    protein* next ;
    int genes ;
public:
    int getGenes() const ;
    void clear() ;
    protein* getNext() const ;
    std::string listGenes() ;
    void setNext(protein* next) ;
    gene* getAt(const int id) ;
    protein();
    protein(const int ID) ;
    void add(const int id , const std::string& name) ;
    void remove(const int id_to_remove) ;
    void print() ;
    int getID() const ;
    ~protein();
};
#endif
