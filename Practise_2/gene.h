#ifndef C_GENE_H
#define C_GENE_H
#include <string>
class gene
{
private:
    int ID ;
    std::string name ;
    gene* next ;
public:
    gene* getNext() const ;
    void setNext(gene* next) ;
    int getID() const ;
    std::string getName() const ;
    gene();
    gene(const int ID , const std::string& name) ;
    ~gene();
};
#endif
