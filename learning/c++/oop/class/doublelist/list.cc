#include "list.h"
#include <iostream>

using std::cout;
using std::endl;

List::List()
:_pHead(nullptr)
,_pTail(nullptr)
,_size(0)
{
    cout << "List()" << endl;
}

List::~List()
{
    cout << "~List()" << endl;
}

void List::display() const
{
    Node *pCur = _pHead;
    for (; pCur; pCur = pCur->_pNext) {
        cout << pCur->_data << " ";
    }
    cout << endl;
}

bool List::empty() const
{
    return _pHead == nullptr;
}

void List::push_front(int data)
{
    //create node
    Node *pNew = new Node(data);
    
    //insert list
    if (empty()) {
        _pTail = pNew;
    }
    else {
        //modify link
        pNew->_pNext = _pHead;
        _pHead->_pPre = pNew;
    }
    //modify _pHead
    _pHead = pNew;
    //add size
    ++_size;
}

void List::push_back(int data)
{
    //create node
    Node *pNew = new Node(data);
    
    //insert list
    if (empty()) {
        _pHead = pNew;
    }
    else {
        //modify link
        _pTail->_pNext = pNew;
        pNew->_pPre = _pTail;
    }
    //modify _pTail
    _pTail= pNew;
    //add size
    ++_size;
}

void List::pop_front()
{
    if (empty()) {
        cout << "List is empty!" << endl;
        return;
    }

    if (1 == _size) {
        //only one
        delete _pHead;
        _pHead = _pTail = nullptr;
    }
    else {
        //modify _pTail
        Node *pCur = _pHead;
        _pHead = _pHead->_pNext;
        _pHead->_pPre = nullptr;

        delete pCur;
        pCur = nullptr;

    }
    //reduce size
    --_size;
}

void List::pop_back()
{
    if (empty()) {
        cout << "List is empty!" << endl;
        return;
    }

    if (1 == _size) {
        //only one
        delete _pHead;
        _pHead = _pTail = nullptr;
    }
    else {
        Node *pCur = _pTail;
        _pTail = _pTail->_pPre;
        _pTail->_pNext = nullptr;

        delete pCur;
        pCur = nullptr;
    }

    --_size;
}

bool List::deleteNode(const int &pos)
{
    if (empty()) {
        cout << "empty!" << endl;
        return false;
    }

    //check pos
    if (pos < 1 || pos > _size) {
        cout << "delete_pos is illegal" << endl;
        return false; 
    }

    if (1 == pos) {
        //only one
        pop_front();
    }
    else if (pos == _size) {
        pop_back();
    }
    else {
        int i = 1;
        Node *pCur = _pHead->_pNext;

        for (i = 1; pCur; ++i, pCur = pCur->_pNext) {
            if (i == pos - 1) {
                pCur->_pPre->_pNext = pCur->_pNext;
                pCur->_pNext->_pPre = pCur->_pPre;

                delete pCur;
                pCur = nullptr;
                --_size;
                break;
            }
        }
    }

    return true;
}

Node *List::find(int data)
{
    if (empty()) {
        cout << "Empty!" << endl;
        return nullptr;
    }

    Node *pCur = _pHead;
    int i = 0;
    for (i = 0; i < _size; ++i, pCur = pCur->_pNext) {
        if (pCur->_data == data) {
            //find and return ptr
            cout << "Find!" << endl;
            return pCur;
        }
    }

    cout << "No this elem!" << endl;
    return nullptr;
}


void List::insert(int pos, int data)
{
    if (pos < 1 || pos > _size + 1) {
        cout << "pos is illegal" << endl;
        return;
    }

    Node *pNew = new Node(data);

    //first
    if (1 == pos) {
        pNew->_pNext = _pHead;
        _pHead->_pPre = pNew;
        _pHead = pNew;
    }

    //last 
    else if (_size + 1 == pos) {
        _pTail->_pNext = pNew;
        pNew->_pPre = _pTail;
    }

    //middle
    else {
        int i = 0;
        Node *pCur = _pHead;
        for (i = 1; i < _size; ++i, pCur = pCur->_pNext) {
            if (i == pos - 1) {
                pCur->_pPre->_pNext = pNew;
                pNew->_pNext = pCur;
                break;
            }
        }
    }

    ++_size;
}

Node *List::location(const int pos)
{
    if (empty()) {
        cout << "Empty!" << endl;
        return nullptr;
    }
    
    if (pos < 1 || pos > _size) {
        cout << "find_pos illegal!" << endl;
        return nullptr;
    }

    int idx = 0;
    Node *pCur = _pHead;
    for (idx = 0; idx < _size; ++idx, pCur = pCur->_pNext) {
        if (idx == pos - 1) {
            cout << "Find! pos " << pos << " elem is " << pCur->_data << endl;
            break;
        }
    }
    return pCur;
}

void List::destory()
{
    while (_pHead) {
        Node *pCur = _pHead;
        delete pCur;
        
        _pHead = _pHead->_pNext;
    }
}

int List::getsize() const
{
    return _size;
}

void List::erase(int data)
{
    //list empty
    if (empty()) {
        cout << "there is no elems!" << endl;
    }

    Node *pCur = _pHead;
    if (data == _pHead->_data) {
        pop_front();
    }
    else if (data == _pTail->_data) {
        pop_back();
    }
    else {
        int i = 0;
        for (i = 0; i < getsize(); ++i, pCur = pCur->_pNext) {
            if (pCur->_data == data) {
#if 1
                //modify pPre->pNext pNext->pPre
                pCur->_pPre->_pNext = pCur->_pNext;
                pCur->_pNext->_pPre = pCur->_pPre;

                delete pCur;
                pCur = nullptr;
                --_size;
#endif
                break;         
            }
        }
    }
}

