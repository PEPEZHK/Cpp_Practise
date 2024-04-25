#ifndef C_CUSTOMER_H
#define C_CUSTOMER_H
#include <iostream>
#include <string>
class Customer
        {
        public:
            Customer() ;
            Customer(const int customerID, const std::string name) ;
            ~Customer() ;

            int getRents() ;
            int getID() ;
            std::string getName() ;
            std::string* getRentedDVDs() ;
            void setUser(const std::string name) ;
            void setID(const int customerID) ;
            void toString() ;
            void setDVD(const std::string serialNo) ;
            int indexOf(std::string no) ;
            void decreaseArray(int index) ;
        private:
            int ID_Number;
            std::string Username;
            std::string* amountOfRents;
            void enlargeArray() ;
            std::string* customer_dvd;
            int rentedDVDs ;
        };
#endif
