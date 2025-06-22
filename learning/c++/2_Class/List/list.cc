#include "list.hpp"
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{

List::List()
:_head(nullptr)
,_tail(nullptr)
,_size(0)
{}

List::~List()
{

}


void List::push_front(int data)
{
    Node *pNew = new Node();
    pNew->data = data;

    if (empty()) {
        _head = _tail = pNew;        
    }
    else {
        pNew->next = _head;
        _head->pre = pNew;
        _head = pNew;
    }

    ++_size;
}

void List::push_back(int data)
{
    Node *pNew = new Node();
    pNew->data = data;

    if (empty()) {
        _head = _tail = pNew;        
    }
    else {
        pNew->pre = _tail;
        _tail->next = pNew;
        _tail = pNew;
    }

    ++_size;
}

void List::pop_front()
{
    if (!empty()) {
        Node *p = _head;
        _head = _head->next;

        if (_head) { 
            _head->pre = nullptr;
        }
        else { 
            _tail = _head; //only one
        }

        delete p;
        p = nullptr;

        --_size;
    }
    else {
        cout << "the list is empty!" << endl;
    }
}

void List::pop_back()
{
    if (!empty()) {
        Node *p = _tail;
        _tail = _tail->pre;

        if (_tail) {
            _tail->next = nullptr;
        }
        else {
            _head = _tail;
        }

        delete p;
        p = nullptr;

        --_size;
    }
    else {
        cout << "the list is empty!" << endl;
    }


}

bool List::find(int data)
{
    if (empty()) {
        return false;
    } 

    Node *p = _head;
    for (; p != nullptr; p = p->next) {
        if (p->data == data) {
            return true;
        }
    }

    return false;
}

#if 1
void List::insert(int pos, int data)
{
    if (pos < 1 || pos > _size + 1) {
        cout << "pos is illegal!" << endl;
        return;
    }


    Node *pNew = new Node();
    pNew->data = data;

    //first
    if (1 == pos) {
        pNew->next = _head;
        _head->pre = pNew;
        _head = pNew;

        if (_tail == nullptr) {
            _tail = pNew;
        }
    }

    //last
    else if (pos == _size + 1) {
        _tail->next = pNew;
        pNew->pre = _tail;
        _tail = pNew;
    }

    //middle
    else {
        int idx = 0;
        Node *p = _head;
        for (; idx < _size; p = p->next, ++idx) {
            if (idx == pos - 1) {
                pNew->next = p;
                pNew->pre = p->pre;
                p->pre = pNew;
                p->pre->next = pNew;
                break;
            }
        }
    }
    ++_size;
}
#endif


#if 0
void List::insert(int pos, int data)
{
    if (pos < 1 || pos > _size + 1) {
        cout << "pos is illegal" << endl;
        return;
    }

    Node *pNew = new Node();
    pNew->data = data;

    //first
    if (1 == pos) {
        pNew->next = _head;
        _head->pre = pNew;
        _head = pNew;
        if (_tail == nullptr) {
            _tail = pNew;
        }
    }

    //last 
    else if (_size + 1 == pos) {
        _tail->next = pNew;
        pNew->pre = _tail;
        _tail = pNew;
    }

    //middle
    else {
        int i = 0;
        Node *pCur = _head;
        for (i = 1; i < _size; ++i, pCur = pCur->next) {
            if (i == pos - 1) {
                pCur->pre->next = pNew;
                pNew->next = pCur;
                break;
            }
        }
    }

    ++_size;
}
#endif

void List::display() const
{
    if (!empty()) {
        Node *p = _head;
        for (; p != nullptr; p = p->next) {
            cout << p->data << "  ";
        }
        cout << endl;
    }
    else {
        cout << "the list is empty!" << endl;
    }
}

bool List::erase(int data)
{
    if (empty()) {
        cout << "the list is empty!" << endl;
        return false;
    } 

    for (Node *p = _head; p != nullptr; p = p->next) {
        if (p->data == data) { //find
            if (p == _head) {   //is _head
                _head = _head->next;
                if (p == _tail) {   //only one
                    _tail = _head;
                }
            }
            else if (p == _tail) {  // is _tail
                _tail = _tail->pre;
            }
            else { //is middle
                p->pre->next = p->next;
                p->next->pre = p->pre;
            }
            
            delete p;
            p = nullptr;

            --_size;
            return true;
        }
    }
    return false;
}

}//end of namespace wd
