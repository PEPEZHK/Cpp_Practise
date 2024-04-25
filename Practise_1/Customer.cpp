#include "Customer.h"
#include <string>
#include <iostream>
Customer::Customer(const int customerID, const std::string name)
{
    setID(customerID) ;
    setUser(name) ;
    rentedDVDs = 0 ;
    customer_dvd = new std::string[rentedDVDs] ;
}
Customer::~Customer(){}
int Customer::getRents()
{
    return  rentedDVDs ;
}
int Customer::getID()
{
    return  ID_Number ;
}
std::string Customer::getName()
{
    return  Username ;
}
std::string* Customer::getRentedDVDs()
{
    return  customer_dvd ;
}
void Customer::setUser(const std::string name)
{
    Username = name ;
}
void Customer::setID(const int customerID)
{
    ID_Number = customerID ;
}

void Customer::toString()
{
    std::cout << "Customer: " << ID_Number
              << ", Name: "     << Username
              << ", DVDs Rented: " << rentedDVDs << std::endl ;
}

void Customer::setDVD(const std::string serialNo)
{
    enlargeArray() ;
    customer_dvd[rentedDVDs - 1] = serialNo ;
}

void Customer::enlargeArray()
{
    std::string* newArr = new std::string[rentedDVDs + 1] ;
    for (int i = 0 ; i < rentedDVDs ; ++i)
        newArr[i] = customer_dvd[i] ;
    delete[] customer_dvd;
    customer_dvd = newArr ;
    ++rentedDVDs ;
}

void Customer::decreaseArray(int index)
{
    int j = 0 ;
    for (int i = 0 ; i < rentedDVDs ; ++i)
        if( i != index ){customer_dvd[j] = customer_dvd[i] ; ++j ;}
    rentedDVDs = j ;
}

Customer::Customer() {
    setID(-1) ;
    setUser("") ;
    rentedDVDs = 0 ;
    customer_dvd = nullptr ;
}

int Customer::indexOf(std::string no)
{
    for (int i = 0 ; i < rentedDVDs ; ++i)
        if (customer_dvd[i] == no)
            return  i ;
    return  -1 ;
}
