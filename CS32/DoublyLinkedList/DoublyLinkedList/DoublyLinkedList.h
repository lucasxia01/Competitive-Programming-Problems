//
//  DoublyLinkedList.h
//  DoublyLinkedList
//
//  Created by Lucas Xia on 1/25/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include <string>

using namespace std;

struct Node {
    string value;
    Node * next;
    Node * prev;
};

class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    int getSize();
    bool insert(int pos, string value);
    bool erase(string value);
    Node* find(string value);
    void print();
    
private:
    Node* head, *tail;
    int size;
};


#endif /* DoublyLinkedList_h */
