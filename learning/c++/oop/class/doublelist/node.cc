#include "list.h"
#include <iostream>

using std::cout;
using std::endl;

Node::Node(int data)
:_data(data)
,_pPre(nullptr)
,_pNext(nullptr)
{
    cout << "Node()" << endl;
}

Node::~Node()
{
    cout << "~Node()" << endl;
}


Node::Node(const Node &rhs)
:_data(rhs._data)
,_pPre(rhs._pPre)
,_pNext(rhs._pNext)
{
    cout << "Node(const Node &)" << endl;
}

Node &Node::operator=(const Node &rhs)
{
    cout << "Node &operator=(const Node &)" << endl;
    _data = rhs._data;
    _pPre = rhs._pPre;
    _pNext = rhs._pNext;
    return *this;
}
