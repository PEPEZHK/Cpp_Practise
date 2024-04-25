#include <iostream>
#include <string>
#include "DVDStoreManagementSystem.h"
#include "DVD.h"
#include "Customer.h"
    DVDStoreManagementSystem::DVDStoreManagementSystem()
    {
        amountOfTransactions = 0 ;
        amountOfDVDs = 0 ;
        amountOfCustomers = 0 ;
        customers = new Customer[amountOfCustomers] ;
        DVDs = new DVD[amountOfDVDs] ;
        transactions = new std::string[amountOfTransactions] ;
    }
    DVDStoreManagementSystem::~DVDStoreManagementSystem()
    {
        delete[] transactions ;
        delete[] customers ;
        delete[] DVDs ;
    }

    void DVDStoreManagementSystem::addDVD(const std::string serialNo, const std::string title, const std::string director)
    {
        if (DVDExists(serialNo) == -1)
        {
            enlargeDVDStore() ;
            DVDs[amountOfDVDs-1] = DVD(serialNo , title , director) ;
            std::cout << "DVD with serial number " << serialNo << " successfully added." << std::endl ;
        }
        else
        {
            std::cout << "Cannot add DVD. DVD with serial number " << serialNo << " already exists." << std::endl ;
        }
    }
    void DVDStoreManagementSystem::removeDVD(const std::string serialNo)
    {
        int index = DVDExists(serialNo) ;

        if (index != -1)
        {
            if (!DVDs[index].isAvailable())
            {
                std::cout << "Cannot remove DVD. DVD with serial number " << serialNo <<" is currently rented by a customer." << std::endl ;
            }
            else
            {
                decreaseDVDStore(index) ;
                std::cout << "DVD with serial number " << serialNo << " successfully removed." << std::endl;
            }
        }
        else
            std::cout << "Cannot remove DVD. DVD with serial number " << serialNo << " not found." << std::endl ;
    }
    void DVDStoreManagementSystem::addCustomer(const int customerID, const std::string name)
    {
        if(customerExists(customerID) == -1)
        {
            enlargeCustomers() ;
            customers[amountOfCustomers-1] = Customer(customerID , name) ;
            std::cout << "Customer with ID " << customerID <<" successfully added." << std::endl ;
        }
        else
            std::cout << "Cannot add customer. Customer with ID " << customerID << " already exists." << std::endl ;
    }
    void DVDStoreManagementSystem::removeCustomer(const int customerID)
    {
        int index = customerExists(customerID) ;

        if (index != -1)
        {
            if (customers[index].getRents() != 0)
            {
                std::cout << "Cannot remove customer. Customer with ID " << customerID << " has rented DVDs." << std::endl ;
            }
            else
            {
                decreaseCustomers(index) ;
                std::cout << "Customer with ID " << customerID << " successfully removed." << std::endl ;
            }
        }
        else
            std::cout << "Cannot remove customer. Customer with ID " << customerID << " not found." << std::endl ;
    }

    void DVDStoreManagementSystem::rentDVD(const int customerID, const std::string serialNo)
    {
        int custIndex = customerExists(customerID) ;
        int DVDIndex = DVDExists(serialNo) ;
        if (custIndex == -1 && DVDIndex == -1) {
            std::cout << "Cannot rent DVD. Customer with ID " << customerID << " and " << "DVD with serial number "
                      << serialNo << " not found." << std::endl;
            return;
        }
        else if (custIndex == -1) {
            std::cout << "Cannot rent DVD. " << "Customer with ID " << customerID << " not found." << std::endl;
            return;
        }
        else if (DVDIndex == -1) {
            std::cout << "Cannot rent DVD. " << "DVD with serial number " << serialNo << " not found." << std::endl;
            return;
        }

        if (!DVDs[DVDIndex].isAvailable())
        {
            std::cout << "Cannot rent DVD. " << "DVD with serial number " << serialNo << " is not available." << std::endl ;
            return;
        }

        DVDs[DVDIndex].setAvailability(false) ;
        customers[custIndex].setDVD(serialNo) ;
        newTransaction("Rental" , serialNo , std::to_string(customerID)) ;
        std::cout << "DVD with serial number " << serialNo <<
                     " successfully rented by customer with ID " << customerID <<"." << std::endl ;
    }
    void DVDStoreManagementSystem::returnDVD(const int customerID, const std::string serialNo)
    {
        int custIndex = customerExists(customerID) ;
        int DVDIndex = DVDExists(serialNo) ;
        if (custIndex == -1 && DVDIndex == -1) {
            std::cout << "Cannot return DVD. Customer with ID " << customerID << " and " << "DVD with serial number "
                      << serialNo << " not found." << std::endl;
            return;
        }
        else if (custIndex == -1) {
            std::cout << "Cannot return DVD. Customer with ID " << customerID << " not found." << std::endl;
            return;
        }
        else if (DVDIndex == -1) {
            std::cout << "Cannot return DVD. DVD with serial number " << serialNo << " not found." << std::endl;
            return;
        }
        
        int index = customers[custIndex].indexOf(serialNo) ;
        if (index == -1)
        {
            std::cout << "Cannot return DVD. DVD with serial number " << serialNo << " not rented by customer with ID " << customerID << "." << std::endl ;
            return;
        }
        customers[custIndex].decreaseArray(index) ;
        DVDs[DVDIndex].setAvailability(true) ;
        newTransaction("Return" , serialNo , std::to_string(customerID)) ;
        std::cout << "DVD with serial number " << serialNo <<
                  " successfully returned by customer with ID " << customerID <<"." << std::endl ;
    }
    void DVDStoreManagementSystem::showAllDVDs() const
    {
        std::cout << "DVDs in the system:" << std::endl ;
        if (amountOfDVDs == 0)
        {
            std::cout << "None" << std::endl;
            return;
        }
        else
        {
            for (int i = 0 ; i < amountOfDVDs ; i++)
            {
                DVDs[i].toString() ;
            }
        }
    }
    void DVDStoreManagementSystem::showAllCustomers() const
    {
        std::cout << "Customers in the system:" << std::endl ;
        if (amountOfCustomers == 0)
        {
            std::cout << "None" << std::endl ;
            return;
        }
        for (int i = 0 ; i < amountOfCustomers ; i++)
        {
            customers[i].toString() ;
        }
    }
    void DVDStoreManagementSystem::showDVD(const std::string serialNo) const
    {
        int index = DVDExists(serialNo) ;
        if (index != -1)
        {
            DVDs[index].toString() ;
        }
        else
        {
            std:: cout << "DVD with serial number " << serialNo << " not found." << std::endl ;
        }
    }
    void DVDStoreManagementSystem::showCustomer(const int customerID) const
    {
        int index = customerExists(customerID) ;
        if (index != -1)
        {
            customers[index].toString() ;
        }
        else
        {
            std::cout << "Customer with ID " << customerID << " not found." << std::endl ;
        }
    }
    void DVDStoreManagementSystem::showTransactionHistory() const
    {
        std::cout << "Transactions in the system:" << std::endl ;
        if (amountOfTransactions == 0)
        {
            std::cout << "None" << std::endl ;
            return ;
        }
        for (int i = 0 ; i < amountOfTransactions ; ++i)
        {
            std::cout << transactions[i] << std::endl ;
        }
    }
    int DVDStoreManagementSystem::customerExists(const int customerID) const {
        for (int i = 0 ; i < amountOfCustomers ; i++)
            if (customers[i].getID() == customerID)
                return  i ;

        return  -1 ;
    }

    int DVDStoreManagementSystem::DVDExists(const std::string no) const {
        for (int i = 0 ; i < amountOfDVDs ; i++)
            if (DVDs[i].getNo() == no)
                return  i ;

        return  -1 ;
    }

    void DVDStoreManagementSystem::enlargeCustomers()
    {
        Customer* newArr = new Customer[amountOfCustomers+1] ;
        for (int i = 0; i < amountOfCustomers; ++i)
            newArr[i] = customers[i];
        delete[] customers ;
        customers = newArr ;
        ++amountOfCustomers ;
    }

    void DVDStoreManagementSystem::enlargeDVDStore()
    {
        DVD* newArr = new DVD[amountOfDVDs + 1] ;
        for (int i = 0 ; i < amountOfDVDs ; ++i)
            newArr[i] = DVDs[i] ;
        delete[] DVDs ;
        DVDs = newArr ;
        ++amountOfDVDs;
    }

    void DVDStoreManagementSystem::decreaseDVDStore(const int index)
    {
        int j = 0 ;
        DVD* newArr = new DVD[amountOfDVDs - 1] ;
        for (int i = 0 ; i < amountOfDVDs ; ++i)
            if( i != index )
            {
                newArr[j] = DVDs[i] ;
                ++j ;
            }
        delete[] DVDs ;
        DVDs = newArr ;
        --amountOfDVDs ;
    }

    void DVDStoreManagementSystem::decreaseCustomers(const int index)
    {
        int j = 0 ;
        Customer* newArr = new Customer[amountOfCustomers - 1] ;
        for (int i = 0 ; i < amountOfCustomers ; ++i)
            if( i != index )
            {
                newArr[j] = customers[i] ;
                ++j ;
            }
        delete[] customers ;
        customers = newArr ;
        --amountOfCustomers ;
    }

    void DVDStoreManagementSystem::newTransaction(std::string state, std::string no, std::string id)
    {
        std::string* newArr = new std::string[amountOfTransactions + 1] ;
        for (int i = 0 ; i < amountOfTransactions ; ++i)
            newArr[i] = transactions[i] ;
        delete[] transactions ;
        transactions = newArr ;
        transactions[amountOfTransactions] = "Transaction: " + state + ", Customer: " + id + ", DVD: " + no ;
        ++amountOfTransactions ;
    }