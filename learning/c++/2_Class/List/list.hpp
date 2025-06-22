#ifndef __LIST_HPP__
#define __LIST_HPP__

namespace wd
{

struct Node
{
    int data;
    Node * pre;
    Node * next;
};

class List
{
public:
    List();
    ~List();

    bool empty() const      {   return _head == nullptr;    }
    int size() const        {   return _size;   }

    void push_front(int data);//在头部进行插入         
    void push_back(int data);//在尾部进行插入

    void pop_front();//在链表头部进行删除          
    void pop_back();//在链表的尾部进行删除

    bool find(int data);//在链表中进行查找
    void insert(int pos, int data);//在指定位置后面插入pos 
    void display() const; //打印链表	
    bool erase(int data);//删除一个指定的节点			 		

private:
    Node * _head;
    Node * _tail;
    int    _size;
};

}//end of namespace wd

#endif
