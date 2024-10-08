#ifndef C_BUILDINGMAP_H
#define C_BUILDINGMAP_H
#include <string>
#include "Stack.h"
class BuildingMap{
public:
BuildingMap(const std::string buildingMapFile);
~BuildingMap();
void displayAllCubicles()const;
void displayAdjacentCubicles(const int row,const int col)const;
void displayBuildingMap()const;
void findPaths(const int startRow,const int startCol,const int endRow,const int endCol);
void findPaths(const int startRow,const int startCol,const int endRow,const int endCol,
        const int avoidRow,const int avoidCol);
void setH(const int h) ;
void setW(const int w) ;
int  getH() const;
int  getW() const;
void show() ;
private:
    void wentTo(int x , int y ,int xx , int yy , bool value) ;
    bool backtracked ;
    bool noPath ;
    void clearW(int x , int y) ;
    bool give(int x , int y ,int xx , int yy) ;
    void createPaths() const;
    void toString() const ;
    bool** went ;
    bool** visited ;
    bool** arr ;
    int** indexes ;
    int h ;
    int w ;
    void add_edge(const int x ,const int y) const ;
    void init(const std::string link) ;
    bool contJustOne(int x , int y , int erow , int ecol) ;
    void rmv(std::string& str , std::string& index) ;
    void rmv(Stack& s) ;
    int count(int x) ;
    bool contJustOne(int x , int y) ;
    void clear(int x , int y) ;
    int to_int(std::string data , std::string index) ;
    std::string getnext(int x , int y) ;
    bool diffPaths(int x , int y , Stack& s , int erow , int ecol) ;
} ;

#include "BuildingMap.cpp"
#endif
