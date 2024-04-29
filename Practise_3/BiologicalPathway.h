// sec1-Perhat-Amanlyyev-22201007
#ifndef C_BIOLOGICALPATHWAY_H
#define C_BIOLOGICALPATHWAY_H
#include <string>
#include "Pathway.h"
class BiologicalPathway {
    private:
    Pathway* headPtr ;
    Pathway* next ;
    public:
    Pathway* getNext() ;
    void clear() ;
    void setNext(Pathway* next) ;
    Pathway* getAt(const int id) const;
    BiologicalPathway();
    ~BiologicalPathway();
    void addPathway( const int pathwayId, const std::string pathwayName );
    void removePathway( const int pathwayId ) ;
    void printPathways() const;
    void addProtein( const int proteinId, const int pathwayId );
    void removeProtein( const int proteinId, const int pathwayId );
    void printProteinsInPathway( const int pathwayId ) const;
    void addGene( const int geneID, const std::string geneName, const int proteinId );
    void removeGene( const int geneID, const int proteinId );
    void printGenesOfProtein( const int proteinId ) const;
};
#endif
