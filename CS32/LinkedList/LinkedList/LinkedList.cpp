//
//  LinkedList.cpp
//  LinkedList
//
//  Created by Lucas Xia on 1/22/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>

#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    size = 0;
}

LinkedList::~LinkedList() {
    Node* temp = head;
    while (temp != nullptr) {
        Node * temp2 = temp->next;
        cout << "deleted " << temp->name << " at " << temp << endl;
        delete temp;
        temp = temp2;
        cout << "temp is now: " << temp2 << endl;
    }
    head = nullptr;
    cout << "it is over" << endl;
}

int LinkedList::getSize() {
    return size;
}

bool LinkedList::insert(int pos, string name, int value) {
    if (pos < 0 || pos > size) return false;
    Node* n = new Node;
    cout << "new pointer at ";
    if (pos == 0) {
        n->name = name;
        n->value = value;
        n->next = head;
        head = n;
    } else {
        Node *temp = head;
        int i = 0;
        while (temp->next != nullptr && i != pos) temp = temp->next;
        n->name = name;
        n->value = value;
        n->next = temp->next;
        temp->next = n;
    }
    cout << n << " with data: " << n->name <<  ", " << n->value << endl;
    cout << "head is now: " << head << endl;
    size++;
    return true;
}

bool LinkedList::erase(string name) {
    Node* temp = head;
    if (temp == nullptr) return false;
    if (head->name == name) {
        cout << "i am deleting this: " << head << endl;
        delete head;
        head = temp->next;
        cout << "head now is: " << head << endl;
        return true;
    }
    while (temp->next != nullptr && temp->next->name != name) temp = temp->next;
    if (temp->next == nullptr) return false;
    Node* temp2 = temp->next;
    temp->next = temp->next->next;
    cout << "i am deleting this: " << temp2 << endl;
    cout << "temp has been changed to " << temp << endl;
    delete temp2;
    
    return true;
}

Node* LinkedList::find(string name) {
    Node *temp = head;
    while (temp != nullptr) {
        if (temp->name == name) return temp;
        temp = temp->next;
    }
    return nullptr;
}

void LinkedList::print() {
    Node *temp = head;
    cout << "Head ptr: " << head << endl;
    while (temp != nullptr) {
        cout << "(Name, Value, Addr, Next Addr): (" << temp->name << ", " << temp->value << ", " << temp << ", " << temp->next << ")" << endl;
        temp = temp->next;
    }
}
