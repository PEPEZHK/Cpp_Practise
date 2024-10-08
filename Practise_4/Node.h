//
// Created by perha on 10.05.2024.
//

#ifndef C_NODE_H
#define C_NODE_H
#include <string>
class Node{
public:
    Node() ;
    Node(std::string data) ;
    ~Node() ;
    Node* getNext() ;
    void setNext(Node* ptr) ;
    std::string getData() ;
    void setData(std::string data) ;
private:
    Node* next;
    std::string data;
};
#include "Node.cpp"
#endif //C_NODE_H
