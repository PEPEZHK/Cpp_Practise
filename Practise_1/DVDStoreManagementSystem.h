#ifndef C_DVDSTOREMANAGEMENTSYSTEM_H
#define C_DVDSTOREMANAGEMENTSYSTEM_H
#include <string>
#include "Customer.h"
#include "DVD.h"
class DVDStoreManagementSystem{
 public:
    DVDStoreManagementSystem();
    ~DVDStoreManagementSystem();
    void addDVD(const std::string serialNo, const std::string title, const std::string director);
    void removeDVD(const std::string serialNo);
    void addCustomer(const int customerID, const std::string name);
    void removeCustomer(const int customerID);
    void rentDVD(const int customerID, const std::string serialNo);
    void returnDVD(const int customerID, const std::string serialNo);
    void showAllDVDs() const;
    void showAllCustomers() const;
    void showDVD(const std::string serialNo) const;
    void showCustomer(const int customerID) const;
    void showTransactionHistory() const;
private:
    void newTransaction(std::string state , std::string no , std::string id) ;
    std::string* transactions ;
    int amountOfTransactions ;
    Customer* customers ;
    DVD* DVDs ;
    int amountOfDVDs;
    int amountOfCustomers;
    int customerExists(const int customerID) const;
    int DVDExists(const std::string no) const;
    /*void enlargeArray(std::string*& arr, int size);
    void decreaseArray(std::string*& arr, int index, const int size);
    void deleteData(std::string*& arr, int index, const int size);*/
    void decreaseDVDStore(const int index) ;
    void decreaseCustomers(const int index) ;
    void enlargeDVDStore() ;
    void enlargeCustomers() ;
};

#endif