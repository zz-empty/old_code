#include <iostream>

using std::cout;
using std::endl;

class MyLinkedList {
private:
    struct LinkNode {
        int _val;
        struct LinkNode *_next;
        LinkNode(int val):_val(val), _next(nullptr) {}
    };

    LinkNode *_head;       //链表头结点
    int _size;                  //链表大小

public:
    MyLinkedList() {
        _head = new LinkNode(0); // 这里定义的头结点 是一个虚拟头结点，而不是真正的链表头结点
        _size = 0;
    }

    //得到index下标的元素值，如果index非法返回-1
    int get(int index) {
        if (0 > index || _size <= index) {
            return -1;
        }

        LinkNode *cur = _head->_next;
        while (index--) {
            cur = cur->_next;
        }
        return cur->_val;
    }

    //头插法
    void addAtHead(int val) {
        LinkNode *node = new LinkNode(val);
        node->_next = _head->_next;
        _head->_next = node;
        ++_size;
    }

    //尾插法
    void addAtTail(int val) {
        //找到指针域是空的结点，插在后面
        LinkNode *cur = _head;
        while (cur->_next) {
            cur = cur->_next;
        }
        LinkNode *node = new LinkNode(val);
        cur->_next = node;
        ++_size;
    }

    //index比size大无效
    //index比0小，头插
    //index==size，尾插
    //index在中间，插在那个位置前
    void addAtIndex(int index, int val) {
        if (index > _size) {
            return;
        }
        if (index < 0) {
            index = 0;
        }
        LinkNode *node = new LinkNode(val);
        LinkNode *cur = _head;
        while (index--) {
            cur = cur->_next;
        }
        node->_next = cur->_next;
        cur->_next = node;
        ++_size;
        return;
    }

    void deleteAtIndex(int index) {
        if (index < 0 || index >= _size) {
            return;
        }
        LinkNode *cur = _head;
        while (index--) {
            cur = cur->_next;
        }
        LinkNode *tmp = cur->_next;
        cur->_next = cur->_next->_next;
        delete tmp;
        tmp = nullptr;
        --_size;
        return;
    }
};

int main()
{
    return 0;
}

