//
// Created by perha on 10.05.2024.
//

#include "Node.h"
#include <string>
Node::Node()
{
    next = nullptr ;
}
Node::Node(std::string data)
{
    this->data = data ;
    next = nullptr ;
}
Node::~Node(){}
Node* Node::getNext()
{
    return  next ;
}
void Node::setNext(Node* ptr)
{
    next = ptr ;
}
void Node::setData(std::string data)
{
    this->data = data ;
}
std::string Node::getData()
{
    return data ;
}