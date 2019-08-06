//
//  LinkedList.h
//  LinkedList
//
//  Created by Lucas Xia on 1/22/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#ifndef LinkedList_h
#define LinkedList_h

#include <string>

using namespace std;

struct Node {
    string name;
    int value;
    Node * next;
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    int getSize();
    bool insert(int pos, string name, int value);
    bool erase(string name);
    Node* find(string name);
    void print();
    
private:
    Node * head;
    int size;
};

#endif /* LinkedList_h */
