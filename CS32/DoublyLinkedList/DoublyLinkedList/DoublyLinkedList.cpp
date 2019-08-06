//
//  DoublyLinkedList.cpp
//  DoublyLinkedList
//
//  Created by Lucas Xia on 1/25/19.
//  Copyright © 2019 Lucas Xia. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <string>

#include "DoublyLinkedList.h"

using namespace std;

DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

DoublyLinkedList::~DoublyLinkedList() {
    Node* temp = head;
    while (temp != nullptr) {
        Node * temp2 = temp->next;
        cout << "deleted " << temp->value << " at " << temp << endl;
        delete temp;
        temp = temp2;
    }
    head = nullptr;
    tail = nullptr;
    cout << "it is over" << endl;
}

int DoublyLinkedList::getSize() {
    return size;
}

bool DoublyLinkedList::insert(int pos, string value) {
    if (pos < 0 || pos > size) return false;
    Node* n = new Node;
    cout << "new pointer at ";
    if (pos == 0) {
        n->value = value;
        n->next = head;
        n->prev = nullptr;
        head = n;
        if (n->next != nullptr) n->next->prev = n;
        if (size == 0) tail = n;
    } else if (pos == size) {
        tail->next = n;
        n->value = value;
        n->next = nullptr;
        n->prev = tail;
        n->prev->next = n;
        tail = n;
    } else {
        Node *temp = head;
        int i = 0;
        while (temp->next != nullptr && i != pos) temp = temp->next;
        n->value = value;
        n->next = temp->next;
        n->prev = temp;
        temp->next = n;
    }
    cout << n << " with data: " << n->value << endl;
    cout << n->value << " points at " << n->next << ", " << n->prev << endl;
    cout << "head, tail is now: " << head << ", " << tail << endl;
    size++;
    print();
    return true;
}

bool DoublyLinkedList::erase(string value) {
    Node* temp = head;
    if (temp == nullptr) return false; // if size is 0, no erase
    if (head->value == value) { // if element is first one
        delete head;
        head = temp->next;
        cout << "i am deleting " << temp->value << " at " << temp << endl;
        size--;
        return true;
    }
    while (temp->next != nullptr && temp->next->value != value) temp = temp->next;
    if (temp->next == nullptr) return false;
    if (temp->next == tail) {
        tail = temp;
        delete temp->next;
        temp->next = nullptr;
    } else {
        Node* temp2 = temp->next;
        cout << "i am deleting " << temp->value << " at " << temp << endl;
        temp->next = temp->next->next;
        delete temp2;
    }
    size--;
    return true;
}

Node* DoublyLinkedList::find(string value) {
    Node *temp = head;
    while (temp != nullptr) {
        if (temp->value == value) return temp;
        temp = temp->next;
    }
    return nullptr;
}

void DoublyLinkedList::print() {
    Node *temp = head;
    cout << "Head ptr: " << head << endl;
    while (temp != nullptr) {
        cout << "(Value, Addr, Next, Prev): (" << temp->value << ", " << temp << ", " << temp->next << "," << temp->prev << ")" << endl;
        temp = temp->next;
    }
    cout << endl;
}
