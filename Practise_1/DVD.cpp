#include "DVD.h"
#include <string>
#include <iostream>
DVD::DVD(const std::string serialNo, const std::string title, const std::string director)
{
    setAvailability(true) ;
    setDirector(director) ;
    setNo(serialNo) ;
    setTitle(title) ;
}
DVD::~DVD(){}
std::string DVD::getNo()
{
    return  no ;
}
std::string DVD::getDir()
{
    return  dir ;
}
std::string DVD::getTitle()
{
    return  title ;
}
bool  DVD::isAvailable()
{
    return  available ;
}
void DVD::setTitle(const std::string title)
{
    this->title = title ;
}
void DVD::setNo(const std::string serialNo)
{
    this->no = serialNo ;
}
void DVD::setDirector(const std::string director)
{
    dir = director ;
}
void DVD::setAvailability(const bool state)
{
    available = state ;
}

void DVD::toString()
{
    std::string state ;
    if (available)
        state = "Available" ;
    else
        state = "Rented" ;
    std::cout << "DVD: " << no <<
              ", Title: " << title <<
              ", Director: " << dir <<
              ", " << state << std::endl ;
}

DVD::DVD() {
    setAvailability(false) ;
    setDirector("") ;
    setNo("") ;
    setTitle("") ;
}
