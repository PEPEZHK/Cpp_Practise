//
// Created by perha on 10.05.2024.
//

#ifndef C_CUBICLE_H
#define C_CUBICLE_H
#include <string>
class Cubicle{
public:
    void clear() ;
    void add(Cubicle* ptr) ;
    void remove(Cubicle* ptr) ;
    std::string listAdj() ;
    Cubicle(int x , int y) ;
    ~Cubicle() ;
    int getX() ;
    int getY() ;
    void setX(const int x) ;
    void setY(const int y) ;
    Cubicle* getNext() ;
private:
    Cubicle* headPtr ;
    Cubicle* next ;
    int x ;
    int y ;
};
#endif //C_CUBICLE_H
